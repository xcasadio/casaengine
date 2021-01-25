#ifndef LOADER_H
#define LOADER_H

#include "Exceptions.h"
#include <string>
#include "IO\IFile.h"

namespace CasaEngine
{
	template <class T>
	class ILoader :
		public AllocatedObject<ILoader<T> >
	{
	public:
		virtual ~ILoader() {}
		virtual T* LoadFromFile(IFile* pFile_);
		virtual void SaveToFile(const T* /*Object*/, const std::string& /*Filename*/)
		{
			throw CLoadingFailed("", "The registred loader can't save the datas");
		}

	protected:
		ILoader() {}
	};
}

#endif
