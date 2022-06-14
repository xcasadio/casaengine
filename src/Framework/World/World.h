#pragma once

#include "CA_Export.h"

#include "Entities/Component.h"
#include "Entities\BaseEntity.h"
#include "Physics/IPhysicsWorld.h"
#include "SpacePartitioning/CellSpacePartition.h"

#include <vector>

namespace CasaEngine
{
	class CA_EXPORT World :
		public BaseEntity
	{
	public:
		World();
		~World() override;

		std::vector<BaseEntity*>& GetEntities();
		BaseEntity* GetEntityByName(const std::string& name) const;

		void AddEntity(BaseEntity* entity);

		IPhysicsWorld& GetPhysicsWorld() const;

		CellSpacePartition<BaseEntity *> &GetSpacePartition();

	private:
		void RemoveMarkedEntities();

		std::vector<BaseEntity *> _entities;
		IPhysicsWorld *_physicsWorld;
		CellSpacePartition<BaseEntity *> _cellSpacePartition;

	private:
		class WorldComponent : public Component
		{
		public:
			WorldComponent(BaseEntity* entity);

			void Initialize() override;
			void Update(const GameTime& gameTime_) override;
			void Draw() override;

		private:
			World *m_pWorld;
		};
	};
}