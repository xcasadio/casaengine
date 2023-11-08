#pragma once

#include <queue>

#include  "IController.hpp"
#include  "Animations/Animation2D.hpp"
#include  "Entities/Component.hpp"
#include <Physics/CollisionParametersBetween2Entities.hpp>

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

		virtual void CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters) = 0;
		void QueueMessage(Telegram& msg);

	private:
		IController* m_pController;
		BaseEntity* m_pEntity;
		std::queue<Telegram> m_MessageQueue;
		bool m_IsPlayer;
	};
}