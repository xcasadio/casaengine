#include "Base.h"
#include "Entities/BaseEntity.h"

#include "AnimatedSpriteComponent.h"
#include "Animations/Animation2D.h"
#include "Assets/AssetManager.h"
#include "Entities/ComponentTypeEnum.h"

#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/Matrix4.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Transform3DComponent.h"
#include "EventHandler/Event.h"

#include <string>
#include <BulletCollision/CollisionShapes/btBoxShape.h>

#include "Physics/Bullet/BulletObjectsContainer.h"


namespace CasaEngine
{
	AnimatedSpriteComponent::AnimatedSpriteComponent(BaseEntity* pEntity_)
		: Component(pEntity_, ANIMATED_SPRITE),
		m_pSpriteRenderer(nullptr),
		m_pTransform(nullptr),
		m_Color(Color::White),
		m_SpriteEffect(eSpriteEffects::SPRITE_EFFECT_NONE),
		m_pCurrentAnim(nullptr)
	
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
		return m_Color;
	}

	void AnimatedSpriteComponent::SetColor(Color val)
	{
		m_Color = val;
	}

	eSpriteEffects AnimatedSpriteComponent::GetSpriteEffect() const
	{
		return m_SpriteEffect;
	}

	void AnimatedSpriteComponent::SetSpriteEffect(eSpriteEffects val)
	{
		m_SpriteEffect = val;
	}

	void AnimatedSpriteComponent::SetCurrentAnimation(int index_, bool forceReset)
	{
		// if the animation is already set we do nothing
		if (m_pCurrentAnim != nullptr
			/*&& m_pCurrentAnim->ID() == m_AnimationList[index_]->ID()*/
			&& m_pCurrentAnim->GetAnimationData()->GetName() == m_AnimationList[index_]->GetAnimationData()->GetName())
		{
			if (forceReset)
			{
				m_pCurrentAnim->Reset();
			}

			return;
		}

		if (m_pCurrentAnim != nullptr)
		{
			//if (m_FrameChangedConnection.isValid() == true)
			{
				m_FrameChangedConnection->disconnect();
			}

			//if (m_AnimFinishedConnection.isValid() == true)
			{
				m_AnimFinishedConnection->disconnect();
			}
		}

		m_pCurrentAnim = m_AnimationList[index_];
		m_pCurrentAnim->Reset();

		m_FrameChangedConnection = m_pCurrentAnim->subscribeEvent(FrameChangeEvent::GetEventName(),
			Event::Subscriber(&AnimatedSpriteComponent::OnFrameChanged, this));

		m_AnimFinishedConnection = m_pCurrentAnim->subscribeEvent(AnimationFinishedEvent::GetEventName(),
			Event::Subscriber(&AnimatedSpriteComponent::OnAnimationFinished, this));
	}

	bool AnimatedSpriteComponent::SetCurrentAnimation(const char * name_, bool forceReset)
	{
		return SetCurrentAnimation(std::string(name_));
	}

	bool AnimatedSpriteComponent::SetCurrentAnimation(std::string name, bool forceReset)
	{
		for (unsigned int i = 0; i < m_AnimationList.size(); i++)
		{
			if (m_AnimationList[i]->GetAnimationData()->GetName() == name)
			{
				SetCurrentAnimation(i, forceReset);
				return true;
			}
		}

		return false;
	}


	std::string AnimatedSpriteComponent::GetCurrentFrameName()
	{
		if (m_pCurrentAnim == nullptr)
		{
			return "";
		}

		return m_pCurrentAnim->CurrentFrame();
	}

	int AnimatedSpriteComponent::GetCurrentFrameIndex() const
	{
		if (m_pCurrentAnim == nullptr)
		{
			return -1;
		}

		int i = 0;
		for (const auto& frame : m_pCurrentAnim->GetAnimation2DData()->GetFrames())
		{
			if (frame.GetSpriteId() == m_pCurrentAnim->CurrentFrame())
			{
				return i;
			}

			i++;
		}

		return -1;
	}

	Animation2D* AnimatedSpriteComponent::GetCurrentAnimation()
	{
		return m_pCurrentAnim;
	}

	void AnimatedSpriteComponent::Initialize()
	{
		m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr, "AnimatedSpriteComponent::Initialize() can't find the component SpriteRenderer");

		m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(m_pTransform != nullptr, "AnimatedSpriteComponent::Initialize() can't find the Transform2DComponent. Please add it before add a AnimatedSpriteComponent");

		if (Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld() != nullptr)
		{
			//TODO : create all shapes from collisions
			for (auto* animation : m_AnimationList)
			{
				for (auto& frame : dynamic_cast<Animation2DData*>(animation->GetAnimationData())->GetFrames())
				{
					for (auto& collision : Game::Instance().GetAssetManager().GetAsset<SpriteData>(frame.GetSpriteId())->GetCollisions())
					{
						if (collision.GetType() == Defense)
						{
							continue;
						}

						auto* shape = collision.GetShape();
						if (shape->Type() == ShapeType::RECTANGLE) // TODO: conflict between RectangleI et Rectangle
						{
							const auto* pBox2D = dynamic_cast<const RectangleI*>(shape);
							if (pBox2D != nullptr)
							{
								shape = new Rectangle(pBox2D->x, pBox2D->y, pBox2D->w, pBox2D->h);								
							}
						}

						auto* pObj = Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->CreateCollisionShape(shape, Vector3::Zero());
						auto* bullet_collision_object_container = dynamic_cast<BulletCollisionObjectContainer*> (pObj);
						auto* bt_collision_object = bullet_collision_object_container->GetCollisionObject();
						bt_collision_object->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
						bt_collision_object->setUserPointer(GetEntity());

						if (m_CollisionObjectByFrameId.find(frame.GetSpriteId()) == m_CollisionObjectByFrameId.end())
						{
							m_CollisionObjectByFrameId[frame.GetSpriteId()] = std::vector<ICollisionObjectContainer*>();
						}

						m_CollisionObjectByFrameId[frame.GetSpriteId()].push_back(pObj);
					}
				}
			}
			
		}
	}

	void AnimatedSpriteComponent::Update(const GameTime& gameTime_)
	{
		if (m_pCurrentAnim != nullptr)
		{
			m_pCurrentAnim->Update(gameTime_.FrameTime());
		}
	}

	void AnimatedSpriteComponent::Draw()
	{
		if (m_pCurrentAnim != nullptr)
		{
			auto worldMatrix  = m_pTransform->GetWorldMatrix();
			m_pSpriteRenderer->AddSprite(
				//TODO : load all sprites in a dictionary<name, sprite>
				new Sprite(*Game::Instance().GetAssetManager().GetAsset<SpriteData>(m_pCurrentAnim->CurrentFrame())),
				worldMatrix,
				m_Color,
				m_SpriteEffect);
		}
	}

	/*void AnimatedSpriteComponent::HandleEvent(const Event* pEvent_)
	{

	}*/

	void AnimatedSpriteComponent::AddAnimation(Animation2D* pAnim_)
	{
		pAnim_->Initialize();
		m_AnimationList.push_back(pAnim_);
	}

	std::vector<Animation2D *>& AnimatedSpriteComponent::GetAnimations()
	{
		return m_AnimationList;
	}

	bool AnimatedSpriteComponent::OnFrameChanged(const EventArgs& e)
	{
		const auto& event = static_cast<const FrameChangeEvent&>(e);

		if (Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld() != nullptr)
		{
			if (!m_LastFrameId.empty())
			{
				if (m_CollisionObjectByFrameId.find(m_LastFrameId) != m_CollisionObjectByFrameId.end())
				{
					for (auto* collObj : m_CollisionObjectByFrameId[m_LastFrameId])
					{
						Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->RemoveCollisionObject(collObj);
					}
				}
			}

			if (m_CollisionObjectByFrameId.find(event.ID()) != m_CollisionObjectByFrameId.end())
			{
				auto* transform_3d_component = this->GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
				auto translation = transform_3d_component->GetWorldMatrix().Translation();
				auto sprite_data = Game::Instance().GetAssetManager().GetAsset<SpriteData>(event.ID());

				for (auto* collObj : m_CollisionObjectByFrameId[event.ID()])
				{
					auto* bullet_collision_object_container = dynamic_cast<BulletCollisionObjectContainer*> (collObj);
					auto* bt_collision_object = bullet_collision_object_container->GetCollisionObject();
					//TODO : pour les box shape, bullet fonctionne en moité de longueur 
					/*if (bt_collision_object->getCollisionShape() != nullptr)
					{
						auto* bt_box_shape = static_cast<btBoxShape*>(bt_collision_object->getCollisionShape());
						if (bt_box_shape != nullptr)
						{
							auto half_extents_with_margin = bt_box_shape->getHalfExtentsWithMargin();
							translation.x -= half_extents_with_margin.x();
							translation.y -= half_extents_with_margin.y();
						}
					}*/				
					bt_collision_object->getWorldTransform().setOrigin(btVector3(translation.x - sprite_data->GetOrigin().x, translation.y - sprite_data->GetOrigin().y, translation.z));
					Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddCollisionObject(collObj);
				}

			}
		}

		m_LastFrameId = event.ID();

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
