#include "Stage.h"
#include "StageInfo.h"
#include "StageLayer.h"
#include "Entities/ComponentTypeEnum.h"
#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"

using namespace CasaEngine;

Stage::Stage(BaseEntity *entity) :
	Component(entity, CUSTOM_COMPONENT + 1)
{
	m_pSpriteRenderer = nullptr;
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	auto* layer1 = new StageLayer(this);
	layer1->AddTexture(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("plaines.png")));
	layer1->AddTexture(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("plaines.png")));
	layer1->AddTexture(Texture::loadTexture(Game::Instance().GetMediaManager().FindMedia("plaines.png")));
	m_Layers.push_back(layer1);
	m_pSpriteRenderer = Game::Instance().GetGameComponent<SpriteRenderer>();
}

void Stage::Update(const GameTime& gameTime_)
{
	
}

void Stage::Draw()
{
	auto* transform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
	
	Matrix4 matrix;
	matrix.Identity();
	float offsetX = 0;
	
	for (auto* layer : m_Layers)
	{
		layer->Draw(m_pSpriteRenderer);
	}
}

void Stage::SetStageInfo(StageInfo* stage_info)
{
	m_pInfo = stage_info;
}
