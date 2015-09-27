#ifndef PLAYERCONTROLLER_H_
#define PLAYERCONTROLLER_H_

#include "IController.h"
#include "GameTime.h"
#include "Export.h"
#include "AI\FSM\StateMachine.h"
#include "AI\FSM\IState.h"
#include <map>
#include "CharacterEnum.h"
#include "Maths\Vector2.h"
#include "Hero.h"
#include "CompilationMacro.h"


using namespace CasaEngine;

typedef unsigned int PlayerIndex;

/**
 * 
 */
class PlayerController :
	public IController
{
public:
	PlayerController(Hero *pHero, PlayerIndex index_);
	~PlayerController();

	void Initialize() OVERRIDE;
	void Update( const GameTime elapsedTime_ ) OVERRIDE;

	Hero *GetHero() const;

	bool IsAttackButtonJustPressed();
	bool IsAttackButtonPressed();

	Orientation GetDirectionFromInput(Vector2F& direction_);

private:
	PlayerIndex m_PlayerIndex;
	Hero *m_pHero;
};

#endif // PLAYERCONTROLLER_H_