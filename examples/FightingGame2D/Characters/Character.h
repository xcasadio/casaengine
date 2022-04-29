#pragma once

#include <map>

#include "Animations\Animation2D.h"
#include "Entities\Component.h"
#include "Entities\Components\AnimatedSpriteComponent.h"
#include "GameDatas/CharacterBase.h"


class Character :
	public CasaEngine::CharacterBase
{
public:
	static const int Deadzone = 20;

public:
	~Character() override;

	void Initialize() override;
	void Update(const CasaEngine::GameTime& gameTime_) override;
	void Draw() override;

	bool SetCurrentAnimationByName(const char* name);

	bool OnFrameChangedEvent(const CasaEngine::EventArgs& e_);
	bool OnAnimationFinished(const CasaEngine::EventArgs& e_);

protected:
	Character(CasaEngine::BaseEntity* pEntity);

private:
	int m_HPMax;
	int m_HP;
	//
	int m_MPMax;
	int m_MP;

	std::map<int, CasaEngine::Animation2D*> m_Animations;
};
