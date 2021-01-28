#ifndef ANIMATED_SPRITECOMPONENT_H
#define ANIMATED_SPRITECOMPONENT_H

#include <string>
#include <vector>

#include "CA_Export.h"
#include "Entities/Component.h"
#include "GameTime.h"
#include "Graphics/Color.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Transform3DComponent.h"
#include "Animations/Animation2D.h"
#include "EventHandler\EventSet.h"
#include "EventHandler/Event.h"

#include "Physics/PhysicsObjectContainer.h"

namespace CasaEngine
{
	class CA_EXPORT AnimatedSpriteComponent :
		public Component,
		public EventSet
	{
	private:
		SpriteRenderer*	m_pSpriteRenderer;
		Transform3DComponent* m_pTransform;
		CColor m_Color;		
		eSpriteEffects m_SpriteEffect;
		Animation2D *m_pCurrentAnim;

		std::vector<Animation2D *> m_AnimationList;
		// keep physics object created by the current frame in order to remove them after
		// the frame change
		std::vector<ICollisionObjectContainer *> m_LastSpriteCollisionObjects;

		Event::Connection m_FrameChangedConnection;
		Event::Connection m_AnimFinishedConnection;

	public:
		AnimatedSpriteComponent(BaseEntity* pEntity_);
		virtual ~AnimatedSpriteComponent();

		CColor GetColor() const;
		void SetColor(CColor val);
		eSpriteEffects GetSpriteEffect() const;
		void SetSpriteEffect(eSpriteEffects val);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		void SetCurrentAnimation(int index_);
		bool SetCurrentAnimation(std::string name_);
		bool SetCurrentAnimation(const char *name_);
		std::string GetCurrentFrameName();
		Animation2D *GetCurrentAnimation();

		void AddAnimation(Animation2D *pAnim_);
		std::vector<Animation2D*>& GetAnimations();

		//Event
		bool OnFrameChanged(const EventArgs &e);
		bool OnAnimationFinished(const EventArgs &e);
	};
}

#endif
