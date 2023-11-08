#include  "Base.hpp"
#include  "Character.hpp"
#include  "Entities/Physics/PhysicalEntity.hpp"
#include  "GameDatas/MessageType.hpp"
#include  "Entities/BaseEntity.hpp"
#include  "GameTime.hpp"


Character::Character(BaseEntity* pEntity) :
	Character2DBase(pEntity)
{
	SetAnimationDirectionOffset(Orientation::LEFT, static_cast<int>(AnimationDirectionOffset::LEFT));
	SetAnimationDirectionOffset(Orientation::RIGHT, static_cast<int>(AnimationDirectionOffset::RIGHT));
	SetAnimationParameters(2, -1);
}

Character::~Character() = default;

void Character::Initialize()
{
	Character2DBase::Initialize();

	m_HPMax = 100;
	m_MPMax = 100;
	m_Speed = 300.0f;

	m_HP = m_HPMax;
	m_MP = m_MPMax;
}

void Character::Update(const GameTime& gameTime)
{
	Character2DBase::Update(gameTime);
}

void Character::Draw()
{
	Character2DBase::Draw();
}

void Character::CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters)
{

}

