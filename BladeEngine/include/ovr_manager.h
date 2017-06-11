#ifndef BLADE_OVR_MANAGER_H_
#define BLADE_OVR_MANAGER_H_

#ifdef BLADE_BUILD_OVR

#include "oculus_texture.h"
#include "types.h"
#include "viewport.h"

#ifdef BLADE_BUILD_D3D
#include "D3D/d3d11.h"
#endif

namespace Blade
{
	struct OvrXformData
	{
		Mat4f projection;
		Mat4f view;
		Viewport viewport;
	};

	class OvrManager
	{
	private:
		ovrSession m_Session{ nullptr };
		ovrGraphicsLuid m_GraphicsLuid;

		ovrHmdDesc m_HmdDesc;
		ovrRecti m_EyeRenderViewport[2];

		ovrEyeRenderDesc m_EyeRenderDesc[2];
		ovrPosef m_EyePoses[2];

		ovrSessionStatus m_SessionStatus;

		OculusTexture* m_EyeTextures[2];

#ifdef BLADE_BUILD_D3D
		ComPtr<ID3D11DepthStencilView> m_EyeDepthStencilViews[2];
#endif

		long long m_FrameIndex{ 0 };

		double m_SesnorSampleTime{ 0.0 };

	public:

		bool Initialize() noexcept;

		void CalculateEyePoses() noexcept;

		void BindRenderTarget(int eye) const noexcept;

		void ClearRenderTarget(int eye, const Vec4f& color) const noexcept;

		OvrXformData GetOvrXformDataPerEye(int eye, float nearP, float farP, float translationScalingFactor = 1.0f) const noexcept;

		void CommitOvrTexture(int eye) const noexcept;

		void SubmitOvrFrame() noexcept;

		ovrGraphicsLuid* GetOvrGraphicsLuidPtr() noexcept;

		const ovrSessionStatus& GetOvrSessionStatus() noexcept;
	};
}

#endif //BLADE_BUILD_OVR

#endif //BLADE_OVR_MANAGER_H_
