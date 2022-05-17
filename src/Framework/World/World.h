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
		const std::vector<BaseEntity*>& GetEntities();
		BaseEntity* GetEntityByName(const std::string& name);

		void AddEntity(BaseEntity* pEntity);
		void RemoveEntity(BaseEntity* pEntity);

		IPhysicsWorld& GetPhysicsWorld() const;

		CellSpacePartition<BaseEntity *> &GetSpacePartition();

		void Write(std::ostream& os) override;
		void Read(std::ifstream& is) override;

	private:
		std::vector<BaseEntity *> _entities;
		IPhysicsWorld *_physicsWorld;
		CellSpacePartition<BaseEntity *> _cellSpacePartition;

	private:
		class WorldComponent : public Component
		{
		public:
			WorldComponent(BaseEntity* pEntity_);

			void Initialize() override;
			void Update(const GameTime& gameTime_) override;
			void Draw() override;

		private:
			World *m_pWorld;
		};
	};
}