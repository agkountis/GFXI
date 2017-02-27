#include "game_scene_color_pass.h"
#include "render_state_manager.h"
#include "shader_program_manager.h"
#include "engine_context.h"
#include "windowing_service.h"
#include <iostream>
#include "math_utils.h"
#include "entity.h"

using namespace Blade;

//Temporary test
struct UniformBuffer
{
	Mat4f MVP;
	Mat4f ITMV;
	Mat4f MV;
	Mat4f V;
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

	ShaderProgramManager::Get("render_texture_sdrprog")->Bind();

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

	//Bind the render target.
	m_ColorRenderTarget.Bind(RenderTargetBindType::COLOR_AND_DEPTH);

	//Define a clear color and clear the color buffer and depth stencil.
	Vec4f clearColor{ 0.2f, 0.2f, 0.2f, 0.0f };
	m_ColorRenderTarget.Clear(&clearColor[0]);

	//Get the window size.
	Vec2i winSize{ WindowingService::GetWindow(0)->GetSize() };

	//Get the device context.
	D3D11Context* context{ EngineContext::get_GAPI_context() };
	ID3D11DeviceContext* device_context{ context->GetDeviceContext() };

	//Bind the requested shader program.
	ShaderProgramManager::Get("default_sdrprog")->Bind();

	//Set the linear wrap texture sampler.
	device_context->PSSetSamplers(0, 1, m_SamplerLinearWrap.GetAddressOf());

	//Iterate through the render components.
	for (auto renderComponent : data)
	{
		//Get the model matrix from the Entity.
		Mat4f m{ renderComponent->GetParent()->GetXform() };
		
		//Temporarily define a fixed projection matrix.
		Mat4f p{ MathUtils::PerspectiveLH(MathUtils::ToRadians(60.0f), static_cast<float>(winSize.x), static_cast<float>(winSize.y), 0.1f, 500.0f) };

		//Temporarily define a fixed view matrix.
		Mat4f v{ MathUtils::Translate(Mat4f{1.0f}, Vec3f{0.0f, 0.0f, 2.0f}) };

		//Calculate the ModelViewProjection matrix. 
		Mat4f mvp{ p * v * m };

		//Calculate the ModelView matrix.
		Mat4f mv{ v * m };

		Mat4f textureMatrix{ MathUtils::Scale(Mat4f{1.0f}, Vec3f{4.0f, 4.0f, 0.0f}) };

		//Fill up the uniform structure.
		UniformBuffer uniforms;
		uniforms.MVP = MathUtils::Transpose(mvp);
		uniforms.ITMV = MathUtils::Inverse(v);
		uniforms.MV = MathUtils::Transpose(mv);
		uniforms.V = MathUtils::Transpose(v);
		uniforms.textureMatrix = MathUtils::Transpose(textureMatrix);

		//Get the material from the RenderComponent.
		Material material{ renderComponent->GetMaterial() };

		uniforms.diffuse = material.diffuse;
		uniforms.specular = material.specular;

		// If the material has a diffuse texture bind it.
		if (material.textures[TEX_DIFFUSE])
		{
			material.textures[TEX_DIFFUSE]->Bind();
		}

		// If the material has a specular texture bind it.
		if (material.textures[TEX_SPECULAR])
		{
			material.textures[TEX_SPECULAR]->Bind();
		}

		// If the material has a normal map texture bind it.
		if (material.textures[TEX_NORMAL])
		{
			material.textures[TEX_NORMAL]->Bind();
		}

		//Copy the data into the D3D11 constant buffer.
		D3D11_MAPPED_SUBRESOURCE ms;
		device_context->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
		memcpy(ms.pData, &uniforms, sizeof(UniformBuffer));
		device_context->Unmap(m_ConstantBuffer.Get(), 0);

		//Set the constant buffer to both the Vertex shader and the Pixel shader.
		device_context->VSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
		device_context->PSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());

		//Get the Mesh from the Render component.
		Mesh* mesh{ renderComponent->GetMesh() };

		//Set the blend state of the RenderComponent's material
		RenderStateManager::Set(material.blendState);

		//Bind the VBO
		mesh->GetVbo()->Bind();

		//If the mesh is indexed Draw indexed.
		if (mesh->GetIndexCount())
		{
			mesh->GetIbo()->Bind();
			mesh->GetIbo()->Draw();
		}
		else //Else draw arrays.
		{
			mesh->GetVbo()->Draw();
		}

		// Disable any blend states activated.
		RenderStateManager::Set(RenderStateType::BS_BLEND_DISSABLED);
	}

	//Unbind the render target.
	m_ColorRenderTarget.Unbind();

	//Disaply to the fullscreen quad.
	DisplayToScreen();

	// Return the render target so that the next stage of the pipeline can process it if needed.
	return PipelineData<D3D11RenderTarget*>{ &m_ColorRenderTarget };
}
