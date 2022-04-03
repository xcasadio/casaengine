#include "Base.h"
#include "MemoryReport.h"
#include "Log\LogManager.h"

#include <iosfwd>
#include <iomanip>
#include <iostream>

namespace CasaEngine
{
	MemoryReport* MemoryReport::m_pInstance(nullptr);

	MemoryReport& MemoryReport::Instance()
	{
		if (m_pInstance == nullptr)
		{
			m_pInstance = new MemoryReport();
		}

		return *m_pInstance;
	}

	void MemoryReport::Destroy()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

	MemoryReport::MemoryReport()
#if CA_PLATFORM_DESKTOP
		: m_File("Memory monitor.log")
#endif
	{
	}

	void MemoryReport::Allocate(void* ptr, const size_t size, const char* file, const int line)
	{
		TBlock block;
		block.Size = size;
		block.File = file;
		block.Line = line;
		m_Blocks[ptr] = block;

		std::ostringstream oss;
		oss << "++ 0x" << ptr
			<< " | " << std::setw(7) << std::setfill(' ') << static_cast<int>(block.Size) << " octets"
			<< " | " << block.File << " (" << block.Line << ")" << std::endl;
#if CA_PLATFORM_DESKTOP
		m_File << oss.str().c_str();
#endif
	}

	void MemoryReport::Deallocate(void* ptr)
	{
		TBlockMap::iterator It = m_Blocks.find(ptr);
		std::ostringstream oss;

		if (It != m_Blocks.end())
		{
			oss << "-- 0x" << ptr
				<< " | " << std::setw(7) << std::setfill(' ') << static_cast<int>(It->second.Size) << " octets"
				<< " | " << It->second.File << " (" << It->second.Line << ")" << std::endl;
			m_Blocks.erase(It);
		}
		else
		{
			oss << "-- 0x" << ptr << std::endl;
		}

#if CA_PLATFORM_DESKTOP
		m_File << oss.str().c_str();
#endif
	}

	MemoryReport::~MemoryReport()
	{
		//m_File.close();
	}

	void MemoryReport::ReportLeak()
	{
		std::ostringstream oss;

		if (m_Blocks.empty() == false)
		{
			oss << std::endl;
			oss << "========================================" << std::endl;
			oss << "   Memory leak tracker " << std::endl;
			oss << "========================================" << std::endl << std::endl;

			std::size_t TotalSize = 0;

			for (TBlockMap::iterator i = m_Blocks.begin(); i != m_Blocks.end(); ++i)
			{
				TotalSize += i->second.Size;

				// log
				oss << "-> 0x" << i->first
					<< " | " << std::setw(7) << std::setfill(' ') << static_cast<int>(i->second.Size) << " octets"
					<< " | " << i->second.File << " (" << i->second.Line << ")" << std::endl;

				// free memory block
				//free(i->first);
			}

			oss << std::endl << "-- "
				<< static_cast<int>(m_Blocks.size()) << " blocks not released, "
				<< static_cast<int>(TotalSize) << " octets --"
				<< std::endl;
		}
		else
		{
			oss << std::endl;
			oss << "==== No memory leaks detected ====" << std::endl;
		}

#if CA_PLATFORM_DESKTOP
		m_File << oss.str().c_str();
#endif
	}
}