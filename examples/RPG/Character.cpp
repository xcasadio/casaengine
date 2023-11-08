#include  "Base.hpp"
#include  "Character.hpp"
#include  "CharacterEnum.hpp"
#include  "CA_Assert.hpp"
#include  "PlayerController.hpp"
#include  "ScriptCharacter.hpp"
#include  "Log/LogManager.hpp"
#include  "Entities/Events/BaseEntityEvents.hpp"
#include  "EventHandler/Event.hpp"
#include  "Assets/AssetManager.hpp"
#include  "Entities/Physics/PhysicalEntity.hpp"
#include  "AI/MovementSystem/MovementRequest.hpp"
#include  "Entities/Events/BaseEntityEvents.hpp"
#include  "EventHandler/Event.hpp"
#include  "GameDatas/MessageType.hpp"
#include  "Entities/Components/ScriptComponent.hpp"
#include <Physics/CollisionParametersBetween2Entities.hpp>


Character::Character(BaseEntity* pEntity) :
	Character2DBase(pEntity)
{
	SetAnimationDirectionOffset(Orientation::DOWN, static_cast<int>(AnimationDirectionOffset::DOWN));
	//SetAnimationDirectionOffset(DOWN_LEFT, static_cast<int>(AnimationDirectionOffset::DOWN_LEFT));
	//SetAnimationDirectionOffset(DOWN_RIGHT, static_cast<int>(AnimationDirectionOffset::DOWN_RIGHT));
	SetAnimationDirectionOffset(Orientation::RIGHT, static_cast<int>(AnimationDirectionOffset::RIGHT));
	SetAnimationDirectionOffset(Orientation::LEFT, static_cast<int>(AnimationDirectionOffset::LEFT));
	SetAnimationDirectionOffset(Orientation::UP, static_cast<int>(AnimationDirectionOffset::UP));
	//SetAnimationDirectionOffset(UP_LEFT, static_cast<int>(AnimationDirectionOffset::UP_LEFT));
	//SetAnimationDirectionOffset(UP_RIGHT, static_cast<int>(AnimationDirectionOffset::UP_RIGHT));
	SetAnimationParameters(4, -1);
}

Character::~Character() = default;

void Character::Initialize()
{
	Character2DBase::Initialize();

	m_HPMax = 100;
	m_HPMaxOffSet = 0;
	m_HPOffSet = 0;
	m_MPMax = 100;
	m_MPMaxOffSet = 0;
	m_MPOffSet = 0;
	m_Strength = 10;
	m_StrengthOffSet = 0;
	m_DefenseOffSet = 0;

	m_HP = m_HPMax;
	m_MP = m_MPMax;

	m_ComboNumber = 0;
}

void Character::Update(const GameTime& gameTime)
{
	Character2DBase::Update(gameTime);
}

void Character::Draw()
{
}

bool Character::IsDead() const
{
	return m_HP <= 0;
}

void Character::CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters)
{
	//hit by other
	if (collisionParameters->GetCollision()->GetType() == CollisionHitType::Defense
		&& otherCollisionParameters->GetCollision()->GetType() == CollisionHitType::Attack)
	{
		auto* scriptComponent = otherEntity->GetComponentMgr()->GetComponent<ScriptComponent>();
		if (scriptComponent != nullptr)
		{
			auto* script_character = dynamic_cast<ScriptCharacter*>(scriptComponent->GetScriptObject());

			if (script_character != nullptr)
			{
				auto* otherCharacter = script_character->GetCharacter();

				//state hit
				//HitBy(otherCharacter);
			}
		}
	}
	//hit other
	else if (collisionParameters->GetCollision()->GetType() == CollisionHitType::Attack
		&& otherCollisionParameters->GetCollision()->GetType() == CollisionHitType::Defense)
	{
		auto* scriptComponent = otherEntity->GetComponentMgr()->GetComponent<ScriptComponent>();
		if (scriptComponent != nullptr)
		{
			auto* scriptObject = scriptComponent->GetScriptObject();
			if (scriptObject != nullptr)
			{
				//Hit(scriptObject); // par exemple tile
			}
		}
		/*auto* tileMap = otherEntity->GetComponentMgr()->GetComponent<TiledMapComponent>();
		//tileMap->
		auto* tile = otherEntity->GetComponentMgr()->GetComponent<TiledComponent>();
		if (tile->IsDesctructible())
		{

		}*/
	}

	//si je suis une arme alors c'est le parent que je dois invoquer
	//creer un character pour l'arme du coup
	//TODO : creer GetScriptObject pour l'arme qui appelera le character parent
	if (otherEntity->GetParent() != nullptr)
	{
		otherEntity = otherEntity->GetParent();
	}

	auto* scriptComponent = otherEntity->GetComponentMgr()->GetComponent<ScriptComponent>();
	if (scriptComponent != nullptr)
	{
		auto* script_character = dynamic_cast<ScriptCharacter*>(scriptComponent->GetScriptObject());

		if (script_character != nullptr)
		{
			auto* otherCharacter = script_character->GetCharacter();


		}
	}
}
