#pragma once

#include "CA_Export.h"
#include "DynamicModule.h"
#include "EngineSettings.h"
#include "GameInfo.h"
#include "GameTime.h"
#include "Input.h"
#include "Messaging/MessageDispatcher.h"
#include "Assets/AssetManager.h"
#include "Entities/EntityManager.h"
#include "EventHandler/GlobalEventSet.h"
#include "Game/DrawableGameComponent.h"
#include "Game/GameComponent.h"
#include "GameDatas/GameDataFactory.h"
#include "Graphics/Renderer/Renderer.h"
#include "Physics/PhysicsEngine.h"
#include "Resources/MediaManager.h"
#include "Script/ScriptEngine.h"
#include "Tools/DebugOptions.h"
#include "Tools/DebugSystem.h"
#include "Tools/InGameLogger.h"
#include "UI/Console.h"

#include "imgui.h"
#include "SFML/Window/Window.hpp"
#if CA_PLATFORM_DESKTOP
#	include "SFML/Window/WindowHandle.hpp"
#endif

namespace CasaEngine
{
	class CA_EXPORT Game
	{
	public:
		static Game& Instance();
		
		Game(const Game&) = delete;
		Game& operator = (const Game&) = delete;

		void Run();
		void Exit();

		void AddComponent(IGameComponent* component_);
		void RemoveComponent(IGameComponent* component_);
		template <class T> T* GetGameComponent() const;

		bool LoadGamePlayDLL(const char* pFileName_);
		void RenderThreadloop();

		Vector2I GetWindowSize() const;
		EngineSettings& GetEngineSettings();
		Input& GetInput();
		DebugOptions& GetDebugOptions();
		DebugSystem& GetDebugSystem();
		GlobalEventSet& GetGlobalEventSet();
		ScriptEngine& GetScriptEngine();
		GameInfo& GetGameInfo();
		EntityManager& GetEntityManager();
		MediaManager& GetMediaManager();
		AssetManager& GetAssetManager();
		IRenderer& GetRenderer();
		InGameLogger& GetInGameLogger();
		GameDataFactory& GetGameDataFactory();
		PhysicsEngine& GetPhysicsEngine();
		MessageDispatcher& GetMessageDispatcher();

	protected:

#if CA_PLATFORM_DESKTOP
		Game(sf::WindowHandle handle_ = nullptr);
#else
		Game();
#endif

		virtual ~Game();
		virtual void BeginRun();

#if CA_PLATFORM_MOBILE
	public:
#endif
		virtual void EndRun();

	protected:
		virtual void BeginDraw();
		virtual void Draw();
		virtual void EndDraw();

		virtual void Initialize();
		virtual void LoadContent();
		virtual void Update(const GameTime& gameTime);


		void AddDebugComponents();
		void AddUsualComponents();

	private:
		void MakeWindow();

#if CA_PLATFORM_DESKTOP

		void InitializeEngineSettings();

#else // mobile platform

	public:

		void InitializeEngineSettings(int windowWidth_, int windowHeight_, int depthColor_);

	private:

#endif


#if CA_PLATFORM_MOBILE
	public:
#endif
		void BeginUpdate(const GameTime& gameTime);
		void FrameLoop();

	private:
		void Resize();
		void OnWindowResized(unsigned int width, unsigned int height);
		void HandleWindowEvents();

	private:
		static Game* s_Application;

		GameTime m_GameTime;
		Input m_Input;
		bool m_NeedResize;
		Vector2I m_NewSize;

		bool				m_IsRunning;
		DynamicModule* m_pGamePlayDLL;

		std::vector<IGameComponent*> m_Components;
		std::vector<DrawableGameComponent*> m_DrawableComponents;
		bool				m_Initialized;
		EngineSettings		m_EngineSettings;

		DebugSystem m_DebugSystem;
		Console m_Console;
		DebugOptions m_DebugOptions;
		GlobalEventSet* m_pGlobalEventSet;
		ScriptEngine m_ScriptEngine;
		GameInfo m_GameInfo;
		EntityManager m_EntityManager;
		MediaManager m_MediaManager;
		AssetManager m_AssetManager;
		IRenderer m_Renderer;
		InGameLogger m_InGameLogger;
		GameDataFactory m_GameDataFactory;
		PhysicsEngine m_PhysicsEngine;
		MessageDispatcher m_MessageDispatcher;

		sf::WindowHandle m_Hwnd;
		sf::Window* m_pWindow;
	};

	template <class T>
	T* Game::GetGameComponent() const
	{
		T* res = nullptr;

		for (auto* component : m_Components)
		{
			res = dynamic_cast<T*>(component);

			if (res != nullptr)
			{
				break;
			}
		}

		return res;
	}

}
