#pragma once

#include "CA_Export.hpp"
#include  "Entities/Component.hpp"
#include  "Script/IScriptObject.hpp"

namespace CasaEngine
{
	class CA_EXPORT ScriptComponent :
		public Component
	{
	public:
		ScriptComponent(BaseEntity* entity);
		~ScriptComponent() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		bool HandleMessage(const Telegram& msg) override;

		void SetScriptObject(IScriptObject*);
		IScriptObject* GetScriptObject();

	private:
		IScriptObject* m_pScriptObject;
	};
}
