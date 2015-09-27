
#ifndef IGAMEDATA_H_
#define IGAMEDATA_H_

#include "CA_Export.h"
#include <iosfwd>
#include "Parsers/Xml/tinyxml2.h"

#include "Assets/Assetable.h"
#include "CompilationMacro.h"

namespace CasaEngine
{
	typedef unsigned int GameDataClassID;

	/**
	 *	
	 */
	class CA_EXPORT IGameData :
		public IAssetable
	{
	public:
		IGameData();
		virtual ~IGameData();
		
		virtual void Read (const tinyxml2::XMLElement& xmlElt) OVERRIDE;
		virtual void Read (std::ifstream& is) OVERRIDE;
		virtual void Write(tinyxml2::XMLElement& xmlElt) OVERRIDE;
		virtual void Write(std::ostream&  os) OVERRIDE;

	private:
		
	};

} // namespace CasaEngine

#endif // IGAMEDATA_H_
