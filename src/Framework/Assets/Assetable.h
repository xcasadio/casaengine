
#ifndef _ASSETABLE_H_
#define _ASSETABLE_H_

#include "CA_Export.h"
#include <string>
#include <iosfwd>
#include "Parsers\Xml\tinyxml2.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	/**
	 *	Each object can be stored inherit from this class
	 */
	class CA_EXPORT IAssetable :
		public AllocatedObject<IAssetable>
	{
	public:
		virtual ~IAssetable();

		std::string GetName() const;
		void SetName(std::string val); // Only EDITOR

		virtual void Read(const tinyxml2::XMLElement& node_);
		virtual void Read(std::ifstream& in);

//#ifdef EDITOR

		virtual void Write(tinyxml2::XMLElement& node_);
		virtual void Write(std::ostream& os);

//#endif // EDITOR
		
	protected:
		IAssetable();

	private:
		std::string m_Name;

	}; // class IAssetable

}

#endif // _ASSETABLE_H_
