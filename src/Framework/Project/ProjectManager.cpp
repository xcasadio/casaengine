
#include "Base.h"
#include "ProjectManager.h"
#include "Log/LogVerbose.h"
#include "Log/LogManager.h"

#include <iosfwd>
#include <string>
#include "Parsers/Xml/tinyxml2.h"
#include "Parsers/Xml/XMLHelper.h"

using namespace tinyxml2;

namespace CasaEngine
{

// #ifdef EDITOR
// 
// 	//Used by the C++/Cli Wrapper
// 	extern "C" __declspec(dllexport) ProjectManager* ProjectManager_New()
// 	{
// 		return new ProjectManager();
// 	}
// 	extern "C" __declspec(dllexport) void ProjectManager_Delete(ProjectManager* project_)
// 	{
// 		delete project_;
// 	}
// 	///////////////////////////////////////////////////////////
// 
// #endif // EDITOR

ProjectManager::ProjectManager()
{

}


ProjectManager::~ProjectManager()
{

}

void ProjectManager::LoadProject(const char *fileName_)
{
	tinyxml2::XMLDocument *xmlDoc;

	xmlDoc = ::new tinyxml2::XMLDocument();
	XMLError error = xmlDoc->LoadFile(fileName_);

	if (error == XML_SUCCESS)
	{
		const XMLElement *pElem;
		
		pElem = XMLHelper::GetNodeXmlPath(xmlDoc->FirstChildElement(), "Project\\Config");		
		LoadConfig(pElem);

		pElem = XMLHelper::GetNodeXmlPath(xmlDoc->FirstChildElement(), "Project\\EngineSettings");
		LoadEngineSettings(pElem);
	}
	else
	{
		//handle XMLError
	}	

	delete xmlDoc;
}

void ProjectManager::LoadConfig( const XMLElement* /*node_*/ )
{

}

void ProjectManager::LoadEngineSettings( const XMLElement* /*node_*/ )
{

}

void ProjectManager::SaveProject(const char* /*fileName_*/)
{

}

std::string ProjectManager::ProjectPath() const
{
	return m_ProjectPath;
}

} // namespace CasaEngine
