#ifndef BLADE_DOC_MAIN_PAGE_H_
#define BLADE_DOC_MAIN_PAGE_H_

/**
 * \mainpage Developer Guide
 * \section intro_sec Legend of the Blade.
 * The Blade engine uses an entity-component hybrid architecture allowing it to be highly modular and extendable. 
 * It provides abstrations for:
 *	- Rendering with Direct3D
 *	- Asset loading
 *	- Math operations
 *	- Shader loading and ShaderProgram creation
 *	- Physics simulation
 *	- Input
 *	- Audio
 *	- Networking
 *	- Oculus VR
 * \section app_sec Creating an Application instance.
 * The Application class provides the intefrace for creating your own application.
 * To create your application create a class that inherits from the engines Application class:
 * \code{.cpp}
 * class MyApplication : public Blade::Application
 * {
 * public:
 *		bool Initialize(int* argc, char* argv[]) override;
 * 
 *		void Update() noexcept override;
 * 
 *		void Draw() const noexcept override;
 * 
 *		int Run() noexcept override;
 * }
 * \endcode
 * 
 * The initialize method is used to initialize your application. Do not forget to call the base class Initialze method first.
 * 
 * \code{.cpp}
 * using namespace Blade;
 * 
 * bool MyApplication::Initialize(int* argc, char* argv[])
 * {
 *		if (!Application::Initialize(argc, argv))
 *		{
 *			return false;
 *		}
 *		
 *		// Initialization code here.
 *		
 *		return true;
 * }
 * \endcode
 * 
 * The Update and Draw methods are used to Update and Draw your Scene.
 * 
 * The Run gives the user the ability to implement an OS specific main loop and tweak it accordingly for maximum performance.
 * Example of a Win32 main loop:
 * \code{.cpp}
 * int MyApplication::Run()
 * {
 *		MSG msg;
 *		while (!ShouldTerminate())
 *		{
 *			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
 *			{
 *				TranslateMessage(&msg);
 *				DispatchMessage(&msg);
 *				
 *				if (WM_QUIT == msg.message)
 *				{
 *					break;
 *				}
 *			}
 *			else
 *			{
 *				Update();
 *				Draw();
 *			}
 *		}
 *		
 *		return 0;
 * }
 * \endcode
 * 
 * In the entry point of your program this is how your application gets instantiated.
 * 
 * \code{.cpp}
 * int main(int argc, char* argv[])
 * {
 *		MyApplication myApplication;
 *		
 *		if (!myApplication.Initialize(&argc, argv))
 *		{
 *			return 1;
 *		}
 *		
 *		return myApplication.Run();
 * }
 * \endcode
 *
 * \section scene_sec Creating a Scene.
 * The Scene class represents a scene in your game. For example a scene can be used for the main menu of your game or the gameplay of your game.
 * It is responsible for managing all the Entities you create and provides input events.
 * To create your own scene simply inherit from the Blade::Scene class and implement the interface functions like so:
 * 
 * \code{.cpp}
 * class MyMainMenu : public Blade::Scene
 * {
 * public:
 *		bool Initialize() override;
 *		
 *		void OnKeyDown(unsigned char key, int x, int y) noexcept override;
 *		
 *		void OnKeyUp(unsigned char key, int x, int y) noexcept override;
 *		
 *		void OnMouseMotion(int x, int y) noexcept override;
 *		
 *		void OnMouseClick(int button, bool state, int x, int y) noexcept override;
 *		
 *		void Update(float deltaTime, long time) noexcept override;
 *		
 *		void Draw() const noexcept override;
 * }
 * \endcode
 * 
 * All the scenes are managed bu the SceneManager. The SceneManager is responsible for updating, drawing and providing input events to the scenes.
 * It contains a stack to hold the scenes and the current active scene is the top of the stack.
 * To add a scene to the SceneManager you have to do the following:
 * \code{.cpp}
 * using namespace Blade;
 * 
 * bool MyApplication::Initialize(int* argc, char* argv[])
 * {
 *		if (!Application::Initialize(argc, argv))
 *		{
 *			return false;
 *		}
 *		
 *		G_SceneManager.PushScene(std::make_unique<MyMainMenu>());
 *		
 *		return true;
 * }
 * \endcode
 * \section shader_sec Creating a ShaderProgram.
 * A ShaderProgram is a class that describes the programmable pipeline stages. It is an aggregation of Shaders.
 * It uses an OpenGL-like usage format by binding and unbinding resources.
 * To create a ShaderProgram you have to do the following:
 * \code{.cpp}
  * using namespace Blade;
 * 
 * bool MyApplication::Initialize(int* argc, char* argv[])
 * {
 *		if (!Application::Initialize(argc, argv))
 *		{
 *			return false;
 *		}
 *		
 *		ShaderProgramDesc sdrProgDesc;
 *		sdrProgDesc.name = "render_texture_sdrprog";
 *		sdrProgDesc.inputLayoutMask = IL_POSITION | IL_TEXCOORD;
 *		sdrProgDesc.vertexShader = L"render_texture.vs.hlsl";
 *		sdrProgDesc.fragmentShader = L"render_texture.ps.hlsl";
 *		
 *		if (!G_ShaderProgramManager.Create(sdrProgDesc))
 *		{
 *			return false;
 *		}
 *		
 *		return true;
 * }
 * \endcode 
 * 
 * \code{.cpp}
 * void MyDrawFunction()
 * {
 *		G_ShaderProgramManager.Get("render_texture_sdrprog")->Bind();
 *		
 *		//Drawing goes here.
 *		
 *		G_ShaderProgramManager.Get("render_texture_sdrprog")->Unbind();
 * }
 * \endcode
 * 
 * \section component_sec Creating a Component.
 * The component class is the basic building block of any entity the user wants to create within the application. 
 * For the most part components are plain data containers which give specific characteristics to an entity, 
 * but occasionally some of the components may contain logic. 
 * That is why the word 'hybrid' is used for this specific engine design. 
 * 
 * To create your own component do the following:
 * 
 * \code{.cpp}
 * class MyComponent : public Blade::Component
 * {
 * public:
 *		
 *		//Implementation specific functions go here
 *		
 *		void OnMessage(const MessageContainer<std::string>& msg)  override;
 * }
 * \endcode
 * 
 * The components are added to Entities in order to alter their role.
 * 
 * \section entity_sec Creating an Entity.
 * An entity is an aggregate of components. Depending on which components an entity is equipped with it assumes a different role within the application.
 * 
 * To add a component to the entity do the following:
 * \code{.cpp}
 * bool MyMainMenu::Initialize()
 * {
 *		Entity* entity{ new Entity{ "myEntity" } };
 *		
 *		MyComponent component{ new MyComponent{ entity } };
 *		
 *		// Rest of the code goes here.  
 * }
 * \endcode
 * 
 * \section systems_sec Using the Systems.
 * Systems are classes that are responsible for processing specific component types and applying specific logic based on the component type.
 * Example usage of the systems:
 * \code{.cpp}
 * 
 * void MyMainMenu::Update(float deltaTime, long time) noexcept
 * {
 *		Scene::Update(deltaTime, time);
 *	
 *		G_SimulationSystem.Process(deltaTime);
 *	
 *		G_LightSystem.Process();
 *	
 *		G_BehaviourSystem.Process(deltaTime, time);
 *	}
 *	
 *	void MyMainMenu::Draw() const noexcept
 *	{
 *		G_RenderSystem.Process();
 *	}
 * \endcode
 */

#endif //BLADE_DOC_MAIN_PAGE_H_
