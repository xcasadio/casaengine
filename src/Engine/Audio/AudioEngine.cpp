
#include "Base.h"
#include "AudioEngine.h"
#include "Log\LogManager.h"
#include "GL\glew.h"
#include "IO\IFile.h"


namespace CasaEngine
{

/**
 * 
 */
AudioEngine::AudioEngine()
{
	//m_pCurrentViewport = &m_DefaultViewport;
}

/**
 * 
 */
AudioEngine::~AudioEngine()
{
}

/*!
	Start the audio system. This function will automatically use the first valid
	OpenAL device found on your device and will create an OpenAL context. Make sure
	you call this function at initialization time if you plan to use audio. In addition,
	this function will link the necessary callbacks to handle the OGG decompression
	in memory.
*/
void AudioEngine::Start()
{
	m_Device = alcOpenDevice(NULL);

	m_Context = alcCreateContext(m_Device, NULL);

	alcMakeContextCurrent(m_Context);

	CA_INFO("AL_VENDOR:      %s\n", (char *) alGetString ( AL_VENDOR     ) );
	CA_INFO("AL_RENDERER:    %s\n", (char *) alGetString ( AL_RENDERER   ) );
	CA_INFO("AL_VERSION:     %s\n", (char *) alGetString ( AL_VERSION    ) );
	CA_INFO("AL_EXTENSIONS:  %s\n", (char *) alGetString ( AL_EXTENSIONS ) );

	/*m_Callbacks.read_func  = OggRead;
	m_Callbacks.seek_func  = OggSeek;
	m_Callbacks.tell_func  = OggTell;
	m_Callbacks.close_func = OggClose;*/
}

/*!
	Stop the system. This function will also destroy the OpenAL context and close
	the current OpenAL device in use and reset the global audio structure. This function
	should be called inside the exit function of your app, only if you have previous
	called AUDIO_start.
*/
void AudioEngine::Stop()
{
	alcMakeContextCurrent(NULL);
	alcDestroyContext(m_Context);
	alcCloseDevice(m_Device);

	m_Device = NULL;
	m_Context = NULL;
	/*m_Callbacks.read_func  = NULL;
	m_Callbacks.seek_func  = NULL;
	m_Callbacks.tell_func  = NULL;
	m_Callbacks.close_func = NULL;*/
}

/*!
	Function to set the location and direction of the OpenAL listener. You should
	use this function along with your camera to synchronize position and orientation.
	
	\param[in] location Specifies the position of the listener.
	\param[in] direction A normalized vector that specifies the orientation of the listener.
	\param[in] up Specifies the direction of the up vector.
*/
void AudioEngine::SetListener(Vector3F *location, Vector3F *direction, Vector3F *up)
{
	float orientation[6] = { 
		direction->x, direction->y, direction->z,
		up->x, up->y, up->z };

	alListener3f(AL_POSITION,
		location->x,
		location->y,
		location->z );

	alListenerfv(AL_ORIENTATION, &orientation[0]);
}

//! OGG callback to read from a binary stream in memory.
size_t AudioEngine::OggRead(void *ptr, size_t size, size_t read, void *memory_ptr)
{
	unsigned int seof, pos;

	IFile *file = (IFile *) memory_ptr;

	seof = file->GetBufferLength() - file->Position();

	pos = ((read * size) < seof) ? pos = read * size :
	pos = seof;

	if (pos)
	{
		//memcpy(ptr, memory->buffer + memory->position, pos );
		//memory->position += pos;
	}

	return pos;
}

//! OGG callback to seek through a binary stream in memory.
int AudioEngine::OggSeek(void *memory_ptr, size_t offset, int stride)
{
	/*unsigned int pos;
	MEMORY *memory = (MEMORY *) memory_ptr;

	switch( stride )
	{
	case SEEK_SET:
		{
			pos = ( memory->size >= offset ) ? pos = ( unsigned int )offset :
			pos = memory->size;
			memory->position = pos;
			break;
		}

	case SEEK_CUR:
		{
			unsigned int seof = memory->size - memory->position;
			pos = ( offset < seof ) ? pos = ( unsigned int )offset : pos = seof;
			memory->position += pos;
			break;
		}

	case SEEK_END:
		{
			memory->position = memory->size + 1;
			break;
		}
	};*/

	return 0;
}

//! OGG callback to return the current position of the cursor of a binary stream in memory.
long AudioEngine::OggTell(void *memory_ptr)
{
	/*MEMORY *memory = (MEMORY *) memory_ptr;
	return memory->position;*/
	return 0;
}

//! Return wheter or not the memory pointer is closed.
int AudioEngine::OggClose(void *memory_ptr)
{
	//return memory_ptr ? 1 : 0;
	return 0;
}


} // namespace CasaEngine
