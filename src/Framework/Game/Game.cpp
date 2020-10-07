#include "Base.h"

#include "Entities/EntityManager.h"
#include "Exceptions.h"
#include "Game/DrawableGameComponent.h"
#include "Game/Game.h"
#include "Game/GameComponent.h"
#include "Game/GameInfo.h"
#include "GameTime.h"

#include "Graphics/Renderer/Enums.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Viewport.h"
#include "Loaders/XmlLoader.h"
#include "Log/LogManager.h"
#include "Log/LoggerFile.h"
#include "Parsers/Ini/INIReader.h"
#include "Resources/MediaManager.h"
#include "Resources/ResourceManager.h"
#include "SFML/Window/Window.hpp"
#include "SFML/Window/Event.hpp"

#include "bx/thread.h"
// #include <bx/mutex.h>
// #include <bx/handlealloc.h>


// #include "CEGUI/CEGUIRenderer.h"
// #include "CEGUI/CEGUIResourceProvider.h"
// #include <CEGUI/Base.h>
// #include <CEGUI/System.h>
// #include <CEGUI/WindowManager.h>
// #include <CEGUI/GUIContext.h>
// #include <CEGUI/XMLParserModules/TinyXML/XMLParser.h>
// #include "CEGUI/CEGUIXMLParser.h"
// #include "CEGUI/CEGUILogger.h"

#include <algorithm>
#include <string>

#if CA_PLATFORM_WINDOWS

#	include "Win32/Win32Exception.h"

#endif // CA_PLATFORM_WINDOWS

#include "Assets/AssetManager.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iosfwd>
#include "SFML/System/Err.hpp"
#include "EventHandler/GlobalEventSet.h"
#include "Physics/PhysicsEngine.h"


#ifdef USE_BULLET_PHYSICS
#include "Physics/Bullet/BulletPhysicsEngine.h"
#include "Tools/Bullet/BulletPhysicsDebugDraw.h"
#endif // #ifdef USE_BULLET_PHYSICS

#include <dear-imgui/imgui.h>

#include "Memory/MemoryReport.h"
#include "bgfx/platform.h"
#include "Graphics/Effects/Shader.h"
#include "bx/math.h"
#include "Maths/Vector4.h"
#include "Tools/InGameLogger.h"
#include "UI/imguiAdapter.h"

namespace CasaEngine
{
#define ENGINE_SETTING_FILE "EngineSettings.ini"

Game* Game::s_Application = nullptr;

//bx::Thread s_renderThread;

/**
 * Convert SFML key code to CEGUI key code
 */
//CEGUI::Key::Scan convertKeyCodeToCEGUIKey(sf::Keyboard::Key code_);

Game& Game::Instance()
{
	return *s_Application;
}

/**
 * 
 */
#if CA_PLATFORM_DESKTOP
Game::Game(sf::WindowHandle handle_) :
	m_pWindow(nullptr),
#else
Game::Game() :
#endif
	m_pGlobalEventSet(GlobalEventSet::Instance())
{
	m_pGamePlayDLL = nullptr;
	m_IsRunning = true;
	m_Initialized = false;
// 	m_pCEGUIRenderer = nullptr;
// 	m_pCEGUIResourceProvider = nullptr;
// 	m_pCEGUIXMLParser = nullptr;
// 	m_pCEGUILogger = nullptr;
// 	m_pCEGUIImageCodec = nullptr;
	m_NeedResize = false;
    s_Application = this;	

    RegisterLoaders();

#if CA_PLATFORM_DESKTOP

	m_Hwnd = handle_;

#endif // defined(PPLATFORM_DESKTOP)

	//TODO : redirect to the LogManager
	// Redirect to a file
	std::ofstream file("sfml-log.txt");
	std::streambuf* previous = sf::err().rdbuf(file.rdbuf());
	// Redirect to nothing
	//sf::err().rdbuf(nullptr);
	// Restore the original output
	//sf::err().rdbuf(previous);
}

/**
 * 
 */
Game::~Game()
{
	DELETE_AO m_pGamePlayDLL;

// 	::delete m_pCEGUIRenderer;
// 	::delete m_pCEGUIResourceProvider;
// 	::delete m_pCEGUIXMLParser;
// 	::delete m_pCEGUILogger;
// 	::delete m_pCEGUIImageCodec;

#if CA_PLATFORM_DESKTOP

	if (m_pWindow != nullptr)
	{
		m_pWindow->close();
		DELETE_AO m_pWindow;
	}

#endif // CA_PLATFORM_DESKTOP

#if defined(CA_CUSTOM_ALLOCATORS) && defined(CA_CUSTOM_ALLOCATORS_DEBUG)
	MemoryReport::Instance().ReportLeak();
	MemoryReport::Destroy();
#endif

	LogManager::Destroy();
}

/**
 * 
 */
void Game::MakeWindow()
{
	sf::VideoMode videoMode(m_EngineSettings.WindowWidth, m_EngineSettings.WindowHeight, m_EngineSettings.DepthColor);
	sf::ContextSettings winSettings(
		24, //Depth
		8,	//Stencil
		0); //Anti aliasing

#if CA_PLATFORM_DESKTOP

	if (m_Hwnd != nullptr)
	{
		m_pWindow = new sf::Window(m_Hwnd, winSettings);
	}
	else

#endif // CA_PLATFORM_DESKTOP

	{
		m_pWindow = new sf::Window(videoMode, "Title", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close,  winSettings);
		m_pWindow->setVisible(true);

#if CA_PLATFORM_DESKTOP

		m_Hwnd = m_pWindow->getSystemHandle();
		CA_ASSERT(m_Hwnd != nullptr, "Game::MakeWindow() : Hwnd is nullptr");

#endif // CA_PLATFORM_DESKTOP

		bgfx::PlatformData pd;
		bx::memSet(&pd, 0, sizeof pd);
		pd.nwh = m_Hwnd;
		setPlatformData(pd);

		//m_pWindow->AddListener(this);
	}
}




/**
 *
 */
void Game::InitializeEngineSettings()
{
	#if CA_PLATFORM_DESKTOP

	m_EngineSettings.initialize(ENGINE_SETTING_FILE);

	#else // mobile platform

	#endif // CA_PLATFORM_DESKTOP
}

/**
 *	
 */
EngineSettings &Game::GetEngineSettings()
{ 
	return m_EngineSettings; 
}

/**
 * 
 */
void Game::FrameLoop()
{

#if CA_PLATFORM_DESKTOP

    while (m_IsRunning == true)
    {		
		if (m_IsRunning == true)
		{

#endif // CA_PLATFORM_DESKTOP

			HandleWindowEvents();
			m_GameTime.Start();
			Update(m_GameTime);

			BeginDraw();
			Draw();
			EndDraw();

			m_GameTime.End();
 
			if (m_NeedResize == true)
			{
				Resize();
				m_NeedResize = false;
			}

#if CA_PLATFORM_DESKTOP

		} // if (m_IsRunning == true)
    } // while (m_IsRunning == true)

#endif // CA_PLATFORM_DESKTOP

}

/**
 * 
 */
void Game::HandleWindowEvents()
{
	sf::Event event;
	bool handled = false;

	m_Input.Update();

#ifndef EDITOR

	//CEGUI::GUIContext &GUIContext = CEGUI::System::getSingleton().getDefaultGUIContext();

#endif // #ifndef EDITOR
	
	ImGuiIO& io = ImGui::GetIO();

	while (m_pWindow->pollEvent(event))
	{
		m_Input.OnEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:			
			Exit();
			break;

		case sf::Event::Resized:
			OnWindowResized(event.size.width, event.size.height);
			break;

		case sf::Event::KeyPressed:
			io.KeysDown[event.key.code] = 1;

			switch (event.key.code)
			{
			case sf::Keyboard::Quote:
				m_Console.VisibilityToggle(); 
				break;

			case sf::Keyboard::F1:
				m_DebugOptions.ShowLogInGame = !m_DebugOptions.ShowLogInGame; 
				break;

			default:

#ifndef EDITOR
				//handled = GUIContext.injectKeyDown(convertKeyCodeToCEGUIKey(event.key.code));

#endif // #ifndef EDITOR

				break;
			}
			break;

#ifndef EDITOR

		case sf::Event::KeyReleased:
			//handled = GUIContext.injectKeyUp(convertKeyCodeToCEGUIKey(event.key.code));
			//io.KeysDown[event.key.code] = 0;
			break;

		case sf::Event::TextEntered:
			//Console::Instance().SendChar(static_cast<char>(event.text.unicode));
			//handled = GUIContext.injectChar(static_cast<char>(event.text.unicode));
			io.AddInputCharacter(event.text.unicode);
			break;

		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				//handled = GUIContext.injectMouseButtonDown(CEGUI::LeftButton);
				io.MouseDown[0] = true;
				break;

			case sf::Mouse::Right:
				//handled = GUIContext.injectMouseButtonDown(CEGUI::RightButton);
				io.MouseDown[1] = true;
				break;

			case sf::Mouse::Middle:
				//handled = GUIContext.injectMouseButtonDown(CEGUI::MiddleButton);
				io.MouseDown[2] = true;
				break;

			case sf::Mouse::XButton1:
				//handled = GUIContext.injectMouseButtonDown(CEGUI::X1Button);
				break;

			case sf::Mouse::XButton2:
				//handled = GUIContext.injectMouseButtonDown(CEGUI::X2Button);
				break;
			}
			break;

		case sf::Event::MouseButtonReleased:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				//handled = GUIContext.injectMouseButtonUp(CEGUI::LeftButton);
				io.MouseDown[0] = false;
				break;

			case sf::Mouse::Right:
				//handled = GUIContext.injectMouseButtonUp(CEGUI::RightButton);
				io.MouseDown[1] = false;
				break;

			case sf::Mouse::Middle:
				//handled = GUIContext.injectMouseButtonUp(CEGUI::MiddleButton);
				io.MouseDown[2] = false;
				break;

			case sf::Mouse::XButton1:
				//handled = GUIContext.injectMouseButtonUp(CEGUI::X1Button);
				break;

			case sf::Mouse::XButton2:
				//handled = GUIContext.injectMouseButtonUp(CEGUI::X2Button);
				break;
			}
			break;

		case sf::Event::MouseMoved:
// 			handled = GUIContext.injectMousePosition(
// 				static_cast<float>(event.mouseMove.x), 
// 				static_cast<float>(event.mouseMove.y));
			io.MousePos.x = static_cast<float>(event.mouseMove.x);
			io.MousePos.y = static_cast<float>(event.mouseMove.y);

		case sf::Event::MouseWheelMoved:
			//handled = GUIContext.injectMouseWheelChange(static_cast<float>(event.mouseWheel.delta));
			io.MouseWheel += static_cast<float>(event.mouseWheel.delta);
			break;

#endif
		}
	}
}

int32_t renderThreadFunc(void* _userData)
{
	Game* game = static_cast<Game*>(_userData);
	game->RenderThreadloop();

	return 0;
}

void Game::Run()
{
	InitializeEngineSettings();

//#if BGFX_CONFIG_MULTITHREADED

	MakeWindow();
	m_Renderer.Initialize(m_EngineSettings);
	OnWindowResized(m_EngineSettings.WindowWidth, m_EngineSettings.WindowHeight);

	//s_renderThread.init(renderThreadFunc, this);
	RenderThreadloop();

  	//s_renderThread.shutdown();
}

void Game::RenderThreadloop()
{
	CA_TRACE("Renderer initialized\n");
	Initialize();
	CA_TRACE("Game initialized\n");
	LoadContent();
	CA_TRACE("Game load content done\n");

	try
	{
		BeginRun();

#if CA_PLATFORM_DESKTOP

		FrameLoop();
		EndRun();

#endif

	}
	catch (const std::exception& ex)
	{
		CA_FATAL("Error during game running : %s", ex.what());
		return;
	}
	catch (...)
	{
		CA_FATAL("Error during game running : generic exception");
		return;
	}
}

/**
 * 
 */
void Game::BeginRun()
{
}

/**
 * 
 */
void Game::EndRun()
{
	imguiAdapter::imguiDestroy();
}

void Game::Initialize()
{
	m_ScriptEngine.Initialize();

#ifndef EDITOR

// 	m_pCEGUILogger = ::new CEGUILogger();
// 	m_pCEGUIImageCodec = ::new CEGUIImageCodec();
// 	m_pCEGUIRenderer = ::new CEGUIRenderer();
// 	m_pCEGUIResourceProvider = ::new CEGUIResourceProvider();
// 	m_pCEGUIXMLParser = ::new CEGUIXMLParser();
// 
// 	CEGUI::System *pSystem = &CEGUI::System::create(
// 		*m_pCEGUIRenderer, 
// 		m_pCEGUIResourceProvider, 
// 		m_pCEGUIXMLParser, 
// 		m_pCEGUIImageCodec,
// 		nullptr, // ScriptModule
// 		"", // configFile
// 		"CEGUI.log", // logFile
// 		CEGUI_VERSION_ABI); // CEGUI_VERSION_ABI
//
// 		pSystem->getDefaultGUIContext().injectMousePosition(
// 		static_cast<float>(sf::Mouse::getPosition(*m_pWindow).x), 
// 		static_cast<float>(sf::Mouse::getPosition(*m_pWindow).y));

#endif
	
#ifdef USE_BULLET_PHYSICS
	BulletPhysicsDebugDraw* pDebugDraw = NEW_AO BulletPhysicsDebugDraw();
	pDebugDraw->Initialize();
	dynamic_cast<BulletPhysicsEngine*>(PhysicsEngine::Instance().GetPhysicsEngineImpl())->SetPhysicsDebugDraw(pDebugDraw);
#endif

	for (auto* component : m_Components)
	{
		component->Initialize();
	}

	m_PhysicsEngine.Initialize();

// 	if (LoadGamePlayDLL(m_EngineSettings.GameplayDLL) == true)
// 	{
// 		CA_INFO("Gameplay module %s successfully loaded\n", m_EngineSettings.GameplayDLL.c_str());
// 	}
// 	else
// 	{
// 		CA_ERROR("Can't load the Gameplay module %s\n", m_EngineSettings.GameplayDLL.c_str());
// 	}
	
	m_DebugSystem.Initialize();
	m_DisplayDebugInfo.Initialize();

	imguiAdapter::imguiCreate();
	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab]			= sf::Keyboard::Tab;
	io.KeyMap[ImGuiKey_LeftArrow]	= sf::Keyboard::Left;
	io.KeyMap[ImGuiKey_RightArrow]	= sf::Keyboard::Right;
	io.KeyMap[ImGuiKey_UpArrow]		= sf::Keyboard::Up;
	io.KeyMap[ImGuiKey_DownArrow]	= sf::Keyboard::Down;
	io.KeyMap[ImGuiKey_PageUp]		= sf::Keyboard::PageUp;
	io.KeyMap[ImGuiKey_PageDown]	= sf::Keyboard::PageDown;
	io.KeyMap[ImGuiKey_Home]		= sf::Keyboard::Home;
	io.KeyMap[ImGuiKey_End]			= sf::Keyboard::End;
	io.KeyMap[ImGuiKey_Delete]		= sf::Keyboard::Delete;
	io.KeyMap[ImGuiKey_Backspace]	= sf::Keyboard::BackSpace;
	io.KeyMap[ImGuiKey_Enter]		= sf::Keyboard::Return;
	io.KeyMap[ImGuiKey_Escape]		= sf::Keyboard::Escape;
	io.KeyMap[ImGuiKey_A]			= sf::Keyboard::A;
	io.KeyMap[ImGuiKey_C]			= sf::Keyboard::C;
	io.KeyMap[ImGuiKey_V]			= sf::Keyboard::V;
	io.KeyMap[ImGuiKey_X]			= sf::Keyboard::X;
	io.KeyMap[ImGuiKey_Y]			= sf::Keyboard::Y;
	io.KeyMap[ImGuiKey_Z]			= sf::Keyboard::Z;
	
	m_Console.Initialize();

	m_Initialized = true;
}

void Game::LoadContent()
{
	for (auto* component : m_DrawableComponents)
	{
		component->OnLoadContent();
	}
}

void Game::Update(const GameTime& gameTime_)
{
#ifndef EDITOR

	//CEGUI::System::getSingleton().injectTimePulse(gameTime_.FrameTime());

#endif // #ifndef EDITOR

	if (m_GameInfo.GetWorld() != nullptr)
	{
		m_GameInfo.GetWorld()->Update(gameTime_);
	}

	for (auto* component : m_Components)
	{
		component->Update(gameTime_);
	}

	m_InGameLogger.Update(gameTime_);
	m_DebugSystem.Update(gameTime_);
	m_DisplayDebugInfo.Update(gameTime_);
}

/**
 * 
 */
void Game::BeginDraw()
{
	bgfx::setViewRect(0, 0, 0, GetWindowSize().x, GetWindowSize().y);

	// This dummy draw call is here to make sure that view 0 is cleared
	// if no other draw calls are submitted to view 0.
	bgfx::touch(0);
}

/**
 * 
 */
void Game::Draw()
{
	if (m_GameInfo.GetWorld() != nullptr)
	{
		m_GameInfo.GetWorld()->Draw();
	}

	for (auto* component : m_DrawableComponents)
	{
		component->Draw();
	}

	int width = GetEngineSettings().WindowWidth;
	int height = GetEngineSettings().WindowHeight;

	imguiAdapter::imguiBeginFrame(width , height);
}

/**
 * 
 */
void Game::EndDraw()
{
	m_DisplayDebugInfo.Draw();
	m_Console.Draw();

	imguiAdapter::imguiEndFrame();

#ifndef EDITOR

	//CEGUI::System::getSingleton().renderAllGUIContexts();

#endif

	bgfx::frame();
}


////////////////////////////////////////////////////////////
/// Charge un plugin
///
/// \param Filename : Nom de fichier de la DLL
///
////////////////////////////////////////////////////////////
/*void Game::LoadPlugin(const std::string& Filename)
{
    // Si la DLL est d�j� charg�e on lance une exception
    if (m_Plugins.find(Filename) != m_Plugins.end())
        throw CLoadingFailed(Filename, "DLL already loaded");

    // Sinon on cr�e et charge le module
    m_Plugins[Filename] = NEW_AO Plugin(Filename);
}


////////////////////////////////////////////////////////////
/// D�charge un plugin
///
/// \param Filename : Nom de fichier de la DLL
///
////////////////////////////////////////////////////////////
void Game::UnloadPlugin(const std::string& Filename)
{
    // Si la DLL n'est pas charg�e on l�ve une exception
    if (m_Plugins.find(Filename) == m_Plugins.end())
        throw CLoadingFailed(Filename, "DLL not loaded");

    // Sinon on d�charge et d�truit le module
    m_Plugins.erase(Filename);
}*/


/**
 * 
 */
void Game::Exit()
{
    m_IsRunning = false;
}


bool sortGameComponent (IGameComponent* i, IGameComponent* j) 
{ 
	return i->UpdateOrder() < j->UpdateOrder(); 
}

bool sortDrawableGameComponent (DrawableGameComponent* i, DrawableGameComponent* j) 
{ 
	return i->DrawOrder() < j->DrawOrder(); 
}

//----------------------------------------------------------
// 
//----------------------------------------------------------
void Game::AddComponent(IGameComponent *component_)
{
	m_Components.push_back(component_);
	std::sort(m_Components.begin(), m_Components.end(), sortGameComponent); 

	if (m_Initialized == true
		&& component_->IsInitialized() == false)
	{
		component_->Initialize();
	}

	DrawableGameComponent* pDGC = dynamic_cast<DrawableGameComponent*>(component_);
	if (pDGC != nullptr)
	{
		m_DrawableComponents.push_back(pDGC);
		std::sort(m_DrawableComponents.begin(), m_DrawableComponents.end(), sortDrawableGameComponent); 
	}

}

//----------------------------------------------------------
// 
//----------------------------------------------------------
void Game::RemoveComponent(IGameComponent *component_)
{
	for (std::vector<IGameComponent *>::iterator it = m_Components.begin();
		it != m_Components.end();
		++it)
	{
		if (*it == component_)
		{
			m_Components.erase(it);
			break;
		}
	}

	DrawableGameComponent* pDGC = dynamic_cast<DrawableGameComponent*>(component_);
	if (pDGC != nullptr)
	{
		for (std::vector<DrawableGameComponent *>::iterator it = m_DrawableComponents.begin();
			it != m_DrawableComponents.end();
			++it)
		{
			if (*it == pDGC)
			{
				m_DrawableComponents.erase(it);
				break;
			}
		}
	}
}

//----------------------------------------------------------
// Get input
//----------------------------------------------------------
Input &Game::GetInput()
{
	return m_Input;
}

/**
 * 
 */
Vector2I Game::GetWindowSize() const
{
	return Vector2I(m_pWindow->getSize().x, m_pWindow->getSize().y);
}

/**
 * 
 */
void Game::RegisterLoaders()
{
// 	m_MediaManager.RegisterLoader(NEW_AO CImagesLoader, "bmp, dds, jpg, pcx, png, pnm, raw, sgi, tga, tif");
// 	m_MediaManager.RegisterLoader(NEW_AO CShadersLoader(), "vert, fx");
	m_MediaManager.RegisterLoader(NEW_AO XmlLoader, "xml");
}

/**
 * 
 */
void Game::OnWindowResized(unsigned int width_, unsigned int height_)
{
	m_NeedResize = true;
	m_NewSize.x = width_;
	m_NewSize.y = height_;
}

/**
 * 
 */
void Game::Resize()
{
	m_Renderer.Resize(m_NewSize.x, m_NewSize.y);

	//event on all entities
	WindowResizeEvent event(m_NewSize.x, m_NewSize.y);
	GetGlobalEventSet().fireEvent(WindowResizeEvent::GetEventName(), event);

	if (nullptr != m_GameInfo.GetActiveCamera()) // ??
	{
		m_GameInfo.SetActiveCamera(m_GameInfo.GetActiveCamera());
	}
}
    
/**
 * 
 */
// CEGUIRenderer* Game::GetCEGUIRenderer() const
// {
// 	return m_pCEGUIRenderer;
// }

/**
 * 
 */
bool Game::LoadGamePlayDLL( const char *pFileName_ )
{
	//TODO create release method ??

	m_pGamePlayDLL = NEW_AO DynamicModule(pFileName_);
	return m_pGamePlayDLL != nullptr;
}

/**
 * 
 */
DebugOptions &Game::GetDebugOptions()
{
	return m_DebugOptions;
}

/**
 * 
 */
DebugSystem &Game::GetDebugSystem()
{
	return m_DebugSystem;
}

GlobalEventSet& Game::GetGlobalEventSet()
{
	return *m_pGlobalEventSet;
}

ScriptEngine& Game::GetScriptEngine()
{
	return m_ScriptEngine;
}

GameInfo& Game::GetGameInfo()
{
	return m_GameInfo;
}

EntityManager& Game::GetEntityManager()
{
	return m_EntityManager;
}

MediaManager& Game::GetMediaManager()
{
	return m_MediaManager;
}

AssetManager& Game::GetAssetManager()
{
	return m_AssetManager;
}

ResourceManager& Game::GetResourceManager()
{
	return m_ResourceManager;
}

IRenderer& Game::GetRenderer()
{
	return m_Renderer;
}

InGameLogger& Game::GetInGameLogger()
{
	return m_InGameLogger;
}

GameDataFactory& Game::GetGameDataFactory()
{
	return m_GameDataFactory;
}

PhysicsEngine& Game::GetPhysicsEngine()
{
	return m_PhysicsEngine;
}

MessageDispatcher& Game::GetMessageDispatcher()
{
	return m_MessageDispatcher;
}

/**
 * 
 */
// CEGUI::Key::Scan convertKeyCodeToCEGUIKey(sf::Keyboard::Key code_)
// {
// 	switch(code_)
// 	{
// 	case sf::Keyboard::Key::A:		return CEGUI::Key::A; break;
// 	case sf::Keyboard::Key::B:		return CEGUI::Key::B; break;
// 	case sf::Keyboard::Key::C:		return CEGUI::Key::C; break;
// 	case sf::Keyboard::Key::D:		return CEGUI::Key::D; break;
// 	case sf::Keyboard::Key::E:		return CEGUI::Key::E; break;
// 	case sf::Keyboard::Key::F:		return CEGUI::Key::F; break;
// 	case sf::Keyboard::Key::G:		return CEGUI::Key::G; break;
// 	case sf::Keyboard::Key::H:		return CEGUI::Key::H; break;
// 	case sf::Keyboard::Key::I:		return CEGUI::Key::I; break;
// 	case sf::Keyboard::Key::J:		return CEGUI::Key::J; break;
// 	case sf::Keyboard::Key::K:		return CEGUI::Key::K; break;
// 	case sf::Keyboard::Key::L:		return CEGUI::Key::L; break;
// 	case sf::Keyboard::Key::M:		return CEGUI::Key::M; break;
// 	case sf::Keyboard::Key::N:		return CEGUI::Key::N; break;
// 	case sf::Keyboard::Key::O:		return CEGUI::Key::O; break;
// 	case sf::Keyboard::Key::P:		return CEGUI::Key::P; break;
// 	case sf::Keyboard::Key::Q:		return CEGUI::Key::Q; break;
// 	case sf::Keyboard::Key::R:		return CEGUI::Key::R; break;
// 	case sf::Keyboard::Key::S:		return CEGUI::Key::S; break;
// 	case sf::Keyboard::Key::T:		return CEGUI::Key::T; break;
// 	case sf::Keyboard::Key::U:		return CEGUI::Key::U; break;
// 	case sf::Keyboard::Key::V:		return CEGUI::Key::V; break;
// 	case sf::Keyboard::Key::W:		return CEGUI::Key::W; break;
// 	case sf::Keyboard::Key::X:		return CEGUI::Key::X; break;
// 	case sf::Keyboard::Key::Y:		return CEGUI::Key::Y; break;
// 	case sf::Keyboard::Key::Z:		return CEGUI::Key::Z; break;
// 	case sf::Keyboard::Key::Num0:		return CEGUI::Key::Zero; break;		 
// 	case sf::Keyboard::Key::Num1:		return CEGUI::Key::One; break;		 
// 	case sf::Keyboard::Key::Num2:		return CEGUI::Key::Two; break;		 
// 	case sf::Keyboard::Key::Num3:		return CEGUI::Key::Three; break;		 
// 	case sf::Keyboard::Key::Num4:		return CEGUI::Key::Four; break;		 
// 	case sf::Keyboard::Key::Num5:		return CEGUI::Key::Five; break;		 
// 	case sf::Keyboard::Key::Num6:		return CEGUI::Key::Six; break;		 
// 	case sf::Keyboard::Key::Num7:		return CEGUI::Key::Seven; break;		 
// 	case sf::Keyboard::Key::Num8:		return CEGUI::Key::Eight; break;		 
// 	case sf::Keyboard::Key::Num9:		return CEGUI::Key::Nine; break;		 
// 	case sf::Keyboard::Key::Escape:	return CEGUI::Key::Escape; break;	
// 	case sf::Keyboard::Key::LControl:	return CEGUI::Key::LeftControl; break;
// 	case sf::Keyboard::Key::LShift:	return CEGUI::Key::LeftShift; break;
// 	case sf::Keyboard::Key::LAlt:		return CEGUI::Key::LeftAlt; break;
// 	case sf::Keyboard::Key::LSystem:	return CEGUI::Key::LeftWindows; break;
// 	case sf::Keyboard::Key::RControl:	return CEGUI::Key::RightControl; break;
// 	case sf::Keyboard::Key::RShift:	return CEGUI::Key::RightShift; break;
// 	case sf::Keyboard::Key::RAlt:		return CEGUI::Key::RightAlt; break;
// 	case sf::Keyboard::Key::RSystem:	return CEGUI::Key::RightWindows; break;
// 	case sf::Keyboard::Key::Menu:		return CEGUI::Key::AppMenu; break;
// 	case sf::Keyboard::Key::LBracket:	return CEGUI::Key::LeftBracket; break;
// 	case sf::Keyboard::Key::RBracket:	return CEGUI::Key::RightBracket; break;
// 	case sf::Keyboard::Key::SemiColon:return CEGUI::Key::Semicolon; break;
// 	case sf::Keyboard::Key::Comma:	return CEGUI::Key::Comma; break;
// 	case sf::Keyboard::Key::Period:	return CEGUI::Key::Period; break;
// 	case sf::Keyboard::Key::Quote:	return CEGUI::Key::Apostrophe; break;
// 	case sf::Keyboard::Key::Slash:	return CEGUI::Key::Slash; break;
// 	case sf::Keyboard::Key::BackSlash:return CEGUI::Key::Backslash; break;
// 	case sf::Keyboard::Key::Tilde:	return CEGUI::Key::Grave; break;
// 	case sf::Keyboard::Key::Equal:	return CEGUI::Key::Equals; break;
// 	case sf::Keyboard::Key::Dash:		return CEGUI::Key::Minus; break;
// 	case sf::Keyboard::Key::Space:	return CEGUI::Key::Space; break;
// 	case sf::Keyboard::Key::Return:	return CEGUI::Key::Return; break;
// 	case sf::Keyboard::Key::BackSpace:		return CEGUI::Key::Backspace; break;
// 	case sf::Keyboard::Key::Tab:		return CEGUI::Key::Tab; break;
// 	case sf::Keyboard::Key::PageUp:	return CEGUI::Key::PageUp; break;
// 	case sf::Keyboard::Key::PageDown:	return CEGUI::Key::PageDown; break;
// 	case sf::Keyboard::Key::End:		return CEGUI::Key::End; break;
// 	case sf::Keyboard::Key::Home:		return CEGUI::Key::Home; break;
// 	case sf::Keyboard::Key::Insert:	return CEGUI::Key::Insert; break;
// 	case sf::Keyboard::Key::Delete:	return CEGUI::Key::Delete; break;
// 	case sf::Keyboard::Key::Add:		return CEGUI::Key::Add; break;    
// 	case sf::Keyboard::Key::Subtract:	return CEGUI::Key::Subtract; break;    
// 	case sf::Keyboard::Key::Multiply:	return CEGUI::Key::Multiply; break;    
// 	case sf::Keyboard::Key::Divide:	return CEGUI::Key::Divide; break;    
// 	case sf::Keyboard::Key::Left:		return CEGUI::Key::ArrowLeft; break;    
// 	case sf::Keyboard::Key::Right:	return CEGUI::Key::ArrowRight; break;    
// 	case sf::Keyboard::Key::Up:		return CEGUI::Key::ArrowUp; break;    
// 	case sf::Keyboard::Key::Down:		return CEGUI::Key::ArrowDown; break;    
// 	case sf::Keyboard::Key::Numpad0:	return CEGUI::Key::Numpad0; break;
// 	case sf::Keyboard::Key::Numpad1:	return CEGUI::Key::Numpad1; break;
// 	case sf::Keyboard::Key::Numpad2:	return CEGUI::Key::Numpad2; break;
// 	case sf::Keyboard::Key::Numpad3:	return CEGUI::Key::Numpad3; break;
// 	case sf::Keyboard::Key::Numpad4:	return CEGUI::Key::Numpad4; break;
// 	case sf::Keyboard::Key::Numpad5:	return CEGUI::Key::Numpad5; break;
// 	case sf::Keyboard::Key::Numpad6:	return CEGUI::Key::Numpad6; break;
// 	case sf::Keyboard::Key::Numpad7:	return CEGUI::Key::Numpad7; break;
// 	case sf::Keyboard::Key::Numpad8:	return CEGUI::Key::Numpad8; break;
// 	case sf::Keyboard::Key::Numpad9:	return CEGUI::Key::Numpad9; break;
// 	case sf::Keyboard::Key::F1:		return CEGUI::Key::F1; break;
// 	case sf::Keyboard::Key::F2:		return CEGUI::Key::F2; break;
// 	case sf::Keyboard::Key::F3:		return CEGUI::Key::F3; break;
// 	case sf::Keyboard::Key::F4:		return CEGUI::Key::F4; break;
// 	case sf::Keyboard::Key::F5:		return CEGUI::Key::F5; break;
// 	case sf::Keyboard::Key::F6:		return CEGUI::Key::F6; break;
// 	case sf::Keyboard::Key::F7:		return CEGUI::Key::F7; break;
// 	case sf::Keyboard::Key::F8:		return CEGUI::Key::F8; break;
// 	case sf::Keyboard::Key::F9:		return CEGUI::Key::F9; break;
// 	case sf::Keyboard::Key::F10:		return CEGUI::Key::F10; break;
// 	case sf::Keyboard::Key::F11:		return CEGUI::Key::F11; break;
// 	case sf::Keyboard::Key::F12:		return CEGUI::Key::F12; break;
// 	case sf::Keyboard::Key::F13:		return CEGUI::Key::F13; break;
// 	case sf::Keyboard::Key::F14:		return CEGUI::Key::F14; break;
// 	case sf::Keyboard::Key::F15:		return CEGUI::Key::F15; break;
// 	case sf::Keyboard::Key::Pause:	return CEGUI::Key::Pause; break;
// 	}
// 
// 	return CEGUI::Key::Unknown;
// }

}
