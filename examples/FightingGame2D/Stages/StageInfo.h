#pragma once

#include "Entities/BaseEntity.h"

class Stage;

class StageInfo
{
public:
	StageInfo(Stage *stage, CasaEngine::BaseEntity* player1, CasaEngine::BaseEntity* player2);

	CasaEngine::BaseEntity* getPlayer1() const;
	CasaEngine::BaseEntity* getPlayer2() const;
	Stage* getStage() const;
	
	int width;
	int ground_height;
	int sky_height;

	int distance_before_split;

private:
	CasaEngine::BaseEntity* m_pPlayer1, * m_pPlayer2;
	Stage *m_pStage;
};
