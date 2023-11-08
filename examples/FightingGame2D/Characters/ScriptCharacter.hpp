#pragma once

#include  "Character.hpp"
#include  "Script/IScriptObject.hpp"
#include  "GameTime.hpp"
#include  "Messaging/Telegram.hpp"

using namespace CasaEngine;

class ScriptCharacter :
	public IScriptObject
{
public:
	ScriptCharacter(BaseEntity* entity, Character* character);
	~ScriptCharacter() override;

	void OnInitialize() override;
	void OnUpdate(const GameTime& gameTime_) override;
	bool HandleMessage(const Telegram& msg) override;
	void OnDestroy() override;

private:
	Character* _character;
};
