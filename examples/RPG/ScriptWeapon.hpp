#pragma once

#include  "Character.hpp"
#include  "Weapon.hpp"
#include  "Script/IScriptObject.hpp"

using namespace CasaEngine;

class ScriptWeapon :
	public IScriptObject
{
public:
	ScriptWeapon(BaseEntity* entity, Weapon* weapon);
	~ScriptWeapon() override;

	void OnInitialize() override;
	void OnUpdate(const GameTime& gameTime_) override;
	bool HandleMessage(const Telegram& msg) override;
	void OnDestroy() override;

	Weapon* GetWeapon();

private:
	Weapon* _weapon;
};
