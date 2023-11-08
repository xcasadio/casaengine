#pragma once

#include <string>
#include <vector>
#include <map>

#include "CA_Export.hpp"
#include  "Entities/Component.hpp"
#include  "GameTime.hpp"
#include  "Graphics/Color.hpp"
#include  "Sprite/SpriteRenderer.hpp"
#include  "Sprite/SpriteTypes.hpp"
#include  "Animations/Animation2D.hpp"
#include  "EventHandler/EventSet.hpp"
#include  "EventHandler/Event.hpp"
#include  "Physics/PhysicsObjectContainer.hpp"

namespace CasaEngine
{
	class CA_EXPORT AnimatedSpriteComponent :
		public Component,
		public EventSet
	{
	private:
		SpriteRenderer* _spriteRenderer;
		Color _color;
		eSpriteEffects _spriteEffect;
		Animation2D* _currentAnim;

		std::vector<Animation2D*> _animationList;

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

		void SetCurrentAnimation(Animation2D* anim, bool forceReset = false);
		void SetCurrentAnimation(int index_, bool forceReset = false);
		bool SetCurrentAnimation(const std::string& name, bool forceReset = false);
		bool SetCurrentAnimation(const char* name_, bool forceReset = false);
		std::string GetCurrentFrameName();
		int GetCurrentFrameIndex() const;
		Animation2D* GetCurrentAnimation();

		void AddAnimation(Animation2D* pAnim_);
		std::vector<Animation2D*>& GetAnimations();
		void RemoveCollisionsFromLastFrame();

		//Event
		bool OnFrameChanged(const EventArgs& e);
		bool OnAnimationFinished(const EventArgs& e);
	};
}
