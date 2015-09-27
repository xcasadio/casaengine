
#ifndef AUDIO_H_
#define AUDIO_H_

#include "LibraryEngineExport.h"
#include "Memory\MemoryAllocation.h"
#include "Maths\Vector3.h"
#include "al.h"
#include "alc.h"
#include "alExt.h"
#include "alMain.h"

namespace CasaEngine
{
	/**
	 *	
	 */
	class LIBRARY_ENGINE_EXPORT AudioEngine :
		public AllocatedObject<AudioEngine>
	{
	public:
		AudioEngine();
		~AudioEngine();

		void Start();

		void Stop();

		void SetListener(Vector3F *location, Vector3F *direction, Vector3F *up);

		size_t OggRead(void *ptr, size_t size, size_t read, void *memory_ptr);

		int OggSeek(void *memory_ptr, size_t offset, int stride);

		long OggTell(void *memory_ptr);

		int OggClose(void *memory_ptr);

	private:

		//! The OpenAL device pointer.
		ALCdevice		*m_Device;

		//! The OpenAL context pointer.
		ALCcontext		*m_Context;

		//! The in OGG file IO callbacks use to decompress OGG file(s) from memory.
		//ov_callbacks	m_Callbacks;

	};

} // namespace CasaEngine

#endif // AUDIO_H_
