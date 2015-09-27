
#ifndef _CEGUIXMLPARSER_H_
#define _CEGUIXMLPARSER_H_

#include "CA_Export.h"
#include "CEGUI\XMLParser.h"


namespace CasaEngine
{
	///
	class CA_EXPORT CEGUIXMLParser : 
		public CEGUI::XMLParser
	{
	public:
		/**
		 * 
		 */
		CEGUIXMLParser();
		
		/**
		 * 
		 */
		~CEGUIXMLParser();

		// Implementation of public abstract interface
		void parseXML(CEGUI::XMLHandler& handler, const CEGUI::RawDataContainer& filename, const CEGUI::String& schemaName);

	protected:
		// Implementation of abstract interface.
		bool initialiseImpl();
		void cleanupImpl();
	};

}  // namespace CasaEngine

#endif //_CEGUIXMLPARSER_H_
