#include  "Base.hpp"
#include  "Enemy.hpp"
#include  "EnemyController.hpp"

/**
 *
 */
Enemy::Enemy(BaseEntity* pEntity) :
	Character(pEntity)
{
}

/**
 *
 */
Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	SetController(::new EnemyController(this));
	Character::Initialize();
}