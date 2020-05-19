#ifndef HERO_H_
#define HERO_H_

#include "Character.h"
#include <map>
#include "CharacterEnum.h"
#include "Animations\Animation2D.h"
#include "Entities\Components\AnimatedSpriteComponent.h"


using namespace CasaEngine;

/**
 * 
 */
class Hero :
	public Character
{
public:
	Hero(BaseEntity* pEntity);
	virtual ~Hero();
	
	void Initialize() override;

	//////////////////////////////////////////////////////////////////////////
	int FuryPoint() const;
	void FuryPoint(int val);

	float FuryPointDecrease() const;
	void FuryPointDecrease(float val);

	bool InBleedingMode() const;
	void InBleedingMode(bool val);

	int FuryForce() const;
	void FuryForce(int val);

	int FuryDef() const;
	void FuryDef(int val);

	float FurySpeed() const;
	void FurySpeed(float val);

	bool FuryModeDesabling() const;
	void FuryModeDesabling(bool val);

	bool FuryModeEnabling() const;
	void FuryModeEnabling(bool val);

	bool InFuryMode() const;
	void InFuryMode(bool val);

	int MaxFuryPoint() const;
	void MaxFuryPoint(int val);

private:
	int m_FuryPoint;
    float m_FuryPointDecrease;
	bool m_InBleedingMode;
	int m_FuryForce;
	int m_FuryDef;
	float m_FurySpeed;
	bool m_FuryModeEnabling;
	bool m_FuryModeDesabling;
	bool m_InFuryMode;
	int m_MaxFuryPoint;
};

#endif
