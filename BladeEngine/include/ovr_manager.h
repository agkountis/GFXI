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
	/**
	 * \brief Represents the transformation information provided by the Oculus Rift headset.
	 * \details Holds the projection and view matrices provided by the headset plus the appropriate viewport.
	 */
	struct OvrXformData
	{
		Mat4f projection;
		Mat4f view;
		Viewport viewport;
	};

	/**
	 * \brief A manager class that manages rendering to the Oculus Rift headset.
	 * \details Provides the interface to output images to the headset's screen.
	 */
	class OvrManager
	{
	private:
		/**
		 * \brief The current Oculus VR session.
		 */
		ovrSession m_Session{ nullptr };


		/**
		 * \brief The Local Unique Identifier of the graphics.
		 * \details Used to detect the corrent display adapter.
		 */
		ovrGraphicsLuid m_GraphicsLuid;

		/**
		 * \brief A struct that describes the Head Mounted Display.
		 */
		ovrHmdDesc m_HmdDesc;


		/**
		 * \brief The viewport of each eye.
		 */
		ovrRecti m_EyeRenderViewport[2];

		/**
		 * \brief Holds the rendering information for each eye.
		 */
		ovrEyeRenderDesc m_EyeRenderDesc[2];

		/**
		 * \brief Holds the poses (transformations) for each eye.
		 */
		ovrPosef m_EyePoses[2];

		/**
		 * \brief The status of the current Oculus VR session.
		 */
		ovrSessionStatus m_SessionStatus;

		/**
		 * \brief The textures for each eye.
		 */
		OculusTexture* m_EyeTextures[2];

		/**
		 * \brief The mirror texture to be displayed on the window
		 * while the user uses the headset.
		 */
		ovrMirrorTexture m_MirrorTexture{ nullptr };

#ifdef BLADE_BUILD_D3D
		/**
		 * \brief Depth stencil views for each eye.
		 */
		ComPtr<ID3D11DepthStencilView> m_EyeDepthStencilViews[2];
#endif

		/**
		 * \brief Index of the current frame.
		 */
		long long m_FrameIndex{ 0 };

		/**
		 * \brief The time the Oculus VR HMD sensor was sampled.
		 */
		double m_SesnorSampleTime{ 0.0 };

	public:

		/**
		 * \brief Initializes the OvrManager.
		 * \return TRUE if successful, FALSE otherwise.
		 */
		bool Initialize() noexcept;

		/**
		 * \brief Calculates the eye poses(transformations) for both eyes.
		 */
		void CalculateEyePoses() noexcept;

		/**
		 * \brief Binds the rendertarget corresponding to eye specified.
		 * \param eye The index of the current eye.
		 */
		void BindRenderTarget(int eye) const noexcept;

		/**
		 * \brief Clears the render target corresponding to the eye specified and clears it 
		 * with the specified color.
		 * \param eye The index of the current eye.
		 * \param color The clear color.
		 */
		void ClearRenderTarget(int eye, const Vec4f& color) const noexcept;

		/**
		 * \brief Gets the Oculus VR transformation data for the specified eye.
		 * \param eye The index of the current eye.
		 * \param nearP The near clipping plane.
		 * \param farP The far clipping plane.
		 * \param translationScalingFactor A scaling factor used to scale the view matrix provided by the Oculus SDK.
		 * \return The tranformation data for the specified eye.
		 */
		OvrXformData GetOvrXformDataPerEye(int eye, float nearP, float farP, float translationScalingFactor = 1.0f) const noexcept;

		/**
		 * \brief Commits the texture for the specified eye to the swap chain.
		 * \param eye The index of the current eye.
		 */
		void CommitOvrTexture(int eye) const noexcept;

		/**
		 * \brief Submits the current frame to the Oculus VR SDK for further processing.
		 */
		void SubmitOvrFrame() noexcept;

		/**
		 * \brief Returns the pointer to the graphics LUID member.
		 * \return The pointer to the graphics LUID.
		 */
		ovrGraphicsLuid* GetOvrGraphicsLuidPtr() noexcept;

		/**
		 * \brief Returns the Oculs VR session status.
		 * \return The Oculus VR session status.
		 */
		const ovrSessionStatus& GetOvrSessionStatus() noexcept;

		/**
		 * \brief Creates the mirror texture.
		 * \param windowIndex The inder of the current window in the WindowingService
		 * \return TRUE if sucessful, FALSE otherwise.
		 */
		bool CreateMirrorTexture(int windowIndex) noexcept;

		/**
		 * \brief Renders the mirror texture to the window.
		 */
		void RenderMirrorTexture() const noexcept;
	};
}

#endif //BLADE_BUILD_OVR

#endif //BLADE_OVR_MANAGER_H_
