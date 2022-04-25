#pragma once

#include <map>
#include <queue>

#include "CharacterTypes.h"
#include "IController.h"
#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "GameDatas\IGameData.h"
#include "Maths\Vector2.h"

namespace CasaEngine
{
	class CharacterBase :
		public IGameData
	{
	public:
		static orientation GetOrientationFromVector2(Vector2 v);

	public:
		~CharacterBase() override;

		virtual void Initialize();
		virtual void Update(const GameTime& gameTime_);
		virtual void Draw();
		virtual bool HandleMessage(const Telegram& msg);

		bool SetCurrentAnimation(const char* name) const;

		void SetController(IController*);
		IController* GetController() const;
		BaseEntity* GetEntity();

		void Move(Vector2& dir);

		Vector2 Direction() const;
		void Direction(Vector2 val);

		orientation GetOrientation() const;
		void SetOrientation(orientation val);

	protected:
		CharacterBase(BaseEntity* pEntity);
		void QueueMessage(Telegram& msg);

		AnimatedSpriteComponent* m_pAnimatedSprite;

		float m_Speed;
		float m_SpeedOffSet;
		int m_Group;
	
	private:
		IController* m_pController;

		orientation m_Orientation;
		Vector2 m_Direction;

		BaseEntity* m_pEntity;
		std::map<int, Animation2D*> m_Animations;
		std::queue<Telegram> m_MessageQueue;
	};
}
