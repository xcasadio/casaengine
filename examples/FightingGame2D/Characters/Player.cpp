#include  "Base.hpp"
#include  "Player.hpp"
#include  "PlayerController.hpp"


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
