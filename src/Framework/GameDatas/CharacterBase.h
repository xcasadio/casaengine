#pragma once

#include <queue>

#include "CharacterTypes.h"
#include "IController.h"
#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "GameDatas\IGameData.h"
#include "Maths\Vector2.h"
#include <Physics/CollisionParametersBetween2Entities.h>

namespace CasaEngine
{
	class CharacterBase :
		public IGameData
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

		virtual void CollideWith(BaseEntity* otherEntity, CollisionParametersBetween2Entities* collisionParams) = 0;
		void QueueMessage(Telegram& msg);
	
	private:
		IController* m_pController;
		BaseEntity* m_pEntity;
		std::queue<Telegram> m_MessageQueue;
		bool m_IsPlayer;
	};
}
