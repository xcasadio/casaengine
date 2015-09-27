#include "Base.h"

#if CA_PLATFORM_ANDROID

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else

#include <GL/glew.h>
#include <gl/gl.h>
#include "Extensions/glext.h"

#endif // #if CA_PLATFORM_ANDROID

#include <fstream>
#include <string>

#include "Log/LogVerbose.h"
#include "Log/LogManager.h"
#include "IO/IOManager.h"
#include "Resources/MediaManager.h"

#include "Graphics/Renderer/Renderer.h"
#include "GLMacro.h"
#include "GLShader.h"
#include "Graphics/Textures/TextureBase.h"
#include "GLTexture.h"





namespace CasaEngine
{
/**
	* 
	*/
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open() == true)
	{
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
		CA_ERROR("GLShader::LoadShaders() : Can't open %s.\n", vertex_file_path);
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

	if(FragmentShaderStream.is_open() == true)
	{
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else
	{
		CA_ERROR("Impossible to open %s.\n", fragment_file_path);
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLGLength;

	// Compile Vertex Shader
	CA_TRACE("Compiling shader : %d (%s)\n", VertexShaderID, vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	// (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
	GLCheck(glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr));
	GLCheck(glCompileShader(VertexShaderID));

	// Check Vertex Shader
	GLCheck(glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result));
	GLCheck(glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLGLength));
	if (Result == GL_FALSE)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLGLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLGLength, nullptr, &VertexShaderErrorMessage[0]);
		CA_ERROR("Compile vertex shader error %s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	CA_TRACE("Compiling shader : %d (%s)\n", FragmentShaderID, fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	GLCheck(glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr));
	GLCheck(glCompileShader(FragmentShaderID));

	// Check Fragment Shader
	GLCheck(glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result));
	GLCheck(glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLGLength));
	if (Result == GL_FALSE)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLGLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLGLength, nullptr, &FragmentShaderErrorMessage[0]);
		CA_ERROR("Compile fragment shader error %s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	GLuint ProgramID = glCreateProgram();
	CA_TRACE("Linking program %d (vertex shader %d, fragment shader %d)\n", ProgramID, VertexShaderID, FragmentShaderID);		
	GLCheck(glAttachShader(ProgramID, VertexShaderID));
	GLCheck(glAttachShader(ProgramID, FragmentShaderID));
	GLCheck(glLinkProgram(ProgramID));

	// Check the program
	GLCheck(glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result));
	GLCheck(glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLGLength));
	if (Result == GL_FALSE)
	{
		if ( InfoLGLength > 1 )
		{
			std::vector<char> ProgramErrorMessage(InfoLGLength+1);
			glGetProgramInfoLog(ProgramID, InfoLGLength, nullptr, &ProgramErrorMessage[0]);
			CA_ERROR("Link program error %s\n", &ProgramErrorMessage[0]);
		}
	}

	GLCheck(glDeleteShader(VertexShaderID));
	GLCheck(glDeleteShader(FragmentShaderID));

	return ProgramID;
}

/**
 * 
 */
GLuint LoadShaderFrombuffer(const char* pVertexBuffer, const char* pFragmentBuffer)
{
	std::string shaderInit;

#if CA_PLATFORM_ANDROID
	shaderInit = "#version 100\n#define GLES2\n#define texture texture2D\nprecision mediump float;\n";
#else
	shaderInit = "#version 330 core\n";
#endif

	//TODO : use shader compilation option
	shaderInit += "#pragma debug (on)\n#pragma optimize (off)\n";

	const char *pArrayString[2];

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLGLength;

	// Compile Vertex Shader
	pArrayString[0] = shaderInit.c_str();;
	pArrayString[1] = pVertexBuffer;
	CA_TRACE("Compiling vertex shader : %d\n", VertexShaderID);
	GLCheck(glShaderSource(VertexShaderID, 2, pArrayString, nullptr));
	GLCheck(glCompileShader(VertexShaderID));

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLGLength);
	if (Result == GL_FALSE)
	{
		if (InfoLGLength > 1)
		{
			std::vector<char> VertexShaderErrorMessage(InfoLGLength+1);
			glGetShaderInfoLog(VertexShaderID, InfoLGLength, nullptr, &VertexShaderErrorMessage[0]);
			CA_ERROR("Compile vertex shader error %s\n", &VertexShaderErrorMessage[0]);
		}
	}

	// Compile Fragment Shader
	pArrayString[0] = shaderInit.c_str();;
	pArrayString[1] = pFragmentBuffer;
	CA_TRACE("Compiling fragment shader : %d\n", FragmentShaderID);
	GLCheck(glShaderSource(FragmentShaderID, 2, pArrayString , nullptr));
	GLCheck(glCompileShader(FragmentShaderID));

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLGLength);
	if (Result == GL_FALSE)
	{
		if (InfoLGLength > 1)
		{
			std::vector<char> FragmentShaderErrorMessage(InfoLGLength+1);
			glGetShaderInfoLog(FragmentShaderID, InfoLGLength, nullptr, &FragmentShaderErrorMessage[0]);
			CA_ERROR("Compile fragment shader error %s\n", &FragmentShaderErrorMessage[0]);
		}
	}

	// Link the program
	GLuint ProgramID = glCreateProgram();
	CA_TRACE("Linking program %d (vertex shader %d, fragment shader %d)\n", ProgramID, VertexShaderID, FragmentShaderID);		
	GLCheck(glAttachShader(ProgramID, VertexShaderID));
	GLCheck(glAttachShader(ProgramID, FragmentShaderID));
	GLCheck(glLinkProgram(ProgramID));

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLGLength);
	
	if (Result == GL_FALSE)
	{
		if (InfoLGLength > 1)
		{
			std::vector<char> ProgramErrorMessage(InfoLGLength+1);
			glGetProgramInfoLog(ProgramID, InfoLGLength, nullptr, &ProgramErrorMessage[0]);
			CA_ERROR("Link program error %s\n", &ProgramErrorMessage[0]);
		}
	}

	GLCheck(glDeleteShader(VertexShaderID));
	GLCheck(glDeleteShader(FragmentShaderID));

	return ProgramID;
}

////////////////////////////////////////////////////////////
/// Construit le shader à partir des 2 fichiers
/// <name>.vert
/// <name>.frag
///
/// \param shaderFile_ : fichier vertex shader : <name>.vertexshader
///
////////////////////////////////////////////////////////////
GLShader::GLShader(IFile *pFile_)
{
	std::string fragmentFile = pFile_->Filename();

	size_t pos = fragmentFile.find(IRenderer::Get().GetShaderFileExtension());

	if (pos != std::string::npos)
	{
		fragmentFile = fragmentFile.substr(0, pos) + ".frag";
		IFile *pFragFile = MediaManager::Instance().FindMedia(fragmentFile, false);

		if (pFragFile == nullptr)
		{
			throw CLoadingFailed(fragmentFile, "GLShader() : Can't find the fragment shader (maybe add a reference to the right directory ?)");
		}

		if (pFragFile->Exists() == false)
		{
			throw CLoadingFailed(fragmentFile, "GLShader() : The fragment shader doesn't exist");
		}

		m_ProgramID = LoadShaderFrombuffer(pFile_->GetBuffer(), pFragFile->GetBuffer());

		DELETE_AO pFragFile;
	}
	else
	{
		CA_ERROR("GLShader() : Can't find the character '%s' in the filename '%s' to get the fragment shader.", 
			IRenderer::Get().GetShaderFileExtension(), pFile_->Filename().c_str());
	}
}


/**
 * 
 */
void GLShader::Begin()
{
	GLCheck(glUseProgram(m_ProgramID));
}

/**
 * 
 */
void GLShader::End()
{
	//GLCheck(glUseProgram(0)); // not mandatory
}

////////////////////////////////////////////////////////////
/// Change la valeur d'un paramètre (scalaire ou vecteur) du shader
///
/// \param Name :  Nom du paramètre
/// \param Value : Valeur du paramètre (quadruplet de flottants)
///
////////////////////////////////////////////////////////////
void GLShader::SetParameter(const std::string& Name, const size_t count_, const float* Value)
{
	GLuint paramID = glGetUniformLocation(m_ProgramID, Name.c_str());
	/*
	glUniform1f (GLint location, GLfloat v0);
	glUniform2f (GLint location, GLfloat v0, GLfloat v1);
	glUniform3f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	glUniform4f (GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	*/

	switch (count_)
	{
	case 1:
		GLCheck(glUniform1fv(paramID, 1, Value));
		break;

	case 2:
		GLCheck(glUniform2fv(paramID, 1, Value));
		break;

	case 3:
		GLCheck(glUniform3fv(paramID, 1, Value));
		break;

	case 4:
		GLCheck(glUniform4fv(paramID, 1, Value));
		break;
	}
}


////////////////////////////////////////////////////////////
/// Change la valeur d'un paramètre (matrice) du shader
///
/// \param Name :  Nom du paramètre
/// \param Value : Valeur du paramètre (matrice)
///
////////////////////////////////////////////////////////////
void GLShader::SetParameter(const std::string& Name, const Matrix4& Value)
{
	GLuint paramID = glGetUniformLocation(m_ProgramID, Name.c_str());
	glUniformMatrix4fv(paramID, 1, GL_FALSE, (const float *) Value);
}

/**
 * 
 */
void GLShader::SetParameter(const std::string& Name, const ITextureBase* Value)
{
	CA_ASSERT(dynamic_cast<const GLTexture *>(Value) != nullptr, "GLShader::SetParameter() : ITextureBase is not a GLTexture");

	GLuint paramID = glGetUniformLocation(m_ProgramID, Name.c_str());
	glUniform1i(paramID, 0); // unit texture
}

/**
 * 
 */
unsigned int GLShader::ProgramID() const
{
	return static_cast<unsigned int>(m_ProgramID);
}

} // namespace CasaEngine
