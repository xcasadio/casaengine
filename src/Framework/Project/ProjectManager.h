
#ifndef PROJECTMANAGER_H_
#define PROJECTMANAGER_H_

#include "CA_Export.h"
#include <string>
#include "Parsers\Xml\tinyxml2.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT ProjectManager
	{
	public:
		ProjectManager();
		~ProjectManager();

		void LoadProject(const char *fileName_);
		void SaveProject(const char *fileName_);

		std::string ProjectPath() const;

	private:
		void LoadConfig(const tinyxml2::XMLElement* node_);
		void LoadEngineSettings(const tinyxml2::XMLElement* node_);

		std::string m_ProjectPath;
	};

// #ifdef EDITOR
// 
// 	//Used by the C++/Cli Wrapper
// 	extern "C" __declspec(dllexport) ProjectManager* ProjectManager_New();
// 	extern "C" __declspec(dllexport) void ProjectManager_Delete(ProjectManager* package_);
// 
// #endif // EDITOR

}

#endif // PROJECTMANAGER_H_
