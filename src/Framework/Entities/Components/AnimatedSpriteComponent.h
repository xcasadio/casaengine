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
		SpriteRenderer*	_spriteRenderer;
		Color _color;		
		eSpriteEffects _spriteEffect;
		Animation2D *_currentAnim;

		std::vector<Animation2D *> _animationList;

		Event::Connection _frameChangedConnection;
		Event::Connection _animFinishedConnection;

		std::map<std::string, std::vector<ICollisionObjectContainer*>> _collisionObjectByFrameId;
		std::string _lastFrameId;

	public:
		AnimatedSpriteComponent(BaseEntity* entity_);

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

		void SetCurrentAnimation(Animation2D *anim, bool forceReset = false);
		void SetCurrentAnimation(int index_, bool forceReset = false);
		bool SetCurrentAnimation(const std::string& name, bool forceReset = false);
		bool SetCurrentAnimation(const char *name_, bool forceReset = false);
		std::string GetCurrentFrameName();
		int GetCurrentFrameIndex() const;
		Animation2D *GetCurrentAnimation();

		void AddAnimation(Animation2D *pAnim_);
		std::vector<Animation2D*>& GetAnimations();
		void RemoveCollisionsFromLastFrame();

		//Event
		bool OnFrameChanged(const EventArgs &e);
		bool OnAnimationFinished(const EventArgs &e);
	};
}
