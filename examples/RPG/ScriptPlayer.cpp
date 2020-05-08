
#include "Base.h"
#include "ScriptPlayer.h"
#include "Game\Game.h"
#include "CA_Assert.h"
#include "PlayerStates.h"
#include "AI\Messaging\Telegram.h"
#include "MessageType.h"
#include "Entities\Events\BaseEntityEvents.h"
#include "EventHandler\Event.h"

const ScriptObjectClassID ScriptPlayer::ClassID(0xC299A4EE);

/**
 * 
 */
ScriptPlayer::ScriptPlayer(BaseEntity *pEntity_) :
	IScriptObject(pEntity_)
{
}

/**
 * 
 */
ScriptPlayer::~ScriptPlayer()
{

}

/**
 * 
 */
void ScriptPlayer::OnInitialize()
{
	AnimatedSpriteComponent *pAnimatedSprite_ = GetEntity()->GetComponentMgr()->GetComponent<AnimatedSpriteComponent>();
	CA_ASSERT(pAnimatedSprite_ != nullptr);

	//TODO select character

	m_pHero = ::new Hero(pAnimatedSprite_);
	m_pHero->Initialize();
}

/**
 * 
 */
void ScriptPlayer::OnUpdate(const GameTime& gameTime_)
{
	m_pHero->Update(gameTime_);
}

/**
 * 
 */
void ScriptPlayer::OnDestroy()
{
	
}
