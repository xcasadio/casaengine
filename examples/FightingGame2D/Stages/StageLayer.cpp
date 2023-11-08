#include  "Stage.hpp"

#include  "Game/Game.hpp"
#include  "Sprite/SpriteRenderer.hpp"

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
	Matrix4 matrix;
	matrix.Identity();
	float offsetX = 0;
	auto positionZ = m_pStage->GetEntity()->GetCoordinates().GetPosition().z;

	for (auto* texture : m_Textures)
	{
		const auto posInTexture = CasaEngine::Rectangle(0, 0, texture->TextureInfo()->width, texture->TextureInfo()->height);
		matrix.Translation(offsetX, 0, positionZ);

		spriteRenderer->AddSprite(texture, posInTexture, Vector2I::Zero(), matrix, Color::White);

		offsetX += posInTexture.w;
	}
}
