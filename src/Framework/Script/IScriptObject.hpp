#pragma once

#include "CA_Export.hpp"
#include  "Entities/BaseEntity.hpp"

namespace CasaEngine
{
	class CA_EXPORT IScriptObject
	{
	public:
		virtual ~IScriptObject() = default;

		BaseEntity* GetEntity() const;

		virtual void OnInitialize() = 0;
		virtual void OnUpdate(const GameTime& gameTime_) = 0;
		virtual bool HandleMessage(const Telegram& msg) = 0;
		virtual void OnDestroy() = 0;

	protected:
		IScriptObject(BaseEntity* entity_);

	private:
		BaseEntity* _entity;
	};

}
