#ifndef STAGE_H_
#define STAGE_H_

#include "StageInfo.h"
#include "StageLayer.h"
#include "Sprite/SpriteRenderer.h"

class Stage:
	public CasaEngine::Component
{
public:
	Stage(CasaEngine::BaseEntity* entity);
	~Stage();

	void Initialize() override;
	void Update(const CasaEngine::GameTime& gameTime_) override;
	void Draw() override;
	void SetStageInfo(StageInfo* stage_info);

private:
	StageInfo* m_pInfo;
	CasaEngine::SpriteRenderer *m_pSpriteRenderer;
	std::vector<StageLayer*> m_Layers;
};



#endif
