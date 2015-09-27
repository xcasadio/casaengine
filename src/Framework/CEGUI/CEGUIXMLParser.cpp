
#include "Base.h"

#include "CEGUIXMLParser.h"
#include "CEGUI\XMLHandler.h"
#include "CEGUI\DataContainer.h"
#include "CEGUI\String.h"
#include "Parsers\Xml\tinyxml2.h"
#include "CEGUI\Base.h"
#include "CEGUI\Exceptions.h"
#include "CEGUI\XMLAttributes.h"
#include "Log\LogManager.h"



namespace CasaEngine
{
	//////////////////////////////////////////////////////////////////////////

	/**
	 * 
	 */
	class TinyXMLDocument : public tinyxml2::XMLDocument
	{
	public:
		TinyXMLDocument(CEGUI::XMLHandler& handler, const CEGUI::RawDataContainer& source, const CEGUI::String& schemaName);
		~TinyXMLDocument()
		{}
	protected:
		void processElement(const tinyxml2::XMLElement* element);

	private:
		CEGUI::XMLHandler* d_handler;
	};

	/**
	 *
	 */
	TinyXMLDocument::TinyXMLDocument(CEGUI::XMLHandler& handler, const CEGUI::RawDataContainer& source, const CEGUI::String& /*schemaName*/)
	{
		d_handler = &handler;

		// Create a buffer with extra bytes for a newline and a terminating null
		size_t size = source.getSize();
		char* buf = ::new char[size + 2];
		memcpy(buf, source.getDataPtr(), size);
		// PDT: The addition of the newline is a kludge to resolve an issue
		// whereby parse returns 0 if the xml file has no newline at the end but
		// is otherwise well formed.
		buf[size] = '\n';
		buf[size+1] = 0;

		// Parse the document
		tinyxml2::XMLDocument doc;
		if (doc.Parse((const char*)buf, size+1) != tinyxml2::XML_NO_ERROR)
		{
			// error detected, cleanup out buffers
			delete[] buf;

			// throw exception
			CEGUI_THROW(CEGUI::FileIOException("an error occurred while "
				"parsing the XML document - check it for potential errors!."));
		}

		const tinyxml2::XMLElement* currElement = doc.RootElement();
		if (currElement)
		{
			CEGUI_TRY
			{
				// function called recursively to parse xml data
				processElement(currElement);
			}
			CEGUI_CATCH(...)
			{
				delete [] buf;

				CEGUI_RETHROW;
			}
		} // if (currElement)

		delete [] buf;
	}

	/**
	 * 
	 */
	void TinyXMLDocument::processElement(const tinyxml2::XMLElement* element)
	{
		// build attributes block for the element
		CEGUI::XMLAttributes attrs;

		const tinyxml2::XMLAttribute *currAttr = element->FirstAttribute();
		while (currAttr)
		{
			attrs.add(currAttr->Name(), currAttr->Value());
			currAttr = currAttr->Next();
		}

		// start element
		d_handler->elementStart(element->Value(), attrs);

		// do children
		tinyxml2::XMLNode* childNode = const_cast<tinyxml2::XMLNode*>(element->FirstChild());
		while (childNode)
		{
			if (dynamic_cast<tinyxml2::XMLElement *>(childNode) != nullptr)
			{
				processElement(childNode->ToElement());
			}
			else if (dynamic_cast<tinyxml2::XMLText *>(childNode) != nullptr)
			{
				if (childNode->ToText()->Value() != '\0')
					d_handler->text(childNode->ToText()->Value());
			}
			// Silently ignore unhandled node type
			childNode = childNode->NextSibling();
		}

		// end element
		d_handler->elementEnd(element->Value());
	}

	//////////////////////////////////////////////////////////////////////////

	/**
	 * 
	 */
	CEGUIXMLParser::CEGUIXMLParser()
	{
		// set ID string
		d_identifierString = "CasaEngine::CEGUIXMLParser - tinyXML2 based parser module for CEGUI";
	}

	/**
	 * 
	 */
	CEGUIXMLParser::~CEGUIXMLParser()
	{
		
	}

	/**
	 * 
	 */
	void CEGUIXMLParser::parseXML(CEGUI::XMLHandler& handler, const CEGUI::RawDataContainer& source, const CEGUI::String& schemaName)
	{
		TinyXMLDocument doc(handler, source, schemaName);
	}

	/**
	 * 
	 */
	bool CEGUIXMLParser::initialiseImpl(void)
	{
		// This used to prevent deletion of line ending in the middle of a text.
		// WhiteSpace cleaning will be available throught the use of String methods directly
		//TiXmlDocument::SetCondenseWhiteSpace(false);
		return true;
	}

	/**
	 *
	 */
	void CEGUIXMLParser::cleanupImpl(void)
	{}

} // namespace CasaEngine
