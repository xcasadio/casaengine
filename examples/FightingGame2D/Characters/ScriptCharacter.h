#ifndef SCRIPTPLAYER_H_
#define SCRIPTPLAYER_H_

#include "Character.h"
#include "Script\IScriptObject.h"

using namespace CasaEngine;

class ScriptCharacter :
	public IScriptObject
{
public:
	static const ScriptObjectClassID ClassID;

public:
	ScriptCharacter(BaseEntity* pEntity_, Character* pCharacter);
	~ScriptCharacter();

	void OnInitialize() override;
	void OnUpdate(const GameTime& gameTime_) override;
	void OnDestroy() override;

private:
	Character* m_pCharacter;
};

#endif
