
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
#include "UI/Console.h"
#include "Tools/DisplayDebugInfo.h"
#include "Tools/DebugSystem.h"
#include "Tools/DebugOptions.h"

namespace CasaEngine
{
    /**
     * 
     */
    class CA_EXPORT Game
    {
    public :
		static Game *Instance();

        /**
         * 
         */
		void Run();

        /**
         * 
         */
        /*void LoadPlugin(const std::string& Filename);

        /**
         * 
         */
        /*void UnloadPlugin(const std::string& Filename);*/

        /**
         * 
         */
        void Exit();

		/**
		 * 
		 */
		void AddComponent(IGameComponent *component_);

		/**
		 * 
		 */
		void RemoveComponent(IGameComponent *component_);

		//----------------------------------------------------------
		// Get input
		//----------------------------------------------------------
		Input &GetInput();

		/**
		 * 
		 */
		sf::Window* GetWindow();

		/*
		 *	
		 */
		EngineSettings &GetEngineSettings();

		/**
		 * 
		 */
		template <class T>
		T *GetGameComponent() const;

		/**
		 * listen window event
		 */
        void OnEvent(const sf::Event& EventReceived);

		/**
		 * 
		 */
//		CEGUIRenderer *GetCEGUIRenderer() const;

		/**
		 * 
		 */
		bool LoadGamePlayDLL(const char *pFileName_);

		/**
		 * 
		 */
		void RenderThreadloop();

		/**
		 *
		 */
		DebugOptions &GetDebugOptions();

		/**
		 * 
		 */
		DebugSystem &GetDebugSystem();

	//////////////////////////////////////////////////////////////////////////
    protected :

#if CA_PLATFORM_DESKTOP
        Game(sf::WindowHandle handle_ = nullptr);
#else
		Game();
#endif

        /**
         * 
         */
        virtual ~Game();

		//----------------------------------------------------------
		// Called after all components are initialized but before the first update in the game loop. 
		//----------------------------------------------------------
		virtual void BeginRun();

		//----------------------------------------------------------
		// Called after the game loop has stopped running before exiting. 
		//----------------------------------------------------------
#if CA_PLATFORM_MOBILE
	public:
#endif
		virtual void EndRun();

	//////////////////////////////////////////////////////////////////////////
	protected:

		//----------------------------------------------------------
		// Starts the drawing of a frame. This method is followed by calls to Draw and EndDraw. 
		//----------------------------------------------------------
		virtual void BeginDraw();

		//----------------------------------------------------------
		// Called when the game determines it is time to draw a frame.
		//----------------------------------------------------------
		virtual void Draw();

		//----------------------------------------------------------
		// Ends the drawing of a frame. This method is preceeded by calls to Draw and BeginDraw. 
		//----------------------------------------------------------
		virtual void EndDraw();

		//----------------------------------------------------------
		// Called after the Game and Renderer are created, but before LoadContent. 
		//----------------------------------------------------------
		virtual void Initialize();

		//----------------------------------------------------------
		// Called when graphics resources need to be loaded.
		//----------------------------------------------------------
		virtual void LoadContent();

		//----------------------------------------------------------
		// Called when the game has determined that game logic needs to be processed.
		// 
		// \param elpasedTime_ : elapsed time since the last frame
		//----------------------------------------------------------
		virtual void Update(const GameTime& gameTime_);		

	//////////////////////////////////////////////////////////////////////////
    private :

#if CA_PLATFORM_DESKTOP

		void InitializeEngineSettings();

#else // mobile platform

	public:

		void InitializeEngineSettings(int windowWidth_, int windowHeight_, int depthColor_);

	private:

#endif // CA_PLATFORM_WINDOWS || CA_PLATFORM_LINUX

        //----------------------------------------------------------
        // Crée la fenêtre Windows
        //----------------------------------------------------------
        void MakeWindow();

        //----------------------------------------------------------
        // Boucle de rendu
        //----------------------------------------------------------
#if CA_PLATFORM_MOBILE
	public:
#endif
        void FrameLoop();

	//////////////////////////////////////////////////////////////////////////
	private:
	
		/**
		 *
		 */
		void Resize();

		/**
		 * 
		 */
		void RegisterLoaders();

		/**
		 * 
		 */
		void OnWindowResized(unsigned int height_, unsigned int width_);

		/**
		 * 
		 */
		void HandleWindowEvents();


	private:
		Game(const Game&);
		Game& operator = (const Game&);

	private:

        //----------------------------------------------------------
        // Types
        //----------------------------------------------------------
        //typedef std::map<std::string, Plugin > TPluginMap; ///< Type de la table des plugins

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
		GameTime m_GameTime;
		Input m_Input;
		bool m_NeedResize; ///< used when the screen is resized
		Vector2I m_NewSize; ///< used when the screen is resized

#if CA_PLATFORM_DESKTOP
        sf::WindowHandle		m_Hwnd;
#endif
		sf::Window*				m_pWindow;

        bool				m_IsRunning;
        //TPluginMap			m_Plugins;   ///< Table des plugins chargés
		DynamicModule	*m_pGamePlayDLL;

		std::vector<IGameComponent *> m_Components; ///< GameComponent
		std::vector<DrawableGameComponent *> m_DrawableComponents; ///< GameComponent
		bool				m_Initialized;		
		EngineSettings		m_EngineSettings; ///< Settings

// 		CEGUIRenderer* m_pCEGUIRenderer;
// 		CEGUIResourceProvider *m_pCEGUIResourceProvider;
// 		CEGUIXMLParser* m_pCEGUIXMLParser;
// 		CEGUILogger* m_pCEGUILogger;
// 		CEGUIImageCodec* m_pCEGUIImageCodec;

		DebugSystem m_DebugSystem;
		DisplayDebugInfo m_DisplayDebugInfo;
		Console m_Console;
		DebugOptions m_DebugOptions;

        static Game* s_Application;
    };

	#include "Game.inl"

}


#endif // GAME_H
