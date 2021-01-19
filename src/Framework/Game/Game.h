#ifndef GAME_H
#define GAME_H

#include "CA_Export.h"
#include "Resources/MediaManager.h"
#include "Resources/ResourceManager.h"

#include "GameTime.h"
#include "Game/GameComponent.h"
#include "Game/DrawableGameComponent.h"
#include "Log/Logger.h"
#include "EngineSettings.h"
#include <map>
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Color.h"
#include "SFML/Window/Window.hpp"
#include "SFML/Window/Event.hpp"
// #include "CEGUI/CEGUIRenderer.h"
// #include "CEGUI/CEGUIResourceProvider.h"
// #include "CEGUI/CEGUIXMLParser.h"
// #include "CEGUI/CEGUILogger.h"
// #include "CEGUI/CEGUIImageCodec.h"

#if CA_PLATFORM_DESKTOP
#	include "SFML/Window/WindowHandle.hpp"
#endif

#include "Input.h"
#include "Script/ScriptEngine.h"
#include "DynamicModule.h"
#include "GameInfo.h"
#include "AI/Messaging/MessageDispatcher.h"
#include "Assets/AssetManager.h"
#include "GameDatas/GameDataFactory.h"
#include "EventHandler/GlobalEventSet.h"
#include "UI/Console.h"
#include "Tools/DisplayDebugInfo.h"
#include "Tools/DebugSystem.h"
#include "Tools/DebugOptions.h"
#include "Entities/EntityManager.h"
#include "Physics/PhysicsEngine.h"
#include "Tools/InGameLogger.h"

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

		void OnEvent(const sf::Event& EventReceived);
		//		CEGUIRenderer *GetCEGUIRenderer() const;
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
		ResourceManager& GetResourceManager();
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
		virtual void Update(const GameTime& gameTime_);

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
		void FrameLoop();

	private:
		void Resize();
		void OnWindowResized(unsigned int height_, unsigned int width_);
		void HandleWindowEvents();

		void RegisterLoaders();

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

		// 		CEGUIRenderer* m_pCEGUIRenderer;
		// 		CEGUIResourceProvider *m_pCEGUIResourceProvider;
		// 		CEGUIXMLParser* m_pCEGUIXMLParser;
		// 		CEGUILogger* m_pCEGUILogger;
		// 		CEGUIImageCodec* m_pCEGUIImageCodec;

		DebugSystem m_DebugSystem;
		DisplayDebugInfo m_DisplayDebugInfo;
		Console m_Console;
		DebugOptions m_DebugOptions;
		GlobalEventSet* m_pGlobalEventSet;
		ScriptEngine m_ScriptEngine;
		GameInfo m_GameInfo;
		EntityManager m_EntityManager;
		MediaManager m_MediaManager;
		AssetManager m_AssetManager;
		ResourceManager m_ResourceManager;
		IRenderer m_Renderer;
		InGameLogger m_InGameLogger;
		GameDataFactory m_GameDataFactory;
		PhysicsEngine m_PhysicsEngine;
		MessageDispatcher m_MessageDispatcher;

#if CA_PLATFORM_DESKTOP
		sf::WindowHandle m_Hwnd;
#endif
		sf::Window* m_pWindow;
	};

#include "Game.inl"

}

#endif
