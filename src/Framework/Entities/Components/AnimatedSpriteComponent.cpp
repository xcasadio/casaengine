#include <string>

#include "AnimatedSpriteComponent.h"
#include "Base.h"
#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"
#include "Entities/BaseEntity.h"
#include "Entities/ComponentTypeEnum.h"
#include "EventHandler/Event.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/Matrix4.h"
#include "Sprite/SpritePhysicsHelper.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "../Events/BaseEntityEvents.h"


namespace CasaEngine
{
	AnimatedSpriteComponent::AnimatedSpriteComponent(BaseEntity* entity_)
		: Component(entity_, ANIMATED_SPRITE),
		_spriteRenderer(nullptr),
		_color(Color::White),
		_spriteEffect(eSpriteEffects::SPRITE_EFFECT_NONE),
		_currentAnim(nullptr)
	
	{
		addEvent(FrameChangeEvent::GetEventName());
		addEvent(AnimationFinishedEvent::GetEventName());
	}

	/*
	std::string AnimatedSpriteComponent::GetSpriteID() const
	{
		return m_SpriteID;
	}

	void AnimatedSpriteComponent::GetSpriteID(std::string val)
	{
		m_SpriteID = val;
	}*/

	Color AnimatedSpriteComponent::GetColor() const
	{
		return _color;
	}

	void AnimatedSpriteComponent::SetColor(Color val)
	{
		_color = val;
	}

	eSpriteEffects AnimatedSpriteComponent::GetSpriteEffect() const
	{
		return _spriteEffect;
	}

	void AnimatedSpriteComponent::SetSpriteEffect(eSpriteEffects val)
	{
		_spriteEffect = val;
	}

	void AnimatedSpriteComponent::SetCurrentAnimation(Animation2D* anim, bool forceReset)
	{
		if (_currentAnim != nullptr
			&& _currentAnim->GetAnimationData()->GetName() == anim->GetAnimationData()->GetName())
		{
			if (forceReset)
			{
				_currentAnim->Reset();
			}

			return;
		}

		if (_currentAnim != nullptr)
		{
			//if (_frameChangedConnection.isValid() == true)
			{
				_frameChangedConnection->disconnect();
			}

			//if (_animFinishedConnection.isValid() == true)
			{
				_animFinishedConnection->disconnect();
			}
		}

		_currentAnim = anim;
		_currentAnim->Reset();

		_frameChangedConnection = _currentAnim->subscribeEvent(FrameChangeEvent::GetEventName(),
			Event::Subscriber(&AnimatedSpriteComponent::OnFrameChanged, this));

		_animFinishedConnection = _currentAnim->subscribeEvent(AnimationFinishedEvent::GetEventName(),
			Event::Subscriber(&AnimatedSpriteComponent::OnAnimationFinished, this));
	}

	void AnimatedSpriteComponent::SetCurrentAnimation(int index_, bool forceReset)
	{
		SetCurrentAnimation(_animationList[index_], forceReset);
	}

	bool AnimatedSpriteComponent::SetCurrentAnimation(const char * name_, bool forceReset)
	{
		return SetCurrentAnimation(std::string(name_));
	}

	bool AnimatedSpriteComponent::SetCurrentAnimation(const std::string& name, bool forceReset)
	{
		for (const auto& anim : _animationList)
		{
			if (anim->GetAnimationData()->GetName() == name)
			{
				SetCurrentAnimation(anim, forceReset);
				return true;
			}
		}

		return false;
	}


	std::string AnimatedSpriteComponent::GetCurrentFrameName()
	{
		if (_currentAnim == nullptr)
		{
			return "";
		}

		return _currentAnim->CurrentFrame();
	}

	int AnimatedSpriteComponent::GetCurrentFrameIndex() const
	{
		if (_currentAnim == nullptr)
		{
			return -1;
		}

		int i = 0;
		for (const auto& frame : _currentAnim->GetAnimation2DData()->_frames)
		{
			if (frame._spriteId == _currentAnim->CurrentFrame())
			{
				return i;
			}

			i++;
		}

		return -1;
	}

	Animation2D* AnimatedSpriteComponent::GetCurrentAnimation()
	{
		return _currentAnim;
	}

	void AnimatedSpriteComponent::Initialize()
	{
		_spriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(_spriteRenderer != nullptr, "AnimatedSpriteComponent::Initialize() can't find the component SpriteRenderer");

		if (Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld() != nullptr)
		{
			for (auto* animation : _animationList)
			{
				for (auto& frame : dynamic_cast<Animation2DData*>(animation->GetAnimationData())->_frames)
				{
					if (_collisionObjectByFrameId.find(frame._spriteId) != _collisionObjectByFrameId.end())
					{
						continue; // already added
					}

					_collisionObjectByFrameId[frame._spriteId] = SpritePhysicsHelper::CreateCollisionsFromSprite(frame._spriteId, GetEntity());
				}
			}
		}
	}

	void AnimatedSpriteComponent::Update(const GameTime& gameTime_)
	{
		if (_currentAnim != nullptr)
		{
			_currentAnim->Update(gameTime_.FrameTime());
		}
	}

	void AnimatedSpriteComponent::Draw()
	{
		if (_currentAnim != nullptr)
		{
			auto worldMatrix  = GetEntity()->GetCoordinates().GetWorldMatrix();
			_spriteRenderer->AddSprite(
				//TODO : load all sprites in a dictionary<name, sprite>
				new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(_currentAnim->CurrentFrame())),
				worldMatrix,
				_color,
				_spriteEffect);
		}
	}

	/*void AnimatedSpriteComponent::HandleEvent(const Event* pEvent_)
	{

	}*/

	void AnimatedSpriteComponent::AddAnimation(Animation2D* pAnim_)
	{
		pAnim_->Initialize();
		_animationList.push_back(pAnim_);
	}

	std::vector<Animation2D *>& AnimatedSpriteComponent::GetAnimations()
	{
		return _animationList;
	}

	void AnimatedSpriteComponent::RemoveCollisionsFromLastFrame()
	{
		if (_collisionObjectByFrameId.find(_lastFrameId) != _collisionObjectByFrameId.end())
		{
			for (auto* collObj : _collisionObjectByFrameId[_lastFrameId])
			{
				Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->RemoveCollisionObject(collObj);
			}
		}
	}

	bool AnimatedSpriteComponent::OnFrameChanged(const EventArgs& e)
	{
		const auto& event = static_cast<const FrameChangeEvent&>(e);

		if (Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld() != nullptr)
		{
			RemoveCollisionsFromLastFrame();

			if (_collisionObjectByFrameId.find(event.ID()) != _collisionObjectByFrameId.end())
			{
				SpritePhysicsHelper::AddCollisionsFromSprite(GetEntity()->GetCoordinates().GetWorldMatrix().Translation(), event.ID(), _collisionObjectByFrameId[event.ID()]);
			}

			_lastFrameId = event.ID();
		}

		fireEvent(FrameChangeEvent::GetEventName(), const_cast<EventArgs&>(e));

		return false;
	}

	bool AnimatedSpriteComponent::OnAnimationFinished(const EventArgs& e)
	{
		//const AnimationFinishedEvent &event = static_cast<const AnimationFinishedEvent&>(e);
		fireEvent(AnimationFinishedEvent::GetEventName(), const_cast<EventArgs&>(e));
		return false;
	}
}
