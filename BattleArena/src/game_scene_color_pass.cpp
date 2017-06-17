#include "game_scene_color_pass.h"
#include "render_state_manager.h"
#include "shader_program_manager.h"
#include "engine_context.h"
#include "windowing_service.h"
#include <iostream>
#include "math_utils.h"
#include "entity.h"
#include "d3d/D3D11_texture.h"
#include "uniform_buffers.h"

using namespace Blade;


void GameSceneColorPassStage::DisplayToScreen() const
{
	D3D11Context& ctx{ G_GAPIContext };

	ID3D11DeviceContext* dev_con{ ctx.GetDeviceContext() };

	dev_con->OMSetRenderTargets(1, ctx.GetGetAddressOfDefaultRenderTargetView(), ctx.GetDefaultDepthStencilView());

	Vec4f cl_col{ 0.0, 0.0, 0.0, 0.0 };
	dev_con->ClearRenderTargetView(ctx.GetDefaultRenderTargetView(), &cl_col[0]);
	dev_con->ClearDepthStencilView(ctx.GetDefaultDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	G_ShaderProgramManager.Get("render_texture_sdrprog")->Bind();

	ID3D11ShaderResourceView* srv{ m_ColorRenderTarget.GetColorAttachment() };
	dev_con->PSSetShaderResources(0, 1, &srv);
	dev_con->PSSetSamplers(0, 1, m_SamplerLinearWrap.GetAddressOf());

	G_RenderStateManager.Set(RenderStateType::RS_DRAW_SOLID);
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

void GameSceneColorPassStage::SetBrightness(float brightness)
{
	m_Brightness = brightness;
}

PipelineData<D3D11RenderTarget*> GameSceneColorPassStage::Execute(const std::vector<RenderComponent*>& data,
	const PipelineData<D3D11RenderTarget*>& tdata) noexcept
{
	//Bind the render target.
	m_ColorRenderTarget.Bind(RenderTargetBindType::COLOR_AND_DEPTH);

	//Define a clear color and clear the color buffer and depth stencil.
	Vec4f clearColor{ 0.0f, 0.0f, 0.0f, 1.0f };
	m_ColorRenderTarget.Clear(&clearColor[0]);

	//Get the window size.
	Vec2i winSize{ WindowingService::GetWindow(0)->GetSize() };

	//Get the device context.
	ID3D11DeviceContext* deviceContext{ G_GAPIContext.GetDeviceContext() };

	//Bind the requested shader program.
	G_ShaderProgramManager.Get("default_sdrprog")->Bind();

	//Set the linear wrap texture sampler.
	deviceContext->PSSetSamplers(0, 1, m_SamplerLinearWrap.GetAddressOf());

	//Get the active camera projection matrix.
	Mat4f p{ G_CameraSystem.GetActiveCameraProjectionMatrtix() };

	//Get the active camera view matrix.
	Mat4f v{ G_CameraSystem.GetActiveCameraViewMatrix() };

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
		uniforms.pad = m_Brightness;
		

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

		//Set the viewport of the active camera.
		G_CameraSystem.GetActiveCameraViewport().Set();

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

	//////////////////////////////////////////////////////////////////////////

#if !_DEBUG

	G_RenderStateManager.Set(RenderStateType::DSS_DEPTH_MASK_0);
	G_ShaderProgramManager.Get("particles_sdrprog")->Bind();

	auto emitters = G_ParticleSystem.GetEmitterComponents();

	for (auto emitter : emitters)
	{
		Texture* tex{ emitter->GetTexture() };

		tex->Bind();
		deviceContext->PSSetSamplers(0, 1, m_SamplerLinearWrap.GetAddressOf());

		G_RenderStateManager.Set(emitter->GetBlendStateType());

		auto particles = emitter->GetParticles();

		for (auto particle : particles)
		{
			Mat4f model;
			model = MathUtils::Translate(model, particle.position);
			Mat4f MV{ v * model };

			MV[0][0] = 1.0f;
			MV[0][1] = 0.0f;
			MV[0][2] = 0.0f;

			MV[1][0] = 0.0f;
			MV[1][1] = 1.0f;
			MV[1][2] = 0.0f;

			MV[2][0] = 0.0f;
			MV[2][1] = 0.0f;
			MV[2][2] = 1.0f;

			MV = MathUtils::Scale(MV, Vec3f{ particle.size });

			Mat4f MVP{ p * MV };

			ParticleUniformBuffer uniforms;
			uniforms.MVP = MathUtils::Transpose(MVP);
			uniforms.diffuse = particle.color;

			D3D11_MAPPED_SUBRESOURCE ms;

			deviceContext->Map(m_ParticleBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
			memcpy(ms.pData, &uniforms, sizeof(ParticleUniformBuffer));
			deviceContext->Unmap(m_ParticleBuffer.Get(), 0);

			deviceContext->VSSetConstantBuffers(0, 1, m_ParticleBuffer.GetAddressOf());
			deviceContext->PSSetConstantBuffers(0, 1, m_ParticleBuffer.GetAddressOf());

			Mesh* mesh = emitter->GetMesh();

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
		}
	}
	G_RenderStateManager.Set(RenderStateType::BS_BLEND_DISSABLED);
	G_RenderStateManager.Set(RenderStateType::DSS_DEPTH_MASK_1);
#endif // 
	//Unbind the render target.
	m_ColorRenderTarget.Unbind();

	//Display to the full screen quad.
	DisplayToScreen();

	// Return the render target so that the next stage of the pipeline can process it if needed.
	return PipelineData<D3D11RenderTarget*>{ &m_ColorRenderTarget };
}