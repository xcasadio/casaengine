#pragma once

#include  "Parsers/Ini/INIReader.hpp"
#include  "Log/LogManager.hpp"
#include <bgfx/bgfx.h>

namespace CasaEngine
{
	struct EngineSettings
	{
	public:
		char GameplayDLL[256];
		bgfx::RendererType::Enum RendererType;
		bool VerticalSync;
		bool FullScreen;
		int WindowWidth, WindowHeight, DepthColor;

		//
		EngineSettings()
		{
			RendererType = bgfx::RendererType::Count;
			GameplayDLL[0] = '\0';
			VerticalSync = false;
			FullScreen = false;
			WindowWidth = 1024;
			WindowHeight = 768;
			DepthColor = 32;
		}

		void initialize(const char* pFileName_)
		{
			INIReader ini(pFileName_);

			if (ini.ParseError() == 0)
			{
				std::string rdrType = ini.Get("Engine.Settings", "RendererType", "");

				if (rdrType == "dx9") { RendererType = bgfx::RendererType::Direct3D9; }
				else if (rdrType == "dx11") { RendererType = bgfx::RendererType::Direct3D11; }
				else if (rdrType == "dx12") { RendererType = bgfx::RendererType::Direct3D12; }
				else if (rdrType == "gl") { RendererType = bgfx::RendererType::OpenGL; }
				else if (rdrType == "gles") { RendererType = bgfx::RendererType::OpenGLES; }
				else if (rdrType == "vulk") { RendererType = bgfx::RendererType::Vulkan; }
				else if (rdrType == "met") { RendererType = bgfx::RendererType::Metal; }

				WindowWidth = ini.GetInteger("Engine.Settings", "WindowWidth", 1280);
				WindowHeight = ini.GetInteger("Engine.Settings", "WindowHeight", 720);
				DepthColor = ini.GetInteger("Engine.Settings", "DepthColor", 32);
				FullScreen = ini.GetBoolean("Engine.Settings", "FullScreen", false);

				memcpy_s(GameplayDLL,
					256 * sizeof(char),
					ini.Get("Engine.Settings", "GameplayDLL", "").substr(0, 255).c_str(),
					255 * sizeof(char));
			}
			else
			{
				CA_ERROR("Game::InitializeEngineSettings() : Can't find the settings file '%s'.\n", pFileName_);
			}
		}
	};
}