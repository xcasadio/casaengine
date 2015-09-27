#ifndef SCRIPTPLAYER_H_
#define SCRIPTPLAYER_H_


#include "Entities\BaseEntity.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "Export.h"
#include "GameTime.h"
#include "Hero.h"
#include "Maths\Vector2.h"
#include "PlayerController.h"
#include "Script\IScriptObject.h"
#include "CompilationMacro.h"

using namespace CasaEngine;


/**
 * 
 */
class GAMEPLAYDLL_EXPORT ScriptPlayer : 
	public IScriptObject
{
public:
	static const ScriptObjectClassID ClassID;

public:
	ScriptPlayer(BaseEntity *pEntity_);
	~ScriptPlayer();

	void OnInitialize() OVERRIDE;
	void OnUpdate(const GameTime& gameTime_) OVERRIDE;
	void OnDestroy() OVERRIDE;

private:
	
	Hero *m_pHero;
};

#endif // SCRIPTPLAYER_H_