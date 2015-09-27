#ifndef WORLD_H_
#define WORLD_H_

#include "CA_Export.h"
#include "CompilationMacro.h"
#include "Entities/Component.h"
#include "Entities\BaseEntity.h"
#include "Physics/IPhysicsWorld.h"
#include "Script/IScriptObject.h"
#include "SpacePartitioning/CellSpacePartition.h"

#include <vector>

namespace CasaEngine
{
	class PhysicsWorld;

	/**
	 *	
	 */
	class CA_EXPORT World :
		public BaseEntity
	{
	public:
		World();
		~World();

		const std::vector<BaseEntity *>& GetEntities();

		void AddEntity(BaseEntity* pEntity);
		void RemoveEntity(BaseEntity* pEntity);

		void SetPhysicsWorld(IPhysicsWorld *world_);
		IPhysicsWorld *GetPhysicsWorld() const;

		CellSpacePartition<BaseEntity *> &GetSpacePartition();

		virtual void Write(std::ostream& os) OVERRIDE;
		virtual void Read(std::ifstream& is) OVERRIDE;
		virtual void Read (const tinyxml2::XMLElement& xmlElt) OVERRIDE;
		virtual void Write(tinyxml2::XMLElement& xmlElt) OVERRIDE;

	private:
		std::vector<BaseEntity *> m_Entities;
		IPhysicsWorld *m_pPhysicsWorld;
		CellSpacePartition<BaseEntity *> m_CellSpacePartition;

	private:

		/**
		 * 
		 */
		class WorldComponent : public Component
		{
		public:
			WorldComponent(BaseEntity* pEntity_);

			void Initialize() OVERRIDE;
			void Update(const GameTime& gameTime_) OVERRIDE;
			void Draw() OVERRIDE;

		private:
			World *m_pWorld;
		};
	};

} // namespace CasaEngine

#endif // WORLD_H_