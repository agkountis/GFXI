#ifndef BLADE_OCULUS_TEXTURE_D3D_H_
#define BLADE_OCULUS_TEXTURE_D3D_H_

#ifdef BLADE_BUILD_OVR

#include <OVR/OVR_CAPI.h>
#include "D3D/D3D11.h"
#include <vector>

namespace Blade
{
	/**
	 * \brief Represents a D3D implementation of an Oculus texture.
	 * \details This class can be used in two ways. Either as one texture encompassing
	 * both eyes, or as a texture per eye.
	 */
	class OculusTextureD3D
	{
	private:
		/**
		 * \brief The Oculus VR session pointer.
		 */
		ovrSession m_Session;

		/**
		 * \brief The Oculus VR specific swap chain structure for this texture.
		 */
		ovrTextureSwapChain m_TextureChain;

		/**
		 * \brief The render target views needed to access each texture in the swapchain.
		 */
		std::vector<ID3D11RenderTargetView*> m_RenderTargetViews;

	public:
		OculusTextureD3D();

		/**
		 * \brief Initializes the Oculus VR texture class.
		 * \param session The current Oculus VR session.
		 * \param sizeW The width of the texture.
		 * \param sizeH The height of the texture.
		 * \return TRUE on success, FALSE otherwise.
		 */
		bool Initialize(ovrSession session, int sizeW, int sizeH);

		~OculusTextureD3D();

		/**
		 * \brief Returns the current render target view available for modification.
		 * \return The current render target view available for modification in the swapchain.
		 */
		ID3D11RenderTargetView* GetRenderTargetView();

		/**
		 * \brief Returns the Oculus VR texture swap chain.
		 * \return The Oculus VR texture swap chain.
		 */
		ovrTextureSwapChain GetOvrTextureChain() const noexcept;

		/**
		 * \brief Commits the Oculus VR texture chain to the Oculus SDK for further processing.
		 * \details Use when rendering on the swapchain has finished.
		 */
		void Commit() const;
	};
}

#endif //BLADE_BUILD_OVR

#endif //BLADE_OCULUS_TEXTURE_D3D_H_
