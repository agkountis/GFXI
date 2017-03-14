#include "d3d/D3D11_shader_program.h"
#include "d3d/D3D11_context.h"
#include "d3d/D3D11_shader.h"
#include "resource_manager.h"
#include "vertex.h"
#include "engine_context.h"

namespace Blade
{
	bool D3D11ShaderProgram::Create(unsigned int input_layout_mask,
	                                const std::wstring& vs,
	                                const std::wstring& fs,
	                                const std::wstring& hs,
	                                const std::wstring& ds,
	                                const std::wstring& gs) noexcept
	{
		D3D11Context* GAPI_context{ EngineContext::get_GAPI_context() };

		ID3D11Device* device{ GAPI_context->GetDevice() };

		if (!vs.empty())
		{
			SetShader(ResourceManager::Get<D3D11Shader>(SHADER_PATH + vs), VERTEX_SHADER);

			D3D11Shader* shader{ GetShader(VERTEX_SHADER) };
			ID3DBlob* blob{ shader->GetBlob() };

			HRESULT res{ 0 };
			res = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_VertexShader.ReleaseAndGetAddressOf());
			if (FAILED(res))
			{
				std::cerr << "Vertex shader creation failed! Aborting ShaderProgram creation." << std::endl;
				return false;
			}

			std::vector<D3D11_INPUT_ELEMENT_DESC> input;

			if (input_layout_mask & IL_POSITION)
			{
				input.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, position), D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			if (input_layout_mask & IL_NORMAL)
			{
				input.push_back({ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, normal), D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			if (input_layout_mask & IL_TANGENT)
			{
				input.push_back({ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, tangent), D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			if (input_layout_mask & IL_TEXCOORD)
			{
				input.push_back({ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, texcoord), D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			if (input_layout_mask & IL_COLOR)
			{
				input.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			res = device->CreateInputLayout(input.data(), input.size(), blob->GetBufferPointer(), blob->GetBufferSize(), m_InputLayout.ReleaseAndGetAddressOf());

			if (FAILED(res))
			{
				std::cerr << "Input layout creation failed! Aborting ShaderProgram creation." << std::endl;
				return false;
			}
		}
		else
		{
			std::cerr << "Failed to create shader program. Please provide at least a vertex shader file name!" << std::endl;
			return false;
		}

		if (!hs.empty())
		{
			SetShader(ResourceManager::Get<D3D11Shader>(SHADER_PATH + hs), HULL_SHADER);

			D3D11Shader* shader{ GetShader(DOMAIN_SHADER) };

			ID3DBlob* blob{ shader->GetBlob() };

			HRESULT res{ 0 };
			res = device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_HullShader.ReleaseAndGetAddressOf());
			if (FAILED(res))
			{
				std::cerr << "Hull shader creation failed!" << std::endl;
				return false;
			}
		}

		if (!ds.empty())
		{
			SetShader(ResourceManager::Get<D3D11Shader>(SHADER_PATH + ds), DOMAIN_SHADER);

			D3D11Shader* shader{ GetShader(DOMAIN_SHADER) };

			ID3DBlob* blob{ shader->GetBlob() };

			HRESULT res{ 0 };
			res = device->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_DomainShader.ReleaseAndGetAddressOf());
			if (FAILED(res))
			{
				std::cerr << "Domain shader creation failed!" << std::endl;
				return false;
			}
		}

		if (!gs.empty())
		{
			SetShader(ResourceManager::Get<D3D11Shader>(SHADER_PATH + gs), GEOMETRY_SHADER);

			D3D11Shader* shader{ GetShader(GEOMETRY_SHADER) };

			ID3DBlob* blob{ shader->GetBlob() };

			HRESULT res{ 0 };
			res = device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_GeometryShader.ReleaseAndGetAddressOf());
			if (FAILED(res))
			{
				std::cerr << "Geometry shader creation failed!" << std::endl;
				return false;
			}
		}

		if (!fs.empty())
		{
			SetShader(ResourceManager::Get<D3D11Shader>(SHADER_PATH + fs), FRAGMENT_SHADER);

			D3D11Shader* shader{ GetShader(FRAGMENT_SHADER) };

			ID3DBlob* blob{ shader->GetBlob() };

			HRESULT res{ 0 };
			res = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, m_PixelShader.ReleaseAndGetAddressOf());
			if (FAILED(res))
			{
				std::cerr << "Fragment shader creation failed!" << std::endl;
				return false;
			}
		}

		return true;
	}

	void D3D11ShaderProgram::Bind() const noexcept
	{
		D3D11Context* context{ EngineContext::get_GAPI_context() };

		ID3D11DeviceContext* device_context{ context->GetDeviceContext() };

		device_context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		device_context->IASetInputLayout(m_InputLayout.Get());

		device_context->HSSetShader(m_HullShader.Get(), nullptr, 0);

		device_context->DSSetShader(m_DomainShader.Get(), nullptr, 0);

		device_context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);

		device_context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}
}
