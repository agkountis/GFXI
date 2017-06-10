#ifndef BLADE_OCULUS_TEXTURE_D3D_H_
#define BLADE_OCULUS_TEXTURE_D3D_H_

#ifdef BLADE_BUILD_OVR

#include <OVR/OVR_CAPI.h>
#include "D3D/D3D11.h"
#include <vector>

namespace Blade
{
	class OculusTextureD3D
	{
	private:
		ovrSession m_Session;
		ovrTextureSwapChain m_TextureChain;
		std::vector<ID3D11RenderTargetView*> m_RenderTargetViews;

	public:
		OculusTextureD3D();

		bool Initialize(ovrSession session, int sizeW, int sizeH);

		~OculusTextureD3D();

		ID3D11RenderTargetView* GetRenderTargetView();

		ovrTextureSwapChain GetOvrTextureChain() const noexcept;

		void Commit() const;
	};
}

#endif //BLADE_BUILD_OVR

#endif //BLADE_OCULUS_TEXTURE_D3D_H_
