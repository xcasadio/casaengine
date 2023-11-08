#include  "ScriptWeapon.hpp"

ScriptWeapon::ScriptWeapon(BaseEntity* entity, Weapon* weapon) :
	IScriptObject(entity),
	_weapon(weapon)
{
}

ScriptWeapon::~ScriptWeapon() = default;

void ScriptWeapon::OnInitialize()
{
	_weapon->Initialize();
}

void ScriptWeapon::OnUpdate(const GameTime& gameTime_)
{
	//_weapon->Update(gameTime_);
}

bool ScriptWeapon::HandleMessage(const Telegram& msg)
{
	return _weapon->HandleMessage(msg);
}

void ScriptWeapon::OnDestroy()
{
}

Weapon* ScriptWeapon::GetWeapon()
{
	return _weapon;
}