#include "game_scene_color_pass.h"
#include "render_state_manager.h"
#include "shader_program_manager.h"
#include "engine_context.h"
#include "windowing_service.h"
#include <iostream>

using namespace Blade;

//Temporary test
struct UniformBuffer
{
	Mat4f MVP;
	Mat4f ITMV;
	Mat4f textureMatrix;
	Vec4f diffuse;
	Vec4f specular;
};

void GameSceneColorPassStage::DisplayToScreen() const
{
	D3D11Context* ctx{ EngineContext::get_GAPI_context() };

	ComPtr<ID3D11DeviceContext> dev_con{ ctx->GetDeviceContext() };

	dev_con->OMSetRenderTargets(1, ctx->GetGetAddressOfDefaultRenderTargetView(), ctx->GetDefaultDepthStencilView());

	Vec4f cl_col{ 0.0, 0.0, 0.0, 0.0 };
	dev_con->ClearRenderTargetView(ctx->GetDefaultRenderTargetView(), &cl_col[0]);
	dev_con->ClearDepthStencilView(ctx->GetDefaultDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	ShaderProgramManager::get("render_texture_sdrprog")->Bind();

	ComPtr<ID3D11ShaderResourceView> srv{ m_ColorRenderTarget.GetColorAttachment() };
	dev_con->PSSetShaderResources(0, 1, srv.GetAddressOf());
	dev_con->PSSetSamplers(0, 1, m_SamplerLinearWrap.GetAddressOf());

	RenderStateManager::Set(RenderStateType::RS_DRAW_SOLID);
	dev_con->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	dev_con->Draw(4, 0);

	ID3D11ShaderResourceView* null_srv{ nullptr };
	dev_con->PSSetShaderResources(0, 1, &null_srv);
}

bool GameSceneColorPassStage::Initialize()
{
	Vec2i windowSize{ WindowingService::GetWindow(0)->GetSize() };
	
	if (!m_ColorRenderTarget.Create(windowSize))
	{
		return false;
	}

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	D3D11Context* ctx{ EngineContext::get_GAPI_context() };
	ComPtr<ID3D11Device> device{ ctx->GetDevice() };

	HRESULT res = device->CreateSamplerState(&samplerDesc, m_SamplerLinearWrap.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "Linear Texture Wrap sampler creation failed!" << std::endl;
	}

	UniformBuffer uniforms = {};
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(uniforms);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	res = device->CreateBuffer(&cbDesc, nullptr, m_ConstantBuffer.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "Renderer initialization failed: Uniform buffer creation failed." << std::endl;
	}

	return true;
}

PipelineData<D3D11RenderTarget*> GameSceneColorPassStage::Execute(const std::vector<RenderComponent*>& data, const PipelineData<D3D11RenderTarget*>& tdata) noexcept
{

	//TODO: Draw here
	m_ColorRenderTarget.Bind(RenderTargetBindType::COLOR_AND_DEPTH);

	Vec4f clearColor{ 0.2f, 0.2f, 0.2f, 0.0f };
	m_ColorRenderTarget.Clear(&clearColor[0]);

	Vec2i winSize{ WindowingService::GetWindow(0)->GetSize() };

	D3D11Context* context{ EngineContext::get_GAPI_context() };
	ID3D11DeviceContext* device_context{ context->GetDeviceContext() };

	ShaderProgramManager::get("default_sdrprog")->Bind();

	for (auto renderComponent : data)
	{
		Mat4f p{ MathUtils::PerspectiveLH(MathUtils::ToRadians(60.0f), static_cast<float>(winSize.x), static_cast<float>(winSize.y), 0.1f, 500.0f) };

		Mat4f v{ MathUtils::Translate(Mat4f{1.0f}, Vec3f{0.0f, 0.0f, 2.0f}) };

		Mat4f mvp{ p * v };

		UniformBuffer uniforms;
		uniforms.MVP = MathUtils::Transpose(mvp);
		uniforms.ITMV = MathUtils::Inverse(v);

		Material material{ renderComponent->GetMaterial() };

		uniforms.diffuse = material.diffuse;
		uniforms.specular = material.specular;

		D3D11_MAPPED_SUBRESOURCE ms;

		device_context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		memcpy(ms.pData, &uniforms, sizeof(UniformBuffer));
		device_context->Unmap(m_ConstantBuffer.Get(), 0);

		device_context->VSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
		device_context->PSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());

		Mesh* mesh{ renderComponent->GetMesh() };

		RenderStateManager::Set(material.blendState);

		mesh->GetVbo()->Bind();

		if (mesh->GetIndexCount())
		{
			mesh->GetIbo()->Bind();
			mesh->GetIbo()->Draw();
		}
		else
		{
			mesh->GetVbo()->Draw();
		}

		RenderStateManager::Set(RenderStateType::BS_BLEND_DISSABLED);
	}


	m_ColorRenderTarget.Unbind();

	DisplayToScreen();

	return PipelineData<D3D11RenderTarget*>{ &m_ColorRenderTarget };
}
