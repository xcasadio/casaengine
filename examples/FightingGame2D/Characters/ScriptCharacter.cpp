#include "ScriptCharacter.h"

constexpr ScriptObjectClassID ScriptCharacter::ClassID(0xC299A4EE);

ScriptCharacter::ScriptCharacter(BaseEntity* entity_, Character* character) :
	IScriptObject(entity_), m_pCharacter(character)
{
}

ScriptCharacter::~ScriptCharacter()
{
}

void ScriptCharacter::OnInitialize()
{
	m_pCharacter->Initialize();
}

void ScriptCharacter::OnUpdate(const GameTime& gameTime_)
{
	m_pCharacter->Update(gameTime_);
}

bool ScriptCharacter::HandleMessage(const Telegram& msg)
{
	return false;
}

void ScriptCharacter::OnDestroy()
{
}