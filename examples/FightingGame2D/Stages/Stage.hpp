#pragma once

#include  "StageInfo.hpp"
#include  "StageLayer.hpp"
#include  "Sprite/SpriteRenderer.hpp"

class Stage:
	public CasaEngine::Component
{
public:
	Stage(CasaEngine::BaseEntity* entity);
	~Stage() override;

	void Initialize() override;
	void Update(const CasaEngine::GameTime& gameTime_) override;
	void Draw() override;
	void SetStageInfo(StageInfo* stage_info);

private:
	StageInfo* m_pInfo;
	CasaEngine::SpriteRenderer *m_pSpriteRenderer;
	std::vector<StageLayer*> m_Layers;
};
