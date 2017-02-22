#include "battle_arena_application.h"
#include "scene_manager.h"
#include "windowing_types.h"
#include "windowing_service.h"
#include "shader_program_manager.h"
#include "game_scene.h"

using namespace Blade;

// Static event callbacks ---------------------------------------------------------------
static void Reshape(int x, int y)
{
	//TODO: Called when window size changes.
}

static void KeyDown(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}

	SceneManager::OnKeyDown(key, x, y);
}

static void KeyUp(unsigned char key, int x, int y)
{
	SceneManager::OnKeyUp(key, x, y);
}

static void MouseClick(int button, bool state, int x, int y)
{
	SceneManager::OnMouseClick(button, state, x, y);
}

static void MouseMotion(int x, int y)
{
	SceneManager::OnMouseMotion(x, y);
}

static void PassiveMouseMotion(int x, int y)
{
	//TODO: Call SceneManager's passive mouse motion.
}

// --------------------------------------------------------------------------------------

BattleArenaApplication::~BattleArenaApplication()
{
}

bool BattleArenaApplication::Initialize(int* argc, char* argv[])
{
	if (!Application::Initialize(argc, argv))
	{
		return false;
	}

	WindowFunctionCallbacks callbacks;
	callbacks.passive_motion_func = PassiveMouseMotion;
	callbacks.motion_func = MouseMotion;
	callbacks.mouse_func = MouseClick;
	callbacks.reshape_func = Reshape;
	callbacks.keyboard_func = KeyDown;
	callbacks.keyboard_up_func = KeyUp;
	callbacks.mouse_func = MouseClick;

	std::srand(time(nullptr));

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

	if (!ShaderProgramManager::Create("render_texture_sdrprog", IL_POSITION | IL_TEXCOORD, L"render_texture.vs.hlsl", L"render_texture.ps.hlsl")) {
		return false;
	}

	GameScene* gameScene{ new GameScene };
	SceneManager::PushScene(gameScene);

	return true;
}

void BattleArenaApplication::Update() noexcept
{
	SceneManager::Update(GetDelta(), GetMsec());
}

void BattleArenaApplication::Draw() const noexcept
{
	SceneManager::Draw();

	WindowingService::SwapBuffers();
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
