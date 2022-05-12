#pragma once

#include <queue>

#include "IController.h"
#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include <Physics/CollisionParametersBetween2Entities.h>

namespace CasaEngine
{
	class CharacterBase :
		public IAssetable
	{
	public:
		~CharacterBase() override;

		virtual void Initialize();
		virtual void Update(const GameTime& gameTime_);
		virtual void Draw();
		virtual bool HandleMessage(const Telegram& msg);

		void SetController(IController*);
		IController* GetController() const;
		BaseEntity* GetEntity();

	protected:
		CharacterBase(BaseEntity* pEntity);

		virtual void CollideWith(CollisionParameters *collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters) = 0;
		void QueueMessage(Telegram& msg);
	
	private:
		IController* m_pController;
		BaseEntity* m_pEntity;
		std::queue<Telegram> m_MessageQueue;
		bool m_IsPlayer;
	};
}
