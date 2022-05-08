#pragma once

#include "CA_Export.h"
#include "Entities\Component.h"
#include "Script\IScriptObject.h"

namespace CasaEngine
{
	class CA_EXPORT ScriptComponent :
		public Component
	{
	public:
		ScriptComponent(BaseEntity* pEntity_);
		~ScriptComponent() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		bool HandleMessage(const Telegram& msg) override;

		void SetScriptObject(IScriptObject*);
		IScriptObject* GetScriptObject();

	private:
		IScriptObject* m_pScriptObject;
		ScriptObjectClassID m_ClassID; //  the object classID used by this script
	};
}
