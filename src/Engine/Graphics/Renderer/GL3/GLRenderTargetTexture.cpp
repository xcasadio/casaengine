#include "SystemPlatform.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <windows.h>

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"
#include <gl/glu.h>

#endif // #if CA_PLATFORM_ANDROID

#include "EngineInfo.h"
#include "GLEnum.h"
#include "GLMacro.h"
#include "GLRenderTargetTexture.h"
#include "GLRenderer.h"
#include "GLTexture.h"
#include "Graphics/PixelUtils.h"
#include "Graphics/Viewport.h"
#include "Log/LogManager.h"
#include "CA_Assert.h"



namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur
///
/// \param Size :        Dimensions de la texture
/// \param Format :      Format de pixel de la texture
///
////////////////////////////////////////////////////////////
GLRenderTargetTexture::GLRenderTargetTexture(const Vector2I& Size, PixelFormat::TPixelFormat Format) :
	m_pTexture(nullptr),
	m_pGLTexture(nullptr)
{
	CA_TRACE("GLRenderTargetTexture(%p) created\n", this);
	Create(Size, Format);
}

/**
 * 
 */
GLRenderTargetTexture::~GLRenderTargetTexture()
{
	Release();
}

/**
 * 
 */
void GLRenderTargetTexture::Release()
{
	if (m_GLTexture)
	{
		GLCheck(glDeleteTextures(1, &m_GLTexture));
		m_GLTexture = 0;
	}

	if (m_GLFrameBuffer)
	{
		GLCheck(glDeleteFramebuffers(1, &m_GLFrameBuffer));
		m_GLFrameBuffer = 0;
	}

	if (nullptr != m_pTexture)
	{
		DELETE_AO m_pTexture;
	}

	/*if (nullptr != m_pGLTexture)
	{
		DELETE_AO m_pGLTexture;
	}*/
}

/**
 * 
 */
void GLRenderTargetTexture::Create( const Vector2I& Size, PixelFormat::TPixelFormat Format )
{
	Release();

	CA_TRACE("GLRenderTargetTexture(%p) initialized\n", this);

	// remember previously bound FBO to make sure we set it back
	GLuint previousFBO = 0;
	GLCheck(glGetIntegerv(GL_FRAMEBUFFER_BINDING,reinterpret_cast<GLint*>(&previousFBO)));

	// create FBO
	//GLuint old_tex = 0;
	GLCheck(glGenFramebuffers(1, &m_GLFrameBuffer));
	GLCheck(glBindFramebuffer(GL_FRAMEBUFFER, m_GLFrameBuffer));

	//Create color render
	GLuint colorRenderbuffer;
	GLCheck(glGenRenderbuffers(1, &colorRenderbuffer));
	GLCheck(glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer));
	GLCheck(glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA,
		static_cast<GLsizei>(Size.x), 
		static_cast<GLsizei>(Size.y)));
	GLCheck(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer));

	// set up the texture the FBO will draw to
	GLCheck(glGenTextures(1, &m_GLTexture));
	// TODO : think about how handle the texture. Because ITextureBase create a CImage which
	// allocate memory to store the texture in ram
	//GLTexture *pTexture = NEW_AO GLTexture(m_Size, Format, false, false, m_GLTexture);
	GLCheck(glBindTexture(GL_TEXTURE_2D, m_GLTexture));

	GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCheck(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	//TODO : PixelFormat::TPixelFormat
	GLCheck(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		static_cast<GLsizei>(Size.x),
		static_cast<GLsizei>(Size.y),
		0, GL_RGBA, GL_UNSIGNED_BYTE, 0));

	GLCheck(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_GLTexture, 0));
	//GLCheck(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_GLTexture, 0));


	// The depth buffer
	/*GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);*/

	//Check for framebuffer completeness
	CheckFramebufferStatus();

	m_pGLTexture = NEW_AO GLTexture(Size, Format, false, false, m_GLTexture);
	m_pTexture = NEW_AO Texture();
	m_pTexture->CreateFromTexture(m_pGLTexture);

	// switch from our frame buffer back to the previously bound buffer.
	GLCheck(glBindFramebuffer(GL_FRAMEBUFFER, previousFBO));

	// Set the list of draw buffers.
	//GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	//glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// ensure the CEGUI::Texture is wrapping the gl texture and has correct size
	//d_CEGUITexture->setOpenGLTexture(m_GLTexture, d_area.getSize());

	// restore previous texture binding.
	//GLCheck(glBindTexture(GL_TEXTURE_2D, old_tex));

	SetArea(CRectangle(0, 0,  Size.x,  Size.y));
}

/**
 * 
 */
void GLRenderTargetTexture::CheckFramebufferStatus()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	// Check for completeness
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::stringstream stringStream;
		stringStream << "GLRenderTarget: Error  Framebuffer is not complete\n";

		switch(status)
		{
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			stringStream << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			stringStream << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n";
			break;

#if CA_PLATFORM_WINDOWS

		case GL_FRAMEBUFFER_UNDEFINED:
			stringStream << "GL_FRAMEBUFFER_UNDEFINED \n";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER :
			stringStream << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER \n";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			stringStream << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n";
			break;

		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			stringStream << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n";
			break;

#endif // CA_PLATFORM_WINDOWS

		case GL_FRAMEBUFFER_UNSUPPORTED:
			stringStream << "GL_FRAMEBUFFER_UNSUPPORTED\n";
			break;

		default:
			stringStream << "Undefined Framebuffer error\n";
			break;
		}

		CA_ERROR(stringStream.str().c_str());
	}
}


/////////////////////////////////////////////////////////////
/// Renvoie la texture GL
///
/// \return ID de la texture GL
///
////////////////////////////////////////////////////////////
GLuint GLRenderTargetTexture::GetGLTexture() const
{
    return m_GLTexture;
}

/**
 * 
 */
void GLRenderTargetTexture::Activate()
{
	//CA_TRACE("GLRenderTargetTexture(%p) activated\n", this);

	// remember previously bound FBO to make sure we set it back
	// when deactivating
	GLCheck(glGetIntegerv(GL_FRAMEBUFFER_BINDING,
		reinterpret_cast<GLint*>(&m_GLOldFrameBuffer)));

	// switch to rendering to the texture
	GLCheck(glBindFramebuffer(GL_FRAMEBUFFER, m_GLFrameBuffer));
	IRenderer::Get().SetViewport(
		Viewport(0.0f, 0.0f, 
		static_cast<float>(m_pGLTexture->GetSize().x), 
		static_cast<float>(m_pGLTexture->GetSize().y) ));

	/*if (!d_matrixValid)
		updateMatrix();

	d_owner.setViewProjectionMatrix(d_matrix);
	d_owner.setActiveRenderTarget(this);*/
}

/**
 * 
 */
void GLRenderTargetTexture::Deactivate()
{
	//CA_TRACE("GLRenderTargetTexture(%p) deactivated\n", this);
	// switch back to rendering to the previously bound framebuffer
	GLCheck(glBindFramebuffer(GL_FRAMEBUFFER, m_GLOldFrameBuffer));
}

/**
 * 
 */
Texture *GLRenderTargetTexture::GetTexture()
{
	return m_pTexture;
}

/**
 * 
 */
bool GLRenderTargetTexture::IsImageryCache() const
{
	return true;
}

/**
 * 
 */
bool GLRenderTargetTexture::IsRenderingInverted() const
{
	return true;
}

} // namespace CasaEngine
