#pragma once

#include "Sprite/SpriteRenderer.h"

class Stage;

class StageLayer
{
public:
	StageLayer(Stage *stage);
	~StageLayer();

	void AddTexture(CasaEngine::Texture *texture);
	void Update(const CasaEngine::GameTime& gameTime_);
	void Draw(CasaEngine::SpriteRenderer* spriteRenderer);

private:
	Stage* m_pStage;
	std::vector<CasaEngine::Texture*> m_Textures;
};
