#include "ScriptCharacter.h"

constexpr ScriptObjectClassID ScriptCharacter::ClassID(0xC299A4EE);

ScriptCharacter::ScriptCharacter(BaseEntity* pEntity_, Character* pCharacter) :
	IScriptObject(pEntity_),
	m_pCharacter(pCharacter)
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
	m_pCharacter->HandleMessage(msg);
}

void ScriptCharacter::OnDestroy()
{
}