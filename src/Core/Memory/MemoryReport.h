#ifndef _MEMORYREPORT_H_
#define _MEMORYREPORT_H_

#include "CA_Export.h"

#include <map>
#include <fstream>

namespace CasaEngine
{
	/**
	 *
	 */
	class CA_EXPORT MemoryReport
	{
	public:
		static MemoryReport& Instance();
		static void Destroy();

		~MemoryReport();

		void Allocate(void* ptr, const size_t size, const char* file, const int line);
		void Deallocate(void* ptr);

		void ReportLeak();

	private:
		static MemoryReport* m_pInstance;

		MemoryReport();

	private:
		struct TBlock
		{
			std::size_t Size;
			const char* File;
			int         Line;
		};

		typedef std::map<void*, TBlock> TBlockMap;

		TBlockMap m_Blocks;      ///< allocated blocks

#if CA_PLATFORM_DESKTOP
		std::ofstream m_File;
#endif // #if CA_PLATFORM_DESKTOP
	};
}

#endif	// _MEMORYREPORT_H_
