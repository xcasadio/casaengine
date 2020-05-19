#include "Base.h"
#include "ScriptCharacter.h"

const ScriptObjectClassID ScriptCharacter::ClassID(0xC299A4EE);

/**
 * 
 */
ScriptCharacter::ScriptCharacter(BaseEntity *pEntity_, Character *pCharacter) :
	IScriptObject(pEntity_)
{
    m_pCharacter = pCharacter;
}

/**
 * 
 */
ScriptCharacter::~ScriptCharacter()
{

}

/**
 * 
 */
void ScriptCharacter::OnInitialize()
{
    
    m_pCharacter->Initialize();
}

/**
 * 
 */
void ScriptCharacter::OnUpdate(const GameTime& gameTime_)
{
    m_pCharacter->Update(gameTime_);
}

/**
 * 
 */
void ScriptCharacter::OnDestroy()
{
	
}
