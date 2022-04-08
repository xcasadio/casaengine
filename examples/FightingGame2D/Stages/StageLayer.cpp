#include "Stage.h"

#include "Entities/Components/Transform3DComponent.h"
#include "Game/Game.h"
#include "Sprite/SpriteRenderer.h"

using namespace CasaEngine;

StageLayer::StageLayer(Stage* stage)
{
	m_pStage = stage;
}

StageLayer::~StageLayer()
{
}

void StageLayer::AddTexture(Texture* texture)
{
	m_Textures.push_back(texture);
}

void StageLayer::Update(const GameTime& gameTime_)
{
}

void StageLayer::Draw(SpriteRenderer *spriteRenderer)
{
	auto* transform = m_pStage->GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();

	Matrix4 matrix;
	matrix.Identity();
	float offsetX = 0;
	
	for (auto* texture : m_Textures)
	{
		const auto posInTexture = RectangleI(0, 0, texture->TextureInfo()->width, texture->TextureInfo()->height);
		matrix.Translation(offsetX, 0, transform->GetPosition().z);

		spriteRenderer->AddSprite(texture, posInTexture, Vector2I::Zero(), matrix, CColor::White);

		offsetX += posInTexture.w;
	}
}
