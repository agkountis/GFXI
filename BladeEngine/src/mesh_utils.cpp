#include "mesh_utils.h"
#include "math_utils.h"

namespace Blade
{
	namespace MeshUtils
	{
		Mesh* GenerateCube(float size, VertexWinding vertex_winding) noexcept
		{
			Mesh* m{ new Mesh };

			float half_size{ size / 2.0f };

			//front
			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			//right
			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, -half_size, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, -half_size, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 0.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, half_size, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 0.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, half_size, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 0.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			//left
			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, half_size, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, half_size, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, -half_size, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, -half_size, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			//back
			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});
			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 0.0f ,1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});
			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});
			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, half_size, 1.0f },
					Vec4f{ 0.0f, 0.0f, 1.0f, 1.0f },
					Vec4f{ -1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			//top
			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, half_size, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, half_size, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			//bottom
			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, -1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, half_size, 1.0f },
					Vec4f{ 0.0f, -1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 0.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, -half_size, 1.0f },
					Vec4f{ 0.0f, -1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, 0.0f, 0.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, half_size, 1.0f },
					Vec4f{ 0.0f, -1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->GenerateIndices(vertex_winding);

			if (vertex_winding == VertexWinding::ANTICLOCKWISE)
			{
				FlipNormals(m);
			}

			m->InitiazeBufferObjects();

			return m;
		}

		Mesh* GenerateUvSphere(float radius, int slices, int stacks, float urange, float vrange) noexcept
		{
			Mesh* m{ new Mesh };

			Vertex tmp_vert;

			if (slices < 4)
			{
				slices = 4;
			}

			if (stacks < 2)
			{
				stacks = 2;
			}

			int u_verts = slices + 1;
			int v_verts = stacks + 1;

			float du = urange / static_cast<float>(u_verts - 1);
			float dv = vrange / static_cast<float>(v_verts - 1);

			float u = 0.0;

			for (int i = 0; i < u_verts; i++)
			{
				float theta = (u * 2.0 * MathUtils::PI_F) * urange;

				float v = 0.0;
				for (int j = 0; j < v_verts; j++)
				{
					float phi = v * MathUtils::PI_F * vrange;
					tmp_vert.position = Vec4f{ MathUtils::SphericalToCartesian(theta, phi, radius), 1.0f };
					tmp_vert.normal = tmp_vert.position;
					tmp_vert.tangent = MathUtils::Normalize(
						Vec4f{
							(MathUtils::SphericalToCartesian(theta + 1.0, MathUtils::PI_F / 2.0f)
								- MathUtils::SphericalToCartesian(theta - 1.0, MathUtils::PI_F / 2.0f))
							, 1.0f
						});

					tmp_vert.texcoord.x = u * urange;
					tmp_vert.texcoord.y = v * vrange;

					if (i < slices && j < stacks)
					{
						int idx = i * v_verts + j;

						int idx1 = idx;
						int idx2 = idx + 1;
						int idx3 = idx + v_verts + 1;

						int idx4 = idx;
						int idx5 = idx + v_verts + 1;
						int idx6 = idx + v_verts;

						m->AddIndex(idx1);
						m->AddIndex(idx2);
						m->AddIndex(idx3);
						m->AddIndex(idx4);
						m->AddIndex(idx5);
						m->AddIndex(idx6);
					}

					m->AddVertex(tmp_vert);

					v += dv;
				}
				u += du;
			}

			m->InitiazeBufferObjects();
			return m;
		}

		Mesh* GeneratePlaneXy(float size) noexcept
		{
			Mesh* m{ new Mesh };

			float half_size{ size / 2.0f };

			//front
			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, -half_size, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 0.0f },
					Vec4f{},
					Vec4f{ 0.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ -half_size, half_size, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 0.0f },
					Vec4f{},
					Vec4f{ 0.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, -half_size, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 0.0f },
					Vec4f{},
					Vec4f{ 1.0f, 1.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->AddVertex(
				Vertex{
					Vec4f{ half_size, half_size, 0.0f, 1.0f },
					Vec4f{ 0.0f, 0.0f, -1.0f, 0.0f },
					Vec4f{},
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f },
					Vec4f{ 1.0f, 0.0f, 0.0f, 1.0f }
				});

			m->GenerateIndices(VertexWinding::CLOCKWISE);
			m->InitiazeBufferObjects();
			return m;
		}

		void FlipNormals(const Mesh* m) noexcept
		{
			Vertex* varr{ m->GetVertexData() };

			for (int i = 0; i < m->GetVertexCount(); ++i)
			{
				varr[i].normal = -varr[i].normal;
			}
		}
	}
}
