#pragma once

#include "CA_Export.h"

#include "World/World.h"
#include "Entities\Components\CameraComponent.h"

namespace CasaEngine
{
	class CA_EXPORT GameInfo
	{
	public:
		GameInfo();
		~GameInfo();

		World* GetWorld() const;
		void SetWorld(World* val);

		CameraComponent* GetActiveCamera() const;
		void SetActiveCamera(CameraComponent* val);

	private:
		World* m_pWorld;
		CameraComponent* m_pCamera;
	};

}
