#ifndef WORLD_H_
#define WORLD_H_

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
		BaseEntity* GetEntityByName(std::string name);

		void AddEntity(BaseEntity* pEntity);
		void RemoveEntity(BaseEntity* pEntity);

		void SetPhysicsWorld(IPhysicsWorld *world_);
		IPhysicsWorld *GetPhysicsWorld() const;

		CellSpacePartition<BaseEntity *> &GetSpacePartition();

		void Write(std::ostream& os) override;
		void Read(std::ifstream& is) override;
		void Read (const tinyxml2::XMLElement& xmlElt) override;
		void Write(tinyxml2::XMLElement& xmlElt) override;

	private:
		std::vector<BaseEntity *> m_Entities;
		IPhysicsWorld *m_pPhysicsWorld;
		CellSpacePartition<BaseEntity *> m_CellSpacePartition;

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

#endif // WORLD_H_