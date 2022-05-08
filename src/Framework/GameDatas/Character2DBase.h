#pragma once

#include <map>

#include "CharacterTypes.h"
#include "IController.h"
#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "Maths\Vector2.h"
#include "CharacterBase.h"

namespace CasaEngine
{
	class Character2DBase :
		public CharacterBase
	{
	public:
		static Orientation GetOrientationFromVector2(Vector2 v);

	public:
		~Character2DBase() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		bool SetCurrentAnimationByNameWithOrientation(const char* name);
		bool SetCurrentAnimationByName(const char* name) const;
		void SetAnimationParameters(unsigned int numberOfDir_, unsigned int animationDirMask_);
		void SetAnimationDirectionOffset(Orientation dir_, int offset_);

		bool OnFrameChangedEvent(const EventArgs& e_);
		bool OnAnimationFinished(const EventArgs& e_);

		void Move(Vector2& dir);

		Vector2 Direction() const;
		void Direction(Vector2 val);
		//used to get the right animation according to the direction
		Orientation GetOrientation() const;
		void SetOrientation(Orientation val);

		float Speed() const;
		void Speed(float val);

	protected:
		Character2DBase(BaseEntity* pEntity);
		virtual std::string GetAnimationNameWithOrientation(const char* name, Orientation orientation);

		AnimatedSpriteComponent* m_pAnimatedSprite;
		float m_Speed;
		float m_SpeedOffSet;
		int m_Group;
	
	private:
		int GetAnimationDirectionOffset();

		Orientation m_Orientation;
		Vector2 m_Direction;
		std::map<int, Animation2D*> m_Animations;
		unsigned int m_NumberOfDirection;
		unsigned int m_AnimationDirectionMask;
		std::map<int, int> m_AnimationDirectionOffset;
	};
}
