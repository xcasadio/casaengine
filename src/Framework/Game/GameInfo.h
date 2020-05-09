#ifndef GAMEINFO_H_
#define GAMEINFO_H_

#include "CA_Export.h"

#include "Project/ProjectManager.h"
#include "World/World.h"
#include "Entities\Components\CameraComponent.h"

namespace CasaEngine
{
	class CA_EXPORT GameInfo
	{
	public:
		GameInfo();
		~GameInfo();

		ProjectManager& GetProjectManager();

		World* GetWorld() const;
		void SetWorld(World* val);

		CameraComponent* GetActiveCamera() const;
		void SetActiveCamera(CameraComponent* val);

	private:
		ProjectManager m_ProjectManager;
		World* m_pWorld;
		CameraComponent* m_pCamera;
	};

}

#endif
