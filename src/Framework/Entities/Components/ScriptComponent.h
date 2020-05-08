#ifndef SCRIPTCOMPONENT_H_
#define SCRIPTCOMPONENT_H_

#include "CA_Export.h"
#include "Entities\Component.h"
#include "Entities\BaseEntity.h"
#include "Script\IScriptObject.h"

namespace CasaEngine
{
	class CA_EXPORT ScriptComponent :
		public Component
	{
	public:
		ScriptComponent(BaseEntity* pEntity_);
		virtual ~ScriptComponent();

		void Initialize();
		void Update( const GameTime& gameTime_ );

		void Read( const tinyxml2::XMLElement& xmlElt ) override;
		void Read( std::ifstream& is ) override;
		void Write( tinyxml2::XMLElement& xmlElt ) override;
		void Write( std::ostream& os ) override;

	private:
		IScriptObject *m_pScriptObject;
		ScriptObjectClassID m_ClassID; //  the object classID used by this script
	};
}

#endif // SCRIPTCOMPONENT_H_
