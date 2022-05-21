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
				m_GameTime.Start();

				HandleWindowEvents();
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
		m_Input.Update();

		while (m_pWindow->pollEvent(event))
		{
			m_Input.OnEvent(event);
			ImGuiAdapter::UpdateInput(event);

			switch (event.type)
			{
			case sf::Event::Closed:
				Exit();
				break;

			case sf::Event::Resized:
				OnWindowResized(event.size.width, event.size.height);
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Quote:
					m_Console.VisibilityToggle();
					break;

				case sf::Keyboard::F1:
					m_DebugOptions.ShowLogInGame = !m_DebugOptions.ShowLogInGame;
					break;
				}
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
		catch (const Exception& ex)
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
		m_PhysicsEngine.Initialize();

		for (auto* component : m_Components)
		{
			component->Initialize();
		}

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
		ImGuiAdapter::Update(gameTime);

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

	void Game::Draw() { /* do nothing */ }

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
			throw LoadingFailed(Filename, "DLL already loaded");

		// Sinon on crée et charge le module
		m_Plugins[Filename] = new Plugin(Filename);
	}

	void Game::UnloadPlugin(const std::string& Filename)
	{
		// Si la DLL n'est pas chargée on lève une exception
		if (m_Plugins.find(Filename) == m_Plugins.end())
			throw LoadingFailed(Filename, "DLL not loaded");

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
