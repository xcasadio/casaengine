#ifndef CharacterBase_H_
#define CharacterBase_H_

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
		static orientation GetOrientationFromVector2(Vector2F v);

	public:
		virtual ~CharacterBase();

		virtual void Initialize();
		void Update(const GameTime& gameTime_);
		void Draw();
		virtual bool HandleMessage(const Telegram& msg);

		bool SetCurrentAnimation(const char* name) const;

		void SetController(IController*);
		IController* GetController() const;

		void Move(Vector2F& dir);

		Vector2F Direction() const;
		void Direction(Vector2F val);

		orientation GetOrientation() const;
		void SetOrientation(orientation val);

	protected:
		CharacterBase(BaseEntity* pEntity);
		void QueueMessage(Telegram& msg);

		AnimatedSpriteComponent* m_pAnimatedSprite;

	private:
		IController* m_pController;
		float m_Speed;
		float m_SpeedOffSet;

		orientation m_Orientation;
		Vector2F m_Direction;

		BaseEntity* m_pEntity;
		std::map<int, Animation2D*> m_Animations;
		std::queue<Telegram> m_MessageQueue;
	};
}

#endif
