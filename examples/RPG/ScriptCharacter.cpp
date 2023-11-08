#include  "ScriptCharacter.hpp"

ScriptCharacter::ScriptCharacter(BaseEntity* entity, Character* character) :
	IScriptObject(entity),
	_character(character)
{
}

ScriptCharacter::~ScriptCharacter() = default;

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
	return _character->HandleMessage(msg);
}

void ScriptCharacter::OnDestroy()
{
}

Character* ScriptCharacter::GetCharacter()
{
	return _character;
}