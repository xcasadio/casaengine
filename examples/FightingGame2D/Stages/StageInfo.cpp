#include "Stage.h"


#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"

using namespace CasaEngine;

StageInfo::StageInfo(Stage* stage, BaseEntity* player1, BaseEntity* player2)
{
	m_pStage = stage;
	m_pPlayer1 = player1;
	m_pPlayer2 = player2;
}

BaseEntity* StageInfo::getPlayer1() const
{
	return m_pPlayer1;
}

BaseEntity* StageInfo::getPlayer2() const
{
	return m_pPlayer2;
}

Stage* StageInfo::getStage() const
{
	return m_pStage;
}
