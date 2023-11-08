#pragma once

#include "CA_Export.hpp"

#include  "World/World.hpp"
#include  "Entities/Components/CameraComponent.hpp"

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
