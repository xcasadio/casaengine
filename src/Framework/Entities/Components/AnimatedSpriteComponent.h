#pragma once

#include <string>
#include <vector>
#include <map>

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

namespace CasaEngine
{
	class CA_EXPORT AnimatedSpriteComponent :
		public Component,
		public EventSet
	{
	private:
		SpriteRenderer*	m_pSpriteRenderer;
		Transform3DComponent* m_pTransform;
		Color m_Color;		
		eSpriteEffects m_SpriteEffect;
		Animation2D *m_pCurrentAnim;

		std::vector<Animation2D *> m_AnimationList;

		Event::Connection m_FrameChangedConnection;
		Event::Connection m_AnimFinishedConnection;

		std::map<std::string, std::vector<ICollisionObjectContainer*>> m_CollisionObjectByFrameId;
		std::string m_LastFrameId;

	public:
		AnimatedSpriteComponent(BaseEntity* pEntity_);

		Color GetColor() const;
		void SetColor(Color val);
		eSpriteEffects GetSpriteEffect() const;
		void SetSpriteEffect(eSpriteEffects val);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		//all entities can communicate using messages. They are sent
		//using the MessageDispatcher singleton class
		//void HandleEvent(const Event* pEvent_);

		void SetCurrentAnimation(int index_, bool forceReset = false);
		bool SetCurrentAnimation(std::string name, bool forceReset = false);
		bool SetCurrentAnimation(const char *name_, bool forceReset = false);
		std::string GetCurrentFrameName();
		int GetCurrentFrameIndex() const;
		Animation2D *GetCurrentAnimation();

		void AddAnimation(Animation2D *pAnim_);
		std::vector<Animation2D*>& GetAnimations();

		//Event
		bool OnFrameChanged(const EventArgs &e);
		bool OnAnimationFinished(const EventArgs &e);
	};
}
