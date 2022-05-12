#include "Base.h"

#include "Entities/EntityManager.h"
#include "Exceptions.h"
#include "Game/DrawableGameComponent.h"
#include "Game/Game.h"
#include "Game/GameComponent.h"
#include "Game/GameInfo.h"
#include "GameTime.h"

#include "Graphics/Renderer/Renderer.h"
#include "Log/LogManager.h"
#include "Log/LoggerFile.h"


#include "SFML/Window/Window.hpp"
#include "SFML/Window/Event.hpp"

#include <algorithm>

#if CA_PLATFORM_WINDOWS

#	include "Win32/Win32Exception.h"

#endif

#include "Assets/AssetManager.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iosfwd>
#include "EventHandler/GlobalEventSet.h"
#include "Physics/PhysicsEngine.h"

#include "Physics/Bullet/BulletPhysicsEngine.h"

#include <dear-imgui/imgui.h>

#include "DisplayDebugInfoGameComponent.h"
#include "Line2DRendererComponent.h"
#include "Line3DRendererComponent.h"
#include "MeshRendererGameComponent.h"
#include "Sprite/SpriteRenderer.h"
#include "Tools/InGameLogger.h"
#include "Tools/Bullet/BulletPhysicsDebugDrawComponent.h"
#include "UI/ImGuiAdapter.h"
#include <Entities/Events/BaseEntityEvents.h>

namespace CasaEngine
{
#define ENGINE_SETTING_FILE "EngineSettings.ini"

	Game* Game::s_Application = nullptr;

	Game& Game::Instance()
	{
		return *s_Application;
	}

#if CA_PLATFORM_DESKTOP
	Game::Game(sf::WindowHandle handle_) :
		m_Hwnd(handle_),
		m_pWindow(nullptr),
#else
	Game::Game() :
#endif
		m_NeedResize(false),
		m_Initialized(false),
		m_IsRunning(true),
		m_pGamePlayDLL(nullptr),
		m_pGlobalEventSet(GlobalEventSet::Instance())
	{
		s_Application = this;

		//TODO : redirect to the LogManager
		// Redirect to a file
		//std::ofstream file("sfml-log.txt");
		//std::streambuf* previous = sf::err().rdbuf(file.rdbuf());
		// Redirect to nothing
		//sf::err().rdbuf(nullptr);
		// Restore the original output
		//sf::err().rdbuf(previous);
	}

	Game::~Game()
	{
		delete m_pGamePlayDLL;

		m_EntityManager.Clear();

#if CA_PLATFORM_DESKTOP
		if (m_pWindow != nullptr)
		{
			m_pWindow->close();
			delete m_pWindow;
		}
#endif

#if defined(CA_CUSTOM_ALLOCATORS) && defined(CA_CUSTOM_ALLOCATORS_DEBUG)
		MemoryReport::Instance().ReportLeak();
		MemoryReport::Destroy();
#endif

		LogManager::Destroy();
	}

	void Game::MakeWindow()
	{
		sf::VideoMode videoMode(m_EngineSettings.WindowWidth, m_EngineSettings.WindowHeight, m_EngineSettings.DepthColor);
		sf::ContextSettings winSettings(24, 8, 0);

#if CA_PLATFORM_DESKTOP
		if (m_Hwnd != nullptr)
		{
			m_pWindow = new sf::Window(m_Hwnd, winSettings);
		}
		else
#endif
		{
			m_pWindow = new sf::Window(videoMode, "Title", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, winSettings);
			m_pWindow->setVisible(true);
			m_Hwnd = m_pWindow->getSystemHandle();
		}
	}

	void Game::InitializeEngineSettings()
	{
#if CA_PLATFORM_DESKTOP
		m_EngineSettings.initialize(ENGINE_SETTING_FILE);
#else
#endif
	}

	EngineSettings& Game::GetEngineSettings()
	{
		return m_EngineSettings;
	}

	void Game::FrameLoop()
	{
#if CA_PLATFORM_DESKTOP
		while (m_IsRunning == true)
		{
			if (m_IsRunning == true)
			{
#endif

				HandleWindowEvents();
				m_GameTime.Start();

				BeginUpdate(m_GameTime);
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
			}
		}
#endif
	}

	std::map< sf::Keyboard::Key, ImGuiKey_> keyMapper =
	{
		{ sf::Keyboard::Key::A			 , ImGuiKey_A},
		{ sf::Keyboard::Key::B           , ImGuiKey_B},
		{ sf::Keyboard::Key::C           , ImGuiKey_C},
		{ sf::Keyboard::Key::D           , ImGuiKey_D},
		{ sf::Keyboard::Key::E           , ImGuiKey_E},
		{ sf::Keyboard::Key::F           , ImGuiKey_F},
		{ sf::Keyboard::Key::G           , ImGuiKey_G},
		{ sf::Keyboard::Key::H           , ImGuiKey_H},
		{ sf::Keyboard::Key::I           , ImGuiKey_I},
		{ sf::Keyboard::Key::J           , ImGuiKey_J},
		{ sf::Keyboard::Key::K           , ImGuiKey_K},
		{ sf::Keyboard::Key::L           , ImGuiKey_L},
		{ sf::Keyboard::Key::M           , ImGuiKey_M},
		{ sf::Keyboard::Key::N           , ImGuiKey_N},
		{ sf::Keyboard::Key::O           , ImGuiKey_O},
		{ sf::Keyboard::Key::P           , ImGuiKey_P},
		{ sf::Keyboard::Key::Q           , ImGuiKey_Q},
		{ sf::Keyboard::Key::R           , ImGuiKey_R},
		{ sf::Keyboard::Key::S           , ImGuiKey_S},
		{ sf::Keyboard::Key::T           , ImGuiKey_T},
		{ sf::Keyboard::Key::U           , ImGuiKey_U},
		{ sf::Keyboard::Key::V           , ImGuiKey_V},
		{ sf::Keyboard::Key::W           , ImGuiKey_W},
		{ sf::Keyboard::Key::X           , ImGuiKey_X},
		{ sf::Keyboard::Key::Y           , ImGuiKey_Y},
		{ sf::Keyboard::Key::Z           , ImGuiKey_Z},
		{ sf::Keyboard::Key::Num0        , ImGuiKey_0},
		{ sf::Keyboard::Key::Num1        , ImGuiKey_1},
		{ sf::Keyboard::Key::Num2        , ImGuiKey_2},
		{ sf::Keyboard::Key::Num3        , ImGuiKey_3},
		{ sf::Keyboard::Key::Num4        , ImGuiKey_4},
		{ sf::Keyboard::Key::Num5        , ImGuiKey_5},
		{ sf::Keyboard::Key::Num6        , ImGuiKey_6},
		{ sf::Keyboard::Key::Num7        , ImGuiKey_7},
		{ sf::Keyboard::Key::Num8        , ImGuiKey_8},
		{ sf::Keyboard::Key::Num9        , ImGuiKey_9},
		{ sf::Keyboard::Key::Escape      , ImGuiKey_Escape},
		{ sf::Keyboard::Key::LControl    , ImGuiKey_LeftCtrl},
		{ sf::Keyboard::Key::LShift      , ImGuiKey_LeftShift},
		{ sf::Keyboard::Key::LAlt        , ImGuiKey_LeftAlt},
		{ sf::Keyboard::Key::LSystem     , ImGuiKey_LeftSuper},
		{ sf::Keyboard::Key::RControl    , ImGuiKey_RightCtrl},
		{ sf::Keyboard::Key::RShift      , ImGuiKey_RightShift},
		{ sf::Keyboard::Key::RAlt        , ImGuiKey_RightAlt},
		{ sf::Keyboard::Key::RSystem     , ImGuiKey_RightSuper},
		{ sf::Keyboard::Key::Menu        , ImGuiKey_Menu},
		{ sf::Keyboard::Key::LBracket    , ImGuiKey_LeftBracket},
		{ sf::Keyboard::Key::RBracket    , ImGuiKey_RightBracket},
		{ sf::Keyboard::Key::Semicolon   , ImGuiKey_Semicolon},
		{ sf::Keyboard::Key::Comma       , ImGuiKey_Comma},
		{ sf::Keyboard::Key::Period      , ImGuiKey_Period},
		{ sf::Keyboard::Key::Quote       , ImGuiKey_Apostrophe},
		{ sf::Keyboard::Key::Slash       , ImGuiKey_Slash},
		{ sf::Keyboard::Key::Backslash   , ImGuiKey_Backslash},
		{ sf::Keyboard::Key::Equal       , ImGuiKey_Equal},
		{ sf::Keyboard::Key::Hyphen      , ImGuiKey_Minus},
		{ sf::Keyboard::Key::Space       , ImGuiKey_Space},
		{ sf::Keyboard::Key::Enter       , ImGuiKey_Enter},
		{ sf::Keyboard::Key::Backspace   , ImGuiKey_Backspace},
		{ sf::Keyboard::Key::Tab         , ImGuiKey_Tab},
		{ sf::Keyboard::Key::PageUp      , ImGuiKey_PageUp},
		{ sf::Keyboard::Key::PageDown    , ImGuiKey_PageDown},
		{ sf::Keyboard::Key::End         , ImGuiKey_End},
		{ sf::Keyboard::Key::Home        , ImGuiKey_Home},
		{ sf::Keyboard::Key::Insert      , ImGuiKey_Insert},
		{ sf::Keyboard::Key::Delete      , ImGuiKey_Delete},
		{ sf::Keyboard::Key::Add         , ImGuiKey_KeypadAdd},
		{ sf::Keyboard::Key::Subtract    , ImGuiKey_KeypadSubtract},
		{ sf::Keyboard::Key::Multiply    , ImGuiKey_KeypadMultiply},
		{ sf::Keyboard::Key::Divide      , ImGuiKey_KeypadDivide},
		{ sf::Keyboard::Key::Left        , ImGuiKey_LeftArrow},
		{ sf::Keyboard::Key::Right       , ImGuiKey_RightArrow},
		{ sf::Keyboard::Key::Up          , ImGuiKey_UpArrow},
		{ sf::Keyboard::Key::Down        , ImGuiKey_DownArrow},
		{ sf::Keyboard::Key::Numpad0     , ImGuiKey_Keypad0},
		{ sf::Keyboard::Key::Numpad1     , ImGuiKey_Keypad1},
		{ sf::Keyboard::Key::Numpad2     , ImGuiKey_Keypad2},
		{ sf::Keyboard::Key::Numpad3     , ImGuiKey_Keypad3},
		{ sf::Keyboard::Key::Numpad4     , ImGuiKey_Keypad4},
		{ sf::Keyboard::Key::Numpad5     , ImGuiKey_Keypad5},
		{ sf::Keyboard::Key::Numpad6     , ImGuiKey_Keypad6},
		{ sf::Keyboard::Key::Numpad7     , ImGuiKey_Keypad7},
		{ sf::Keyboard::Key::Numpad8     , ImGuiKey_Keypad8},
		{ sf::Keyboard::Key::Numpad9     , ImGuiKey_Keypad9},
		{ sf::Keyboard::Key::F1          , ImGuiKey_F1},
		{ sf::Keyboard::Key::F2          , ImGuiKey_F2},
		{ sf::Keyboard::Key::F3          , ImGuiKey_F3},
		{ sf::Keyboard::Key::F4          , ImGuiKey_F4},
		{ sf::Keyboard::Key::F5          , ImGuiKey_F5},
		{ sf::Keyboard::Key::F6          , ImGuiKey_F6},
		{ sf::Keyboard::Key::F7          , ImGuiKey_F7},
		{ sf::Keyboard::Key::F8          , ImGuiKey_F8},
		{ sf::Keyboard::Key::F9          , ImGuiKey_F9},
		{ sf::Keyboard::Key::F10         , ImGuiKey_F10},
		{ sf::Keyboard::Key::F11         , ImGuiKey_F11},
		{ sf::Keyboard::Key::F12         , ImGuiKey_F12},
		{ sf::Keyboard::Key::Pause       , ImGuiKey_Pause}
	};

	void addKeyEvent(sf::Event event, ImGuiIO& io, bool isDown)
	{
		const auto key = keyMapper.find(event.key.code);
		if (key != keyMapper.end())
		{
			io.AddKeyEvent(key->second, isDown);
		}
	}

	std::map< sf::Mouse::Button, int> mouseButtonMapper =
	{
		{ sf::Mouse::Button::Left			 , ImGuiMouseButton_Left},
		{ sf::Mouse::Button::Right           , ImGuiMouseButton_Right},
		{ sf::Mouse::Button::Middle          , ImGuiMouseButton_Middle},
	};

	void addMouseButtonEvent(sf::Event event, ImGuiIO& io, bool isDown)
	{
		const auto key = mouseButtonMapper.find(event.mouseButton.button);
		if (key != mouseButtonMapper.end())
		{
			io.AddMouseButtonEvent(key->second, isDown);
		}
	}

	void Game::HandleWindowEvents()
	{
		sf::Event event;
		m_Input.Update();

		ImGuiIO& io = ImGui::GetIO();

		while (m_pWindow->pollEvent(event))
		{
			m_Input.OnEvent(event);

			switch (event.type)
			{
			case sf::Event::Closed:
				Exit();
				break;

			case sf::Event::GainedFocus:
				io.AppFocusLost = false;
				break;

			case sf::Event::LostFocus:
				io.ClearInputKeys();
				io.AppFocusLost = true;
				break;

			case sf::Event::Resized:
				OnWindowResized(event.size.width, event.size.height);
				break;

			case sf::Event::KeyPressed:
				addKeyEvent(event, io, true);

				switch (event.key.code)
				{
				case sf::Keyboard::Quote:
					m_Console.VisibilityToggle();
					break;

				case sf::Keyboard::F1:
					m_DebugOptions.ShowLogInGame = !m_DebugOptions.ShowLogInGame;
					break;

				case sf::Keyboard::LAlt:
				case sf::Keyboard::RAlt:
					io.KeyAlt = true;
					break;

				case sf::Keyboard::LControl:
				case sf::Keyboard::RControl:
					io.KeyCtrl = true;
					break;

				case sf::Keyboard::LShift:
				case sf::Keyboard::RShift:
					io.KeyShift = true;
					break;

				default:
					break;
				}
				break;

			case sf::Event::KeyReleased:
				addKeyEvent(event, io, false);

				switch (event.key.code)
				{
				case sf::Keyboard::LAlt:
				case sf::Keyboard::RAlt:
					io.KeyAlt = false;
					break;

				case sf::Keyboard::LControl:
				case sf::Keyboard::RControl:
					io.KeyCtrl = false;
					break;

				case sf::Keyboard::LShift:
				case sf::Keyboard::RShift:
					io.KeyShift = false;
					break;
				}
				break;

			case sf::Event::TextEntered:
				io.AddInputCharacter(event.text.unicode);
				break;

			case sf::Event::MouseButtonPressed:
				addMouseButtonEvent(event, io, true);
				break;

			case sf::Event::MouseButtonReleased:
				addMouseButtonEvent(event, io, false);
				break;

			case sf::Event::MouseMoved:
				io.AddMousePosEvent(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
				break;

			case sf::Event::MouseWheelScrolled:
				io.AddMouseWheelEvent(0.0f, event.mouseWheelScroll.delta);
				break;
			}
		}
	}

	int32_t renderThreadFunc(void* _userData)
	{
		auto game = static_cast<Game*>(_userData);
		game->RenderThreadloop();
		return 0;
	}

	void Game::Run()
	{
		InitializeEngineSettings();
		MakeWindow();
		m_Renderer.Initialize(m_EngineSettings, m_pWindow->getSystemHandle());
		OnWindowResized(m_EngineSettings.WindowWidth, m_EngineSettings.WindowHeight);
		RenderThreadloop();
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
		}
		catch (const CException& ex)
		{
			CA_FATAL("Error during game running : %s", ex.what());
		}
		catch (...)
		{
			CA_FATAL("Error during game running : generic exception");
		}
	}

	void Game::BeginRun()
	{
	}

	void Game::EndRun()
	{
		ImGuiAdapter::Destroy();
	}

	void Game::Initialize()
	{
		m_ScriptEngine.Initialize();

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

		ImGuiAdapter::Create();
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

	void Game::BeginUpdate(const GameTime& gameTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = gameTime.FrameTime();

		m_DebugSystem.Update(gameTime);

		if (m_GameInfo.GetWorld() != nullptr)
		{
			m_GameInfo.GetWorld()->Update(gameTime);
		}

		for (auto* component : m_Components)
		{
			component->Update(gameTime);
		}
	}

	void Game::Update(const GameTime& gameTime)
	{
	}

	void Game::AddDebugComponents()
	{
#if EDITOR
		AddComponent(new DisplayDebugInfoGameComponent(this));
#endif
		AddComponent(new BulletPhysicsDebugDrawComponent(this));
	}

	void Game::AddUsualComponents()
	{
		AddComponent(new Line2DRendererComponent(this));
		AddComponent(new Line3DRendererComponent(this));
		AddComponent(new SpriteRenderer(this));
		AddComponent(new MeshRendererGameComponent(this));
	}

	void Game::BeginDraw()
	{
		m_Renderer.BeginDraw();

		ImGuiAdapter::BeginFrame(GetWindowSize().x, GetWindowSize().y);

		if (m_GameInfo.GetWorld() != nullptr)
		{
			m_GameInfo.GetWorld()->Draw();
		}

		for (auto* component : m_DrawableComponents)
		{
			component->Draw();
		}
	}

	void Game::Draw()
	{

	}

	void Game::EndDraw()
	{
		m_Console.Draw();
		ImGuiAdapter::EndFrame();
		m_Renderer.EndDraw();
	}

	/*void Game::LoadPlugin(const std::string& Filename)
	{
		// Si la DLL est déjà chargée on lance une exception
		if (m_Plugins.find(Filename) != m_Plugins.end())
			throw CLoadingFailed(Filename, "DLL already loaded");

		// Sinon on crée et charge le module
		m_Plugins[Filename] = new Plugin(Filename);
	}

	void Game::UnloadPlugin(const std::string& Filename)
	{
		// Si la DLL n'est pas chargée on lève une exception
		if (m_Plugins.find(Filename) == m_Plugins.end())
			throw CLoadingFailed(Filename, "DLL not loaded");

		// Sinon on décharge et détruit le module
		m_Plugins.erase(Filename);
	}*/

	void Game::Exit()
	{
		m_IsRunning = false;
	}

	bool sortGameComponent(IGameComponent* i, IGameComponent* j)
	{
		return i->UpdateOrder() < j->UpdateOrder();
	}

	bool sortDrawableGameComponent(DrawableGameComponent* i, DrawableGameComponent* j)
	{
		return i->DrawOrder() < j->DrawOrder();
	}

	void Game::AddComponent(IGameComponent* component_)
	{
		m_Components.push_back(component_);
		std::sort(m_Components.begin(), m_Components.end(), sortGameComponent);

		if (m_Initialized == true
			&& component_->IsInitialized() == false)
		{
			component_->Initialize();
		}

		auto* drawable_game_component = dynamic_cast<DrawableGameComponent*>(component_);
		if (drawable_game_component != nullptr)
		{
			m_DrawableComponents.push_back(drawable_game_component);
			std::sort(m_DrawableComponents.begin(), m_DrawableComponents.end(), sortDrawableGameComponent);
		}
	}

	void Game::RemoveComponent(IGameComponent* component_)
	{
		for (auto it = m_Components.begin();
			it != m_Components.end();
			++it)
		{
			if (*it == component_)
			{
				m_Components.erase(it);
				break;
			}
		}

		auto* drawable_game_component = dynamic_cast<DrawableGameComponent*>(component_);
		if (drawable_game_component != nullptr)
		{
			for (auto it = m_DrawableComponents.begin();
				it != m_DrawableComponents.end();
				++it)
			{
				if (*it == drawable_game_component)
				{
					m_DrawableComponents.erase(it);
					break;
				}
			}
		}
	}

	Input& Game::GetInput()
	{
		return m_Input;
	}

	Vector2I Game::GetWindowSize() const
	{
		return { static_cast<int>(m_pWindow->getSize().x), static_cast<int>(m_pWindow->getSize().y) };
	}

	void Game::OnWindowResized(unsigned int width, unsigned int height)
	{
		m_NeedResize = true;
		m_NewSize.x = width;
		m_NewSize.y = height;
	}

	void Game::Resize()
	{
		m_Renderer.Resize(m_NewSize.x, m_NewSize.y);

		WindowResizeEvent event(m_NewSize.x, m_NewSize.y);
		GetGlobalEventSet().fireEvent(WindowResizeEvent::GetEventName(), event);

		if (nullptr != m_GameInfo.GetActiveCamera()) // ??
		{
			m_GameInfo.SetActiveCamera(m_GameInfo.GetActiveCamera());
		}
	}

	bool Game::LoadGamePlayDLL(const char* pFileName_)
	{
		//TODO create release method ??

		m_pGamePlayDLL = new DynamicModule(pFileName_);
		return m_pGamePlayDLL != nullptr;
	}

	DebugOptions& Game::GetDebugOptions()
	{
		return m_DebugOptions;
	}

	DebugSystem& Game::GetDebugSystem()
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

	IRenderer& Game::GetRenderer()
	{
		return m_Renderer;
	}

	InGameLogger& Game::GetInGameLogger()
	{
		return m_InGameLogger;
	}

	PhysicsEngine& Game::GetPhysicsEngine()
	{
		return m_PhysicsEngine;
	}

	MessageDispatcher& Game::GetMessageDispatcher()
	{
		return m_MessageDispatcher;
	}
}
