#ifndef SCRIPTCOMPONENT_H_
#define SCRIPTCOMPONENT_H_

#include "CA_Export.h"
#include "Entities\Component.h"
#include "Entities\BaseEntity.h"
#include "Script\IScriptObject.h"
#include "CompilationMacro.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	class CA_EXPORT ScriptComponent :
		public Component
	{
	public:
		ScriptComponent(BaseEntity* pEntity_);
		virtual ~ScriptComponent();

		void Initialize();
		void Update( const GameTime& gameTime_ );

		ScriptObjectClassID GetObjectClassID() const;
		void SetObjectClassID(ScriptObjectClassID val);

#ifdef USE_LUA_SCRIPT

		void SetScriptFile(const char *pFileName_);
		const char *GetScriptFile() const;
		void SetScriptFromBuffer(const char *pBuffer_, size_t length_);

#endif // USE_LUA_SCRIPT

		void Read( const tinyxml2::XMLElement& xmlElt ) OVERRIDE;
		void Read( std::ifstream& is ) OVERRIDE;
		void Write( tinyxml2::XMLElement& xmlElt ) OVERRIDE;
		void Write( std::ostream& os ) OVERRIDE;

	private:
		IScriptObject *m_pScriptObject;
		ScriptObjectClassID m_ClassID; //  the object classID used by this script
#ifdef USE_LUA_SCRIPT
		const char *m_pFileName;
#endif // USE_LUA_SCRIPT
	};
} // namespace CasaEngine

#endif // SCRIPTCOMPONENT_H_
