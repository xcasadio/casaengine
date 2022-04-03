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

#endif // CA_PLATFORM_WINDOWS

#include "Assets/AssetManager.h"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include <iosfwd>
#include "SFML/System/Err.hpp"
#include "EventHandler/GlobalEventSet.h"
#include "Physics/PhysicsEngine.h"

#include "Physics/Bullet/BulletPhysicsEngine.h"
#include "Tools/Bullet/BulletPhysicsDebugDraw.h"

#include <dear-imgui/imgui.h>

#include "Memory/MemoryReport.h"
#include "bgfx/platform.h"
#include "bx/math.h"
#include "Tools/InGameLogger.h"
#include "UI/imguiAdapter.h"

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
		DELETE_AO m_pGamePlayDLL;

		m_EntityManager.Clear();

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
			m_pWindow = new sf::Window(videoMode, "Title", sf::Style::Resize | sf::Style::Titlebar | sf::Style::Close, winSettings);
			m_pWindow->setVisible(true);
#if CA_PLATFORM_DESKTOP
			m_Hwnd = m_pWindow->getSystemHandle();
			CA_ASSERT(m_Hwnd != nullptr, "Game::MakeWindow() : Hwnd is nullptr");
#endif // CA_PLATFORM_DESKTOP

			bgfx::PlatformData pd;
			bx::memSet(&pd, 0, sizeof pd);
			pd.nwh = m_Hwnd;
			setPlatformData(pd);
		}
	}

	void Game::InitializeEngineSettings()
	{
#if CA_PLATFORM_DESKTOP
		m_EngineSettings.initialize(ENGINE_SETTING_FILE);
#else // mobile platform
#endif // CA_PLATFORM_DESKTOP
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

	void Game::HandleWindowEvents()
	{
		sf::Event event;
		bool handled = false;

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

#ifndef EDITOR
			case sf::Event::KeyReleased:
				io.KeysDown[event.key.code] = 0;
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
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					io.MouseDown[0] = true;
					break;

				case sf::Mouse::Right:
					io.MouseDown[1] = true;
					break;

				case sf::Mouse::Middle:
					io.MouseDown[2] = true;
					break;

				case sf::Mouse::XButton1:
					break;

				case sf::Mouse::XButton2:
					break;
				}
				break;

			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
					io.MouseDown[0] = false;
					break;

				case sf::Mouse::Right:
					io.MouseDown[1] = false;
					break;

				case sf::Mouse::Middle:
					io.MouseDown[2] = false;
					break;

				case sf::Mouse::XButton1:
					break;

				case sf::Mouse::XButton2:
					break;
				}
				break;

			case sf::Event::MouseMoved:
				io.MousePos.x = static_cast<float>(event.mouseMove.x);
				io.MousePos.y = static_cast<float>(event.mouseMove.y);

			case sf::Event::MouseWheelScrolled:
				io.MouseWheel = event.mouseWheelScroll.delta;
				break;
#endif
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
		m_Renderer.Initialize(m_EngineSettings);
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
		imguiAdapter::imguiDestroy();
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

		m_DisplayDebugInfo.Initialize();

		imguiAdapter::imguiCreate();
		ImGuiIO& io = ImGui::GetIO();
		io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
		io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
		io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
		io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
		io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
		io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
		io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
		io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
		io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
		io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
		io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
		io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
		io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
		io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
		io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
		io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
		io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
		io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;

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

	void Game::BeginUpdate(const GameTime& gameTime_)
	{
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

	void Game::Update(const GameTime& gameTime_)
	{
	}

	void Game::BeginDraw()
	{
		bgfx::setViewRect(0, 0, 0, GetWindowSize().x, GetWindowSize().y);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		imguiAdapter::imguiBeginFrame(GetEngineSettings().WindowWidth, GetEngineSettings().WindowHeight);

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
		m_DisplayDebugInfo.Draw();
		m_Console.Draw();
		imguiAdapter::imguiEndFrame();
		bgfx::frame();
	}

	/*void Game::LoadPlugin(const std::string& Filename)
	{
		// Si la DLL est déjà chargée on lance une exception
		if (m_Plugins.find(Filename) != m_Plugins.end())
			throw CLoadingFailed(Filename, "DLL already loaded");

		// Sinon on crée et charge le module
		m_Plugins[Filename] = NEW_AO Plugin(Filename);
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

		auto pDGC = dynamic_cast<DrawableGameComponent*>(component_);
		if (pDGC != nullptr)
		{
			m_DrawableComponents.push_back(pDGC);
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

		auto pDGC = dynamic_cast<DrawableGameComponent*>(component_);
		if (pDGC != nullptr)
		{
			for (auto it = m_DrawableComponents.begin();
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

	Input& Game::GetInput()
	{
		return m_Input;
	}

	Vector2I Game::GetWindowSize() const
	{
		return { static_cast<int>(m_pWindow->getSize().x), static_cast<int>(m_pWindow->getSize().y) };
	}

	void Game::OnWindowResized(unsigned int width_, unsigned int height_)
	{
		m_NeedResize = true;
		m_NewSize.x = width_;
		m_NewSize.y = height_;
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

		m_pGamePlayDLL = NEW_AO DynamicModule(pFileName_);
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
}
