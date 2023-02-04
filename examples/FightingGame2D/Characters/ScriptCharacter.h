#pragma once

#include "Character.h"
#include "Script/IScriptObject.h"
#include "GameTime.h"
#include "Messaging/Telegram.h"

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
