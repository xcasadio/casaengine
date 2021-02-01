#ifndef CHARACTER_H_
#define CHARACTER_H_

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
	virtual ~Character();

	virtual void Initialize();
	void Update(const CasaEngine::GameTime& gameTime_);
	void Draw();

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

#endif
