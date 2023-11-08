#include  "Base.hpp"

#include  "Shader.hpp"

#include  "Game/Game.hpp"
#include  "Graphics/Renderer/Renderer.hpp"



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

		return new Shader(bgfx::createShader(bgfx::makeRef(pFile->GetBuffer(), pFile->GetBufferLength())));
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