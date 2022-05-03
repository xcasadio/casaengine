#pragma once

#include "Character.h"
#include "Script\IScriptObject.h"

using namespace CasaEngine;

class ScriptCharacter :
	public IScriptObject
{
public:
	static const ScriptObjectClassID ClassID;

public:
	ScriptCharacter(BaseEntity* entity, Character* character);
	~ScriptCharacter() override;

	void OnInitialize() override;
	void OnUpdate(const GameTime& gameTime_) override;
	bool HandleMessage(const Telegram& msg) override;
	void OnDestroy() override;

	Character* GetCharacter();

private:
	Character* _character;
};
