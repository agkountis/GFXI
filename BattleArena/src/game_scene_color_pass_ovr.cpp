#include "game_scene_color_pass_ovr.h"
#include "trace.h"
#include "resource_manager.h"
#include "d3d/D3D11_texture.h"
#include "engine_context.h"
#include "uniform_buffers.h"
#include "OVR/OVR_CAPI_D3D.h"
#include "math_utils.h"
#include "entity.h"

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

void GameSceneColorPassStageOvr::ShutdownOvr() const noexcept
{
	ovr_DestroyTextureSwapChain(m_OvrData.session, m_OvrData.textureSwapChain);
	ovr_DestroyMirrorTexture(m_OvrData.session, m_OvrData.mirrorTexture);
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

#undef max
	int width{ m_OvrData.eyeResolution[ovrEye_Left].w + m_OvrData.eyeResolution[ovrEye_Right].w };
	int height{ std::max(m_OvrData.eyeResolution[ovrEye_Left].h, m_OvrData.eyeResolution[ovrEye_Right].h) };

	m_OvrData.textureSwapChain = nullptr;
	ovrTextureSwapChainDesc swapChainDesc{};
	swapChainDesc.Type = ovrTexture_2D;
	swapChainDesc.ArraySize = 1;
	swapChainDesc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.MipLevels = 1;
	swapChainDesc.SampleCount = 1;
	swapChainDesc.StaticImage = ovrFalse;
	swapChainDesc.MiscFlags = ovrTextureMisc_None;
	swapChainDesc.BindFlags = ovrTextureBind_DX_RenderTarget;

	ovrResult res{ ovr_CreateTextureSwapChainDX(m_OvrData.session, G_GAPIContext.GetDevice(), &swapChainDesc, &m_OvrData.textureSwapChain) };
	if (OVR_FAILURE(res))
	{
		BLADE_ERROR("Failed to create the OVR swapchain.");
		return false;
	}

	int count{ 0 };
	ovr_GetTextureSwapChainLength(m_OvrData.session, m_OvrData.textureSwapChain, &count);
	m_ColorRenderTargets.resize(count);

	for (int i = 0; i < count; ++i)
	{
		ID3D11Texture2D* tex{ nullptr };
		ovr_GetTextureSwapChainBufferDX(m_OvrData.session, m_OvrData.textureSwapChain, i, IID_PPV_ARGS(&tex));
		G_GAPIContext.GetDevice()->CreateRenderTargetView(tex, nullptr, &m_ColorRenderTargets[i]);
		tex->Release();
	}

	D3D11_TEXTURE2D_DESC depth_attachment_desc;
	depth_attachment_desc.Width = width;
	depth_attachment_desc.Height = height;
	depth_attachment_desc.MipLevels = 1;
	depth_attachment_desc.ArraySize = 1;
	depth_attachment_desc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	depth_attachment_desc.SampleDesc.Count = 1;
	depth_attachment_desc.SampleDesc.Quality = 0;

	depth_attachment_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_attachment_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	depth_attachment_desc.CPUAccessFlags = 0;
	depth_attachment_desc.MiscFlags = 0;

	ID3D11Texture2D* tex = nullptr;

	HRESULT hresult = G_GAPIContext.GetDevice()->CreateTexture2D(&depth_attachment_desc, nullptr, &tex);

	if (FAILED(hresult))
	{
		std::cerr << "Failed to create D3D11RenderTarget depth attachment!" << std::endl;
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC desc_dsv;
	desc_dsv.Flags = 0;
	desc_dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc_dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	desc_dsv.Texture2D.MipSlice = 0;

	hresult = G_GAPIContext.GetDevice()->CreateDepthStencilView(tex, &desc_dsv, &m_DepthStencilView);

	if (FAILED(hresult))
	{
		std::cerr << "Failed to create D3D11RenderTarget depth stencil view!" << std::endl;
		return false;
	}

	tex->Release();

	m_OvrData.mirrorTexture = nullptr;

	ovrMirrorTextureDesc mirrorTextureDesc{};
	mirrorTextureDesc.Format = OVR_FORMAT_R8G8B8A8_UNORM;
	mirrorTextureDesc.Width = width;
	mirrorTextureDesc.Height = height;

	res = ovr_CreateMirrorTextureDX(m_OvrData.session, G_GAPIContext.GetDevice(), &mirrorTextureDesc, &m_OvrData.mirrorTexture);
	if (OVR_FAILURE(res))
	{
		BLADE_ERROR("Failed to create OVR mirror texture.");
		return false;
	}

	m_OvrData.layer.ColorTexture[ovrEye_Left] = m_OvrData.textureSwapChain;
	m_OvrData.layer.ColorTexture[ovrEye_Right] = m_OvrData.textureSwapChain;

	ovrRecti leftEyeRect = {
		{ 0, 0 },
		{ width / 2, height }
	};

	ovrRecti rightEyeRect = {
		{ width / 2, 0 },
		{ width / 2, height }
	};

	m_OvrData.layer.Viewport[ovrEye_Left] = leftEyeRect;
	m_OvrData.layer.Viewport[ovrEye_Right] = rightEyeRect;

	return true;
}

void GameSceneColorPassStageOvr::CalculateEyePoses() noexcept
{
	double displayMidpointSeconds{ ovr_GetPredictedDisplayTime(m_OvrData.session, 0) };

	m_OvrData.layer.SensorSampleTime = ovr_GetTimeInSeconds();

	ovrTrackingState hmdState = ovr_GetTrackingState(m_OvrData.session, displayMidpointSeconds, ovrTrue);

	ovr_CalcEyePoses(hmdState.HeadPose.ThePose, m_OvrData.hmdToEyeViewOffset, m_OvrData.eyePoses);
}

const OvrXformData& GameSceneColorPassStageOvr::GetOvrXformDataPerEye(int eye) noexcept
{
	Recti rect{ Vec4f{ m_OvrData.layer.Viewport[eye].Pos.x,
		m_OvrData.layer.Viewport[eye].Pos.y,
		m_OvrData.layer.Viewport[eye].Size.w,
		m_OvrData.layer.Viewport[eye].Size.h } };

	m_OvrXformData.viewport = Viewport{ rect, 0.0f, 1.0f };
	/*-------------------------------------------------------------------------*/

	/*Calculate the Projection Matrix*/
	m_OvrXformData.projection = MathUtils::identityMatrix;

	ovrMatrix4f proj = ovrMatrix4f_Projection(m_OvrData.layer.Fov[eye], 0.01f, 1000.0f, ovrProjection_None);
	memcpy(&m_OvrXformData.projection[0], proj.M, 16 * sizeof(float));
	/*-------------------------------------------------------------------------*/

	/*Calculate the View Matrix*/
	m_OvrXformData.view = MathUtils::identityMatrix;

	Quatf q = Quatf{ m_OvrData.eyePoses[eye].Orientation.w, m_OvrData.eyePoses[eye].Orientation.x,
		m_OvrData.eyePoses[eye].Orientation.y, m_OvrData.eyePoses[eye].Orientation.z };

	q = MathUtils::Inverse(q);

	q = MathUtils::Normalize(q);

	m_OvrXformData.view = MathUtils::Rotate(m_OvrXformData.view, q);

	Vec3f t{ -m_OvrData.eyePoses[eye].Position.x, -m_OvrData.eyePoses[eye].Position.y, -m_OvrData.eyePoses[eye].Position.z };
	m_OvrXformData.view = MathUtils::Translate(m_OvrXformData.view, t);
	/*-------------------------------------------------------------------------*/
	//
	return m_OvrXformData;
}

void GameSceneColorPassStageOvr::BeginOvrFrame() noexcept
{
	m_CurrentRenderTargetIndex = 0;
	ovr_GetTextureSwapChainCurrentIndex(m_OvrData.session, m_OvrData.textureSwapChain, &m_CurrentRenderTargetIndex);

	G_GAPIContext.GetDeviceContext()->OMSetRenderTargets(1, &m_ColorRenderTargets[m_CurrentRenderTargetIndex], m_DepthStencilView);

	Vec4f col{ 0.3, 0.3, 0.3, 1.0 };
	G_GAPIContext.GetDeviceContext()->ClearRenderTargetView(m_ColorRenderTargets[m_CurrentRenderTargetIndex], &col[0]);
	G_GAPIContext.GetDeviceContext()->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
}

void GameSceneColorPassStageOvr::EndOvrFrame() noexcept
{
	D3D11Context& ctx{ G_GAPIContext };

	ID3D11DeviceContext* dev_con{ ctx.GetDeviceContext() };

	ID3D11DepthStencilView* null_dsv{ nullptr };
	ID3D11RenderTargetView* null_rtvs{ nullptr };
	dev_con->OMSetRenderTargets(1, &null_rtvs, null_dsv);

	dev_con->OMSetRenderTargets(1, ctx.GetGetAddressOfDefaultRenderTargetView(), ctx.GetDefaultDepthStencilView());

	ovr_CommitTextureSwapChain(m_OvrData.session, m_OvrData.textureSwapChain);
}

bool GameSceneColorPassStageOvr::SubmitOvrFrame() noexcept
{
	m_OvrData.layer.RenderPose[ovrEye_Left] = m_OvrData.eyePoses[ovrEye_Left];
	m_OvrData.layer.RenderPose[ovrEye_Right] = m_OvrData.eyePoses[ovrEye_Right];

	ovrLayerHeader* layerHeader{ &m_OvrData.layer.Header };

	ovrResult res{ ovr_SubmitFrame(m_OvrData.session, 0, &m_OvrData.viewScaleDesc, &layerHeader, 1) };

	return res == ovrSuccess;
}

// -------------------------------------------------------------------------------------


GameSceneColorPassStageOvr::GameSceneColorPassStageOvr(const std::string& name)
	: Blade::RenderPassStage{ name },
	  m_CurrentRenderTargetIndex{ 0 }
{
}

bool GameSceneColorPassStageOvr::Initialize()
{
	if (!InitializeOvr())
	{
		return false;
	}

	if (!InitializeOvrData())
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
	static bool isVisible{ true };

	if (isVisible)
	{
		CalculateEyePoses();

		BeginOvrFrame();

		//Get the device context.
		ID3D11DeviceContext* deviceContext{ G_GAPIContext.GetDeviceContext() };

		//Bind the requested shader program.
		G_ShaderProgramManager.Get("default_sdrprog")->Bind();

		//Set the linear wrap texture sampler.
		deviceContext->PSSetSamplers(0, 1, m_SamplerLinearWrap.GetAddressOf());

		//Get the active camera view matrix.
		Mat4f v{ G_CameraSystem.GetActiveCameraViewMatrix() };

		for (int eye = 0; eye < 2; ++eye)
		{
			OvrXformData xformData{ GetOvrXformDataPerEye(eye) };

			Mat4f p{ xformData.projection };

			v = xformData.view * v;

			xformData.viewport.Set();

			//Iterate through the render components.
			for (auto renderComponent : data)
			{
				//Get the model matrix from the Entity.
				Mat4f m{ renderComponent->GetParent()->GetXform() };

				//Calculate the ModelViewProjection matrix.
				Mat4f mvp{ p * v * m };

				//Calculate the ModelView matrix.
				Mat4f mv{ v * m };

				auto& lightSystem{ G_LightSystem };

				auto pointLights{ lightSystem.GetPointLightDescriptions() };

				if (!pointLights.empty())
				{
					D3D11_MAPPED_SUBRESOURCE pointLightMs;
					deviceContext->Map(m_PointLightStructuredBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pointLightMs);
					memcpy(pointLightMs.pData, pointLights.data(), pointLights.size() * sizeof(PointLightDesc));
					deviceContext->Unmap(m_PointLightStructuredBuffer.Get(), 0);
				}

				auto directionalLights{ lightSystem.GetDirectionalLightDescriptions() };

				if (!directionalLights.empty())
				{
					D3D11_MAPPED_SUBRESOURCE directionalLightMs;
					deviceContext->Map(m_DirectionalLightStructuredBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &directionalLightMs);
					memcpy(directionalLightMs.pData, directionalLights.data(), directionalLights.size() * sizeof(DirectionalLightDesc));
					deviceContext->Unmap(m_DirectionalLightStructuredBuffer.Get(), 0);
				}

				auto spotlights{ lightSystem.GetSpotlightDescriptions() };

				if (!spotlights.empty())
				{
					D3D11_MAPPED_SUBRESOURCE spotlightMs;
					deviceContext->Map(m_SpotlightStructuredBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &spotlightMs);
					memcpy(spotlightMs.pData, spotlights.data(), spotlights.size() * sizeof(SpotlightDesc));
					deviceContext->Unmap(m_SpotlightStructuredBuffer.Get(), 0);
				}

				deviceContext->VSSetShaderResources(0, 1, m_DirectionalLightSrv.GetAddressOf());
				deviceContext->VSSetShaderResources(1, 1, m_PointLightSrv.GetAddressOf());
				deviceContext->VSSetShaderResources(2, 1, m_SpotlightSrv.GetAddressOf());

				deviceContext->PSSetShaderResources(3, 1, m_DirectionalLightSrv.GetAddressOf());
				deviceContext->PSSetShaderResources(4, 1, m_PointLightSrv.GetAddressOf());
				deviceContext->PSSetShaderResources(5, 1, m_SpotlightSrv.GetAddressOf());

				//Fill up the uniform structure.
				UniformBuffer uniforms;
				uniforms.MVP = MathUtils::Transpose(mvp);
				uniforms.ITMV = MathUtils::Inverse(v);
				uniforms.MV = MathUtils::Transpose(mv);
				uniforms.V = MathUtils::Transpose(v);
				uniforms.pointLightCount = pointLights.size();
				uniforms.directionalLightCount = directionalLights.size();
				uniforms.spotlightCount = spotlights.size();

				//Get the material from the RenderComponent.
				Material material{ renderComponent->GetMaterial() };

				uniforms.diffuse = material.diffuse;
				uniforms.specular = material.specular;
				uniforms.textureMatrix = material.textureMatrix;

				// If the material has a diffuse texture bind it.
				if (material.textures[TEX_DIFFUSE])
				{
					material.textures[TEX_DIFFUSE]->Bind();
				}
				else
				{
					m_DummyDiff->Bind();
				}

				// If the material has a specular texture bind it.
				if (material.textures[TEX_SPECULAR])
				{
					material.textures[TEX_SPECULAR]->Bind();
				}
				else
				{
					m_DummySpec->Bind();
				}

				// If the material has a normal map texture bind it.
				if (material.textures[TEX_NORMAL])
				{
					material.textures[TEX_NORMAL]->Bind();
				}
				else
				{
					m_DummyNorm->Bind();
				}

				//Copy the data into the D3D11 constant buffer.
				D3D11_MAPPED_SUBRESOURCE ms;
				deviceContext->Map(m_ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
				memcpy(ms.pData, &uniforms, sizeof(UniformBuffer));
				deviceContext->Unmap(m_ConstantBuffer.Get(), 0);

				//Set the constant buffer to both the Vertex shader and the Pixel shader.
				deviceContext->VSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());
				deviceContext->PSSetConstantBuffers(0, 1, m_ConstantBuffer.GetAddressOf());

				//Get the Mesh from the Render component.
				Mesh* mesh{ renderComponent->GetMesh() };

				//Set the blend state of the RenderComponent's material
				G_RenderStateManager.Set(material.blendState);

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
				G_RenderStateManager.Set(RenderStateType::BS_BLEND_DISSABLED);
			}
		}

		G_RenderStateManager.Set(RenderStateType::BS_BLEND_DISSABLED);
		G_RenderStateManager.Set(RenderStateType::DSS_DEPTH_MASK_1);

		EndOvrFrame();
	}

	isVisible = SubmitOvrFrame();


	//TODO: Draw mirror texture here.

	// Return the render target so that the next stage of the pipeline can process it if needed.
	return PipelineData<D3D11RenderTarget*>{ nullptr };
}
