#include "ScriptCharacter.h"

ScriptCharacter::ScriptCharacter(BaseEntity* entity_, Character* character) :
	IScriptObject(entity_), _character(character)
{
}

ScriptCharacter::~ScriptCharacter()
{
}

void ScriptCharacter::OnInitialize()
{
	_character->Initialize();
}

void ScriptCharacter::OnUpdate(const GameTime& gameTime_)
{
	_character->Update(gameTime_);
}

bool ScriptCharacter::HandleMessage(const Telegram& msg)
{
	return false;
}

void ScriptCharacter::OnDestroy()
{
}