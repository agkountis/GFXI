#include "game_scene_color_pass_ovr.h"
#include "trace.h"
#include "resource_manager.h"
#include "d3d/D3D11_texture.h"
#include "engine_context.h"
#include "uniform_buffers.h"
#include "OVR/OVR_CAPI_D3D.h"

using namespace Blade;

// Private Functions -------------------------------------------------------------------
bool GameSceneColorPassStageOvr::InitializeOvr() noexcept
{
	if (OVR_FAILURE(ovr_Initialize(nullptr)))
	{
		BLADE_ERROR("Failed to initialize Oculus Rift.");
		return false;
	}

	return true;
}
void GameSceneColorPassStageOvr::ShutdownOvr() noexcept
{
	ovr_Shutdown();
}

bool GameSceneColorPassStageOvr::InitializeOvrData() noexcept
{
	if (OVR_FAILURE(ovr_Create(&m_OvrData.session, &m_OvrData.graphicsLuid)))
	{
		BLADE_ERROR("Failed to create OVR session.");
		return false;
	}

	m_OvrData.hmdDesc = ovr_GetHmdDesc(m_OvrData.session);
	BLADE_TRACE("Initialized HMD: " + std::string{ m_OvrData.hmdDesc.Manufacturer } + " - " + std::string{ m_OvrData.hmdDesc.ProductName });

	m_OvrData.eyeRenderDesc[ovrEye_Left] = ovr_GetRenderDesc(m_OvrData.session, ovrEye_Left, m_OvrData.hmdDesc.DefaultEyeFov[ovrEye_Left]);
	m_OvrData.eyeRenderDesc[ovrEye_Right] = ovr_GetRenderDesc(m_OvrData.session, ovrEye_Right, m_OvrData.hmdDesc.DefaultEyeFov[ovrEye_Right]);

	m_OvrData.hmdToEyeViewOffset[ovrEye_Left] = m_OvrData.eyeRenderDesc[ovrEye_Left].HmdToEyeOffset;
	m_OvrData.hmdToEyeViewOffset[ovrEye_Right] = m_OvrData.eyeRenderDesc[ovrEye_Right].HmdToEyeOffset;

	m_OvrData.viewScaleDesc.HmdSpaceToWorldScaleInMeters = 1.0f;
	m_OvrData.viewScaleDesc.HmdToEyeOffset[ovrEye_Left] = m_OvrData.hmdToEyeViewOffset[ovrEye_Left];
	m_OvrData.viewScaleDesc.HmdToEyeOffset[ovrEye_Right] = m_OvrData.hmdToEyeViewOffset[ovrEye_Right];

	m_OvrData.layer.Fov[ovrEye_Left] = m_OvrData.eyeRenderDesc[ovrEye_Left].Fov;
	m_OvrData.layer.Fov[ovrEye_Right] = m_OvrData.eyeRenderDesc[ovrEye_Right].Fov;

	m_OvrData.eyeResolution[ovrEye_Left] = ovr_GetFovTextureSize(m_OvrData.session, ovrEye_Left, m_OvrData.hmdDesc.DefaultEyeFov[ovrEye_Left], 1.0);
	m_OvrData.eyeResolution[ovrEye_Right] = ovr_GetFovTextureSize(m_OvrData.session, ovrEye_Right, m_OvrData.hmdDesc.DefaultEyeFov[ovrEye_Right], 1.0);


	int width{ m_OvrData.eyeResolution[ovrEye_Left].w + m_OvrData.eyeResolution[ovrEye_Right].w };
	int height{ m_OvrData.eyeResolution[ovrEye_Left].h + m_OvrData.eyeResolution[ovrEye_Right].h };

	m_OvrData.textureSwapChain = nullptr;
	ovrTextureSwapChainDesc swapChainDesc{};
	swapChainDesc.Type = ovrTexture_2D;
	swapChainDesc.ArraySize = 1;
	swapChainDesc.Format = OVR_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.MipLevels = 1;
	swapChainDesc.SampleCount = 1;
	swapChainDesc.StaticImage = ovrFalse;

	ovrResult res{ ovr_CreateTextureSwapChainDX(m_OvrData.session, G_GAPIContext.GetDevice(), &swapChainDesc, &m_OvrData.textureSwapChain) };
	if (OVR_FAILURE(res))
	{
		BLADE_ERROR("Failed to create the OVR swapchain.");
		return false;
	}
	
	ID3D11Texture2D* tex;
	ovr_GetTextureSwapChainBufferDX(m_OvrData.session, m_OvrData.textureSwapChain, 0, IID_PPV_ARGS(&tex));

	m_ColorRenderTarget.SetColorAttachment(tex);
	m_ColorRenderTarget.Create(Vec2i{ width, height });

	return true;
}

void GameSceneColorPassStageOvr::CalculateEyePoses() noexcept
{
}

const OvrXformData& GameSceneColorPassStageOvr::GetOvrXformDataPerEye(ovrEyeType eye) noexcept
{
	return m_OvrXformData;
}
// -------------------------------------------------------------------------------------

GameSceneColorPassStageOvr::GameSceneColorPassStageOvr(const std::string& name)
	: Blade::RenderPassStage{ name }
{
}

bool GameSceneColorPassStageOvr::Initialize()
{
	if (!InitializeOvr())
	{
		return false;
	}

	InitializeOvrData();

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
	ID3D11Device* device{ G_GAPIContext.GetDevice() };

	HRESULT res = device->CreateSamplerState(&samplerDesc, m_SamplerLinearWrap.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Linear Texture Wrap sampler creation failed!" << std::endl;

		return false;
	}


	D3D11_BUFFER_DESC cbDesc{};
	cbDesc.ByteWidth = sizeof(UniformBuffer);
	cbDesc.Usage = D3D11_USAGE_DYNAMIC;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


	res = device->CreateBuffer(&cbDesc, nullptr, m_ConstantBuffer.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Uniform buffer creation failed." << std::endl;

		return false;
	}

	D3D11_BUFFER_DESC pointLightBufferDesc{};
	pointLightBufferDesc.ByteWidth = MAX_LIGHTS * sizeof(PointLightDesc);
	pointLightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	pointLightBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	pointLightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	pointLightBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	pointLightBufferDesc.StructureByteStride = sizeof(PointLightDesc);

	res = device->CreateBuffer(&pointLightBufferDesc, nullptr, m_PointLightStructuredBuffer.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Point light structured buffer creation failed!" << std::endl;

		return false;
	}

	res = device->CreateShaderResourceView(m_PointLightStructuredBuffer.Get(), nullptr, m_PointLightSrv.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Point light shader resource view creation failed!" << std::endl;

		return false;
	}

	D3D11_BUFFER_DESC dirLightBufferDesc{};
	dirLightBufferDesc.ByteWidth = MAX_LIGHTS * sizeof(DirectionalLightDesc);
	dirLightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	dirLightBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	dirLightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	dirLightBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	dirLightBufferDesc.StructureByteStride = sizeof(DirectionalLightDesc);

	res = device->CreateBuffer(&dirLightBufferDesc, nullptr, m_DirectionalLightStructuredBuffer.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Directional light structured buffer creation failed!" << std::endl;

		return false;
	}

	res = device->CreateShaderResourceView(m_DirectionalLightStructuredBuffer.Get(), nullptr, m_DirectionalLightSrv.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Directional light shader resource view creation failed!" << std::endl;

		return false;
	}

	D3D11_BUFFER_DESC spotlightBufferDesc{};
	spotlightBufferDesc.ByteWidth = MAX_LIGHTS * sizeof(SpotlightDesc);
	spotlightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	spotlightBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	spotlightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	spotlightBufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	spotlightBufferDesc.StructureByteStride = sizeof(SpotlightDesc);

	res = device->CreateBuffer(&spotlightBufferDesc, nullptr, m_SpotlightStructuredBuffer.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Point light structured buffer creation failed!" << std::endl;

		return false;
	}

	res = device->CreateShaderResourceView(m_SpotlightStructuredBuffer.Get(), nullptr, m_SpotlightSrv.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Point light shader resource view creation failed!" << std::endl;

		return false;
	}

	D3D11_BUFFER_DESC particleBufferDesc{};
	particleBufferDesc.ByteWidth = sizeof(ParticleUniformBuffer);
	particleBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	particleBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	particleBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	res = device->CreateBuffer(&particleBufferDesc, nullptr, m_ParticleBuffer.ReleaseAndGetAddressOf());

	if (FAILED(res))
	{
		std::cerr << "GameSceneColorPass: Particle buffer creation failed!" << std::endl;

		return false;
	}

	m_DummyDiff = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"dummyDiff.jpg");
	m_DummyDiff->SetTextureType(TEX_DIFFUSE);

	m_DummySpec = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"dummySpec.jpg");
	m_DummySpec->SetTextureType(TEX_SPECULAR);

	m_DummyNorm = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"dummyNorm.png");
	m_DummyNorm->SetTextureType(TEX_NORMAL);

	return true;
}

PipelineData<D3D11RenderTarget*> GameSceneColorPassStageOvr::Execute(const std::vector<RenderComponent*>& data,
                                                                     const PipelineData<D3D11RenderTarget*>& tdata) noexcept
{

	// Return the render target so that the next stage of the pipeline can process it if needed.
	return PipelineData<D3D11RenderTarget*>{ &m_ColorRenderTarget };
}
