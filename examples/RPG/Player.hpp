#pragma once

#include  "Character.hpp"

using namespace CasaEngine;

class Player :
	public Character
{
public:
	Player(BaseEntity* pEntity);
	~Player() override = default;

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

	bool FuryModeDisabling() const;
	void FuryModeDisabling(bool val);

	bool FuryModeEnabling() const;
	void FuryModeEnabling(bool val);

	bool InFuryMode() const;
	void InFuryMode(bool val);

	int MaxFuryPoint() const;
	void MaxFuryPoint(int val);

	void AttachWeapon();
	void UnAttachWeapon();

	void SetWeapon(BaseEntity* weapon);

private:
	int m_FuryPoint;
	float m_FuryPointDecrease;
	bool m_InBleedingMode;
	int m_FuryForce;
	int m_FuryDef;
	float m_FurySpeed;
	bool m_FuryModeEnabling;
	bool m_FuryModeDisabling;
	bool m_InFuryMode;
	int m_MaxFuryPoint;

	BaseEntity* m_Weapon;
};