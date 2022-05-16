#pragma once

#include "Physics/CollisionParameters.h"
#include "Script\IScriptObject.h"

using namespace CasaEngine;

class ScriptGrass :
	public IScriptObject
{
public:
	ScriptGrass(BaseEntity* entity);
	~ScriptGrass() override;

	void OnInitialize() override;
	void OnUpdate(const GameTime& gameTime_) override;
	bool HandleMessage(const Telegram& msg) override;
	void OnDestroy() override;

private:
	void CollideWith(CollisionParameters* collisionParameters, BaseEntity* otherEntity, CollisionParameters* otherCollisionParameters);
};
