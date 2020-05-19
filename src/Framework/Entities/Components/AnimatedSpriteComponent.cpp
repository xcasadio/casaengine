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
#include "Resources/ResourceManager.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "StringUtils.h"
#include "Transform3DComponent.h"
#include "EventHandler/Event.h"

#include <string>


namespace CasaEngine
{

	/**
	 *
	 */
	AnimatedSpriteComponent::AnimatedSpriteComponent(BaseEntity* pEntity_)
		: Component(pEntity_, ANIMATED_SPRITE),
		m_pSpriteRenderer(nullptr),
		m_pTransform(nullptr),
		m_pCurrentAnim(nullptr),
		m_SpriteEffect(SPRITE_EFFECT_NONE),
		m_Color(CColor::White)
	{
		addEvent(FrameChangeEvent::GetEventName());
		addEvent(AnimationFinishedEvent::GetEventName());
	}

	/**
	 *
	 */
	AnimatedSpriteComponent::~AnimatedSpriteComponent()
	{
		/*std::vector<btCollisionObject *>::iterator itColObj;
		for (itColObj = m_LastSpriteCollisionObjects.begin();
			itColObj != m_LastSpriteCollisionObjects.end();
			itColObj++)
		{
			delete *itColObj;
		}*/
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

	CColor AnimatedSpriteComponent::GetColor() const
	{
		return m_Color;
	}

	void AnimatedSpriteComponent::SetColor(CColor val)
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

	void AnimatedSpriteComponent::SetCurrentAnimation(int index_)
	{
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

		// if the animation is already set we do nothing
		if (m_pCurrentAnim != nullptr
			/*&& m_pCurrentAnim->ID() == m_AnimationList[index_]->ID()*/
			&& m_pCurrentAnim->GetName() == m_AnimationList[index_]->GetName())
		{
			return;
		}

		m_pCurrentAnim = m_AnimationList[index_];
		m_pCurrentAnim->Reset();

		m_FrameChangedConnection = m_pCurrentAnim->subscribeEvent(FrameChangeEvent::GetEventName(),
			Event::Subscriber(&AnimatedSpriteComponent::OnFrameChanged, this));

		m_AnimFinishedConnection = m_pCurrentAnim->subscribeEvent(AnimationFinishedEvent::GetEventName(),
			Event::Subscriber(&AnimatedSpriteComponent::OnAnimationFinished, this));
	}

	/**
	 *
	 */
	void AnimatedSpriteComponent::SetCurrentAnimation(std::string name_)
	{
		for (unsigned int i = 0; i < m_AnimationList.size(); i++)
		{
			if (m_AnimationList[i]->GetName() == name_)
			{
				SetCurrentAnimation(i);
				break;
			}
		}
	}

	void AnimatedSpriteComponent::Initialize()
	{
		m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
		CA_ASSERT(m_pSpriteRenderer != nullptr, "AnimatedSpriteComponent::Initialize() can't find the component SpriteRenderer");

		m_pTransform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
		CA_ASSERT(m_pTransform != nullptr, "AnimatedSpriteComponent::Initialize() can't find the Transform2DComponent. Please add it before add a AnimatedSpriteComponent");
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
			m_pSpriteRenderer->AddSprite(
				Game::Instance().GetAssetManager().GetAsset<Sprite>(m_pCurrentAnim->CurrentFrame()),
				m_pTransform->GetWorldMatrix(),
				m_Color,
				m_pTransform->GetWorldMatrix().GetTranslation().z,
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

	bool AnimatedSpriteComponent::OnFrameChanged(const EventArgs& e)
	{
		const FrameChangeEvent& event = static_cast<const FrameChangeEvent&>(e);

		//TODO : don't do this here
		//we need the position of the entity to set the right position
		//do it in the script ?

		/*Sprite *pNewSprite = Game::Instance().GetAssetManager().GetAsset<Sprite>(event.ID());

		std::vector<ICollisionObjectContainer *>::iterator itColObj;
		for (itColObj = m_LastSpriteCollisionObjects.begin();
			itColObj != m_LastSpriteCollisionObjects.end();
			itColObj++)
		{
			//delete (*itColObj)->getCollisionShape();
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->RemoveCollisionShape(*itColObj);
			DELETE_AO *itColObj;
		}
		m_LastSpriteCollisionObjects.clear();
		//TODO : keep shape

		///
		std::vector<IShape *>::iterator itShape;
		for (itShape = pNewSprite->GetCollisionShapeIterator();
			itShape != pNewSprite->GetCollisionShapeIteratorEnd();
			itShape++)
		{
			ICollisionObjectContainer *pObj =
				Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddCollisionShape(*itShape, Vector3F::Zero());
			m_LastSpriteCollisionObjects.push_back(pObj);
		}*/

		///
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
