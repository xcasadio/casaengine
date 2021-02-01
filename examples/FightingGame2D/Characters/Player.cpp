#include "Base.h"
#include "Player.h"
#include "PlayerController.h"


Player::Player(BaseEntity* pEntity) :
	Character(pEntity)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	SetController(::new PlayerController(this, 0));
	Character::Initialize();
}
