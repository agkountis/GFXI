#include "battle_arena_application.h"
#include "scene_manager.h"
#include "windowing_types.h"
#include "windowing_service.h"
#include "shader_program_manager.h"
#include "game_scene.h"
#include "multiplayer.h"
#include "trace.h"
#include "assimp_utils.h"
#include "networked_lobby_scene.h"

using namespace Blade;

// Static event callbacks ---------------------------------------------------------------
static void Reshape(int x, int y)
{
	//TODO: Called when window size changes.

}

static void KeyDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: //esc
		G_Application.SetTermination(true);
		break;
	default:
		break;
	}

	G_SceneManager.OnKeyDown(key, x, y);
}

static void KeyUp(unsigned char key, int x, int y)
{
	G_SceneManager.OnKeyUp(key, x, y);
}

static void MouseClick(int button, bool state, int x, int y)
{
	G_SceneManager.OnMouseClick(button, state, x, y);
}

static void MouseMotion(int x, int y)
{
	G_SceneManager.OnMouseMotion(x, y);
}

static void PassiveMouseMotion(int x, int y)
{
	//TODO: Call SceneManager's passive mouse motion.
}

// --------------------------------------------------------------------------------------

bool BattleArenaApplication::Initialize(int* argc, char* argv[])
{
	if (!Application::Initialize(argc, argv))
	{
		return false;
	}

	BLADE_TRACE("BattleArenaApplication Initialization Starts!");

	SetLoadEntityCallback(AssimpUtils::LoadEntity);

	WindowFunctionCallbacks callbacks;
	callbacks.passive_motion_func = PassiveMouseMotion;
	callbacks.motion_func = MouseMotion;
	callbacks.mouse_func = MouseClick;
	callbacks.reshape_func = Reshape;
	callbacks.keyboard_func = KeyDown;
	callbacks.keyboard_up_func = KeyUp;
	callbacks.mouse_func = MouseClick;

	std::srand(time(nullptr));

	BLADE_TRACE("Creating Window!");

#ifdef BLADE_BUILD_OVR
	WindowingService::Create(L"BattleArena",
		Vec2i{ 1600, 900 },
		Vec2i{},
		true,
		false,
		true,
		true,
		true,
		1,
		callbacks);

	if (!G_OvrManager.CreateMirrorTexture(0))
	{
		return false;
	}
#else
	WindowingService::Create(L"BattleArena",
		Vec2i{ 1600, 900 },
		Vec2i{},
		true,
		false,
		true,
		true,
		true,
		4,
		callbacks);
#endif


	ShaderProgramDesc sdrProgDesc;
	sdrProgDesc.name = "render_texture_sdrprog";
	sdrProgDesc.inputLayoutMask = IL_POSITION | IL_TEXCOORD;
	sdrProgDesc.vertexShader = L"render_texture.vs.hlsl";
	sdrProgDesc.fragmentShader = L"render_texture.ps.hlsl";

	if (!G_ShaderProgramManager.Create(sdrProgDesc))
	{
		return false;
	}

	sdrProgDesc.name = "default_sdrprog";
	sdrProgDesc.inputLayoutMask = IL_POSITION | IL_NORMAL | IL_TANGENT | IL_TEXCOORD;
	sdrProgDesc.vertexShader = L"default.vs.hlsl";
	sdrProgDesc.fragmentShader = L"default.ps.hlsl";

	if (!G_ShaderProgramManager.Create(sdrProgDesc))
	{
		return false;
	}

	sdrProgDesc.name = "particles_sdrprog";
	sdrProgDesc.inputLayoutMask = IL_POSITION | IL_TEXCOORD;
	sdrProgDesc.vertexShader = L"particles.vs.hlsl";
	sdrProgDesc.fragmentShader = L"particles.ps.hlsl";

	if (!G_ShaderProgramManager.Create(sdrProgDesc))
	{
		return false;
	}

	BLADE_TRACE("Allocating and pusing the GameScreen into the ScreenManager!");
	
	if (!G_SceneManager.PushScene(std::make_unique<NetworkedLobbyScene>()))
	{
		return false;
	}

	BLADE_TRACE("BattleArenaApplication Initialization Successfull!");
	return true;
}

void BattleArenaApplication::Update() noexcept
{
	G_SceneManager.Update(GetDelta(), GetMsec());
}

void BattleArenaApplication::Draw() const noexcept
{
	G_SceneManager.Draw();

	WindowingService::SwapBuffers(1);
}

int BattleArenaApplication::Run() noexcept
{
	MSG msg;

	while (!ShouldTerminate())
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (WM_QUIT == msg.message)
			{
				break;
			}
		}
		else
		{
			Update();
			Draw();
		}
	}

	return 0;
}
