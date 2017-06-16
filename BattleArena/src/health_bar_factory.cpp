#include "health_bar_factory.h"

#include "entity.h"
#include "render_component.h"
#include "mesh_utils.h"
#include "resource_manager.h"
#include "engine_context.h"
#include "game_scene_color_pass.h"
#include "pipeline.h"
#include "d3d/D3D11_texture.h"

#include "game_scene.h"

#include <iostream>

using namespace Blade;

HealthBar * HealthBarFactory::CreateHealthBar(Blade::Entity* parent, int maxHealthValue)
{

	Entity* emptyBar = new Entity(parent->GetName() + " empty bar");
	Entity* fullBar = new Entity(parent->GetName() + " full bar");

	emptyBar->SetPosition(Vec3f(0, 4, 0));
	fullBar->SetPosition(Vec3f(0, 4, 0));

	emptyBar->SetScale(Vec3f(4, 0.95f, 0.95f));
	fullBar->SetScale(Vec3f(4.01f, 1, 1));
	HealthBar* hb = new HealthBar(parent, emptyBar, fullBar, maxHealthValue);

	Mesh* cube{ MeshUtils::GenerateCube(1.0f,VertexWinding::CLOCKWISE) };
	//Register the resource to the manager, so it manages it's lifetime(memory).
	G_ResourceManager.RegisterResource(cube, L"BarCube");

	Texture* tex = G_ResourceManager.Get<D3D11Texture>(TEXTURE_PATH + L"plainWhite.png");
	tex->SetTextureType(TEX_DIFFUSE);

	Material material;
	material.diffuse = Vec4f{ 1.0f, 0.0f, 0.1f, 0.5f };
	material.blendState = Blade::RenderStateType::BS_BLEND_ALPHA;
	material.specular = Vec4f{ 0.0f, 0.0f, 0.0f, 60.0f }; //the w value is the shininess.
	material.textures[TEX_DIFFUSE] =tex;
	
	RenderComponent* rc{ new RenderComponent{emptyBar } };
	rc->SetMesh(G_ResourceManager.Get<Mesh>(L"BarCube"));
	rc->SetMaterial(material);

	Material material2;
	material2.diffuse = Vec4f{ 0.0f, 1.0f, 0.1f, 1.0f };
	material2.specular = Vec4f{ 0.0f, 0.0f, 0.0f, 60.0f }; //the w value is the shininess.
	material2.textures[TEX_DIFFUSE] = tex;

	rc = new RenderComponent{ fullBar } ;
	rc->SetMesh(G_ResourceManager.Get<Mesh>(L"BarCube"));
	rc->SetMaterial(material2);

	return hb;
}
