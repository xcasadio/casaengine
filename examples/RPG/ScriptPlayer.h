#ifndef SCRIPTPLAYER_H_
#define SCRIPTPLAYER_H_


#include "Entities\BaseEntity.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "GameTime.h"
#include "Hero.h"
#include "Maths\Vector2.h"
#include "PlayerController.h"
#include "Script\IScriptObject.h"


using namespace CasaEngine;


/**
 * 
 */
class ScriptPlayer : 
	public IScriptObject
{
public:
	static const ScriptObjectClassID ClassID;

public:
	ScriptPlayer(BaseEntity *pEntity_);
	~ScriptPlayer();

	void OnInitialize() override;
	void OnUpdate(const GameTime& gameTime_) override;
	void OnDestroy() override;

private:
	
	Hero *m_pHero;
};

#endif // SCRIPTPLAYER_H_