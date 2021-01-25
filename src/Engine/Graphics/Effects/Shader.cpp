#include "Base.h"

#include "Shader.h"

#include "Game/Game.h"
#include "Graphics/Renderer/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Resources/MediaManager.h"

namespace CasaEngine
{
	/**
	 *
	 */
	Shader* Shader::loadShader(const char* name_)
	{
		const int PATH_SIZE = 512;
		char n[PATH_SIZE];
		//TODO : create name corresponding to the renderer type
		sprintf_s(n, PATH_SIZE, "%s.bin", name_);

		IFile* pFile = Game::Instance().GetMediaManager().FindMedia(n, true);
		if (pFile == nullptr)
		{
			return nullptr;
		}

		return NEW_AO Shader(bgfx::createShader(bgfx::makeRef((uint8_t*)pFile->GetBuffer(), pFile->GetBufferLength())));
	}

	/**
	 *
	 */
	Shader::Shader(bgfx::ShaderHandle handle_)
	{
		m_Handle = handle_;
	}

	/**
	 *
	 */
	Shader::~Shader()
	{
		bgfx::destroy(m_Handle);
	}

	/**
	 *
	 */
	bgfx::ShaderHandle Shader::Handle() const
	{
		return m_Handle;
	}
}