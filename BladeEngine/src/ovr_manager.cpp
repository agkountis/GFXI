#include <OVR/OVR_CAPI_D3D.h>
#ifdef BLADE_BUILD_OVR

#include "ovr_manager.h"
#include "trace.h"
#include "math_utils.h"
#include "engine_context.h"
#include "windowing_service.h"

namespace Blade
{
	bool OvrManager::Initialize() noexcept
	{
		if (OVR_FAILURE(ovr_Initialize(nullptr)))
		{
			BLADE_ERROR("Failed to initialize Oculus Rift.");
			return false;
		}

		if (OVR_FAILURE(ovr_Create(&m_Session, &m_GraphicsLuid)))
		{
			BLADE_ERROR("Failed to create OVR session.");
			return false;
		}

		if (!G_GAPIContext.Create(reinterpret_cast<LUID*>(&m_GraphicsLuid)))
		{
			BLADE_ERROR("Failed to initialize the engine's Graphics Context.");
			return false;
		}

		m_HmdDesc = ovr_GetHmdDesc(m_Session);

		for (int eye = 0; eye < 2; ++eye)
		{
			ovrSizei idealSize = ovr_GetFovTextureSize(m_Session, static_cast<ovrEyeType>(eye), m_HmdDesc.DefaultEyeFov[eye], 1.0f);
			m_EyeTextures[eye] = new OculusTexture();
			if (!m_EyeTextures[eye]->Initialize(m_Session, idealSize.w, idealSize.h))
			{
				return false;
			}

#ifdef BLADE_BUILD_D3D
			DXGI_FORMAT format = DXGI_FORMAT_D32_FLOAT;
			D3D11_TEXTURE2D_DESC dsDesc;
			dsDesc.Width = idealSize.w;
			dsDesc.Height = idealSize.h;
			dsDesc.MipLevels = 1;
			dsDesc.ArraySize = 1;
			dsDesc.Format = format;
			dsDesc.SampleDesc.Count = 1;
			dsDesc.SampleDesc.Quality = 0;
			dsDesc.Usage = D3D11_USAGE_DEFAULT;
			dsDesc.CPUAccessFlags = 0;
			dsDesc.MiscFlags = 0;
			dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

			ID3D11Texture2D* Tex;
			G_GAPIContext.GetDevice()->CreateTexture2D(&dsDesc, nullptr, &Tex);
			G_GAPIContext.GetDevice()->CreateDepthStencilView(Tex, nullptr, m_EyeDepthStencilViews[eye].ReleaseAndGetAddressOf());
			Tex->Release();
#endif

			m_EyeRenderViewport[eye].Pos.x = 0;
			m_EyeRenderViewport[eye].Pos.y = 0;
			m_EyeRenderViewport[eye].Size = idealSize;

			if (!m_EyeTextures[eye]->GetOvrTextureChain())
			{
				return false;
			}
		}

		ovr_SetTrackingOriginType(m_Session, ovrTrackingOrigin_FloorLevel);

		return true;
	}

	void OvrManager::CalculateEyePoses() noexcept
	{
		m_EyeRenderDesc[0] = ovr_GetRenderDesc(m_Session, ovrEye_Left, m_HmdDesc.DefaultEyeFov[0]);
		m_EyeRenderDesc[1] = ovr_GetRenderDesc(m_Session, ovrEye_Right, m_HmdDesc.DefaultEyeFov[1]);

		// Get both eye poses simultaneously, with IPD offset already included.
		ovrVector3f HmdToEyeOffset[2] = { m_EyeRenderDesc[0].HmdToEyeOffset, m_EyeRenderDesc[1].HmdToEyeOffset };

		ovr_GetEyePoses(m_Session, m_FrameIndex, ovrTrue, HmdToEyeOffset, m_EyePoses, &m_SesnorSampleTime);
	}

	void OvrManager::BindRenderTarget(int eye) const noexcept
	{
#ifdef BLADE_BUILD_D3D
		ID3D11RenderTargetView* rtv{ m_EyeTextures[eye]->GetRenderTargetView() };
		G_GAPIContext.GetDeviceContext()->OMSetRenderTargets(1, &rtv, m_EyeDepthStencilViews[eye].Get());
#endif
	}

	void OvrManager::ClearRenderTarget(int eye, const Vec4f& color) const noexcept
	{
#ifdef BLADE_BUILD_D3D
		G_GAPIContext.GetDeviceContext()->ClearRenderTargetView(m_EyeTextures[eye]->GetRenderTargetView(), &color[0]);
		G_GAPIContext.GetDeviceContext()->ClearDepthStencilView(m_EyeDepthStencilViews[eye].Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
#endif
	}

	OvrXformData OvrManager::GetOvrXformDataPerEye(int eye, float nearP, float farP, float translationScalingFactor) const noexcept
	{
		OvrXformData data;

#ifdef BLADE_BUILD_D3D
		Quatf eyeQuat{ m_EyePoses[eye].Orientation.w, m_EyePoses[eye].Orientation.x,
			m_EyePoses[eye].Orientation.y, -m_EyePoses[eye].Orientation.z };

		eyeQuat = MathUtils::Normalize(eyeQuat);

		Vec3f eyePos{ -m_EyePoses[eye].Position.x * translationScalingFactor,
			-m_EyePoses[eye].Position.y * translationScalingFactor,
			m_EyePoses[eye].Position.z * translationScalingFactor };

		data.view = MathUtils::Rotate(data.view, eyeQuat);
		data.view = MathUtils::Translate(data.view, eyePos);

		ovrMatrix4f proj = ovrMatrix4f_Projection(m_EyeRenderDesc[eye].Fov, nearP, farP, ovrProjection_LeftHanded);
		memcpy(&data.projection[0], proj.M, 16 * sizeof(float));

		data.projection = MathUtils::Transpose(data.projection);

		Recti rect{ m_EyeRenderViewport[eye].Pos.x, m_EyeRenderViewport[eye].Pos.y, m_EyeRenderViewport[eye].Size.w, m_EyeRenderViewport[eye].Size.h };
		data.viewport = Viewport{ rect, 0.0, 1.0 };
#endif

		return data;
	}

	void OvrManager::CommitOvrTexture(int eye) const noexcept
	{
		m_EyeTextures[eye]->Commit();
	}

	void OvrManager::SubmitOvrFrame() noexcept
	{
		// Initialize our single full screen Fov layer.
		ovrLayerEyeFov ld = {};
		ld.Header.Type = ovrLayerType_EyeFov;
		ld.Header.Flags = 0;

		for (int eye = 0; eye < 2; ++eye)
		{
			ld.ColorTexture[eye] = m_EyeTextures[eye]->GetOvrTextureChain();
			ld.Viewport[eye] = m_EyeRenderViewport[eye];
			ld.Fov[eye] = m_HmdDesc.DefaultEyeFov[eye];
			ld.RenderPose[eye] = m_EyePoses[eye];
			ld.SensorSampleTime = m_SesnorSampleTime;
		}

		ovrLayerHeader* layers = &ld.Header;
		ovrResult result = ovr_SubmitFrame(m_Session, m_FrameIndex, nullptr, &layers, 1);

		++m_FrameIndex;
	}

	ovrGraphicsLuid* OvrManager::GetOvrGraphicsLuidPtr() noexcept
	{
		return &m_GraphicsLuid;
	}

	const ovrSessionStatus& OvrManager::GetOvrSessionStatus() noexcept
	{
		ovr_GetSessionStatus(m_Session, &m_SessionStatus);
		return m_SessionStatus;
	}

	bool OvrManager::CreateMirrorTexture(int windowIndex) noexcept
	{
		Vec2i winSize{ WindowingService::GetWindow(windowIndex)->GetSize() };
		ovrMirrorTextureDesc mirrorTextureDesc{};
		mirrorTextureDesc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
		mirrorTextureDesc.Width = winSize.x;
		mirrorTextureDesc.Height = winSize.y;

		ovrResult result{ ovr_CreateMirrorTextureDX(m_Session, G_GAPIContext.GetDevice(), &mirrorTextureDesc, &m_MirrorTexture) };

		if (!OVR_SUCCESS(result))
		{
			BLADE_ERROR("Failed to create the OVR mirror texture.");
			return false;
		}

		return true;
	}

	void OvrManager::RenderMirrorTexture() const noexcept
	{
#ifdef BLADE_BUILD_D3D
		ID3D11Texture2D* tex = nullptr;
		ovr_GetMirrorTextureBufferDX(m_Session, m_MirrorTexture, IID_PPV_ARGS(&tex));

		ID3D11Texture2D* backbuffer = G_GAPIContext.GetBackBuffer();
		G_GAPIContext.GetDeviceContext()->CopyResource(backbuffer, tex);
		tex->Release();
#endif
	}
}

#endif //BLADE_BUILD_OVR
