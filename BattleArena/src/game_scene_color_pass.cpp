#include "game_scene_color_pass.h"
#include "render_state_manager.h"
#include "shader_program_manager.h"
#include "engine_context.h"
#include "windowing_service.h"
#include <iostream>

using namespace Blade;

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

	return true;
}

PipelineData<D3D11RenderTarget*> GameSceneColorPassStage::Execute(const std::vector<RenderComponent*>& data, const PipelineData<D3D11RenderTarget*>& tdata) noexcept
{

	//TODO: Draw here
	m_ColorRenderTarget.Bind(RenderTargetBindType::COLOR_AND_DEPTH);

	Vec4f clearColor{ 0.2f, 0.2f, 0.2f, 0.0f };
	m_ColorRenderTarget.Clear(&clearColor[0]);

	m_ColorRenderTarget.Unbind();

	DisplayToScreen();

	return PipelineData<D3D11RenderTarget*>{ &m_ColorRenderTarget };
}
