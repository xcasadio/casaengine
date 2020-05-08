#include "Base.h"

#include "XmlLoader.h"
#include "Parsers/Xml/tinyxml2.h"

using namespace tinyxml2;

namespace CasaEngine
{
XmlLoader::XmlLoader()
{    
}
	
XmlLoader::~XmlLoader()
{    
}

/**
 * 
 */
void HandleXmlError(XMLError error_, const std::string& Filename = "")
{
	if (error_ != XML_SUCCESS)
	{
		std::string msg = "tinyxml2 error : ";

		switch(error_)
		{
		case XML_NO_ATTRIBUTE: msg+= "XML_NO_ATTRIBUTE"; break;
		case XML_WRONG_ATTRIBUTE_TYPE: msg+= "XML_WRONG_ATTRIBUTE_TYPE"; break;
		case XML_ERROR_FILE_NOT_FOUND: msg+= "XML_ERROR_FILE_NOT_FOUND"; break;
		case XML_ERROR_FILE_COULD_NOT_BE_OPENED: msg+= "XML_ERROR_FILE_COULD_NOT_BE_OPENED"; break;
		case XML_ERROR_FILE_READ_ERROR: msg+= "XML_ERROR_FILE_READ_ERROR"; break;
		case XML_ERROR_ELEMENT_MISMATCH: msg+= "XML_ERROR_ELEMENT_MISMATCH"; break;
		case XML_ERROR_PARSING_ELEMENT: msg+= "XML_ERROR_PARSING_ELEMENT"; break;
		case XML_ERROR_PARSING_ATTRIBUTE: msg+= "XML_ERROR_PARSING_ATTRIBUTE"; break;
		case XML_ERROR_IDENTIFYING_TAG: msg+= "XML_ERROR_IDENTIFYING_TAG"; break;
		case XML_ERROR_PARSING_TEXT: msg+= "XML_ERROR_PARSING_TEXT"; break;
		case XML_ERROR_PARSING_CDATA: msg+= "XML_ERROR_PARSING_CDATA"; break;
		case XML_ERROR_PARSING_COMMENT: msg+= "XML_ERROR_PARSING_COMMENT"; break;
		case XML_ERROR_PARSING_DECLARATION: msg+= "XML_ERROR_PARSING_DECLARATION"; break;
		case XML_ERROR_PARSING_UNKNOWN: msg+= "XML_ERROR_PARSING_UNKNOWN"; break;
		case XML_ERROR_EMPTY_DOCUMENT: msg+= "XML_ERROR_EMPTY_DOCUMENT"; break;
		case XML_ERROR_MISMATCHED_ELEMENT: msg+= "XML_ERROR_MISMATCHED_ELEMENT"; break;
		case XML_ERROR_PARSING: msg+= "XML_ERROR_PARSING"; break;
		case XML_CAN_NOT_CONVERT_TEXT: msg+= "XML_CAN_NOT_CONVERT_TEXT"; break;
		case XML_NO_TEXT_NODE: msg+= "XML_NO_TEXT_NODE"; break;
		default: msg+= "unknown"; break;
		}

		throw NEW_AO CLoadingFailed(Filename, msg);
	}
}

tinyxml2::XMLDocument* XmlLoader::LoadFromFile(IFile *pFile_)
{
    tinyxml2::XMLDocument *xmlDoc = new tinyxml2::XMLDocument();
	//XMLError error = xmlDoc->LoadFile(Filename.c_str());

	const char *xml = pFile_->GetBuffer();
	XMLError error = xmlDoc->Parse(xml, pFile_->GetBufferLength());

	HandleXmlError(error, pFile_->Filename());	
    return xmlDoc;
}

void XmlLoader::SaveToFile(const tinyxml2::XMLDocument* Object, const std::string& Filename)
{
    XMLError error = const_cast<tinyxml2::XMLDocument *>(Object)->SaveFile(Filename.c_str());
	HandleXmlError(error, Filename);
}

}
