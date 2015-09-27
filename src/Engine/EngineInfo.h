
#ifndef ENGINEINFO_H_
#define ENGINEINFO_H_

#include "CA_Export.h"
#include "Singleton.h"
#include "Graphics/Viewport.h"

namespace CasaEngine
{
	/**
	 *	
	 */
	class CA_EXPORT EngineInfo :
		public CSingleton<EngineInfo>
	{
		MAKE_SINGLETON(EngineInfo)

	public:

		/**
		 * Get the default viewport (size of the screen).
		 */
		//Viewport* GetDefaultViewport();

		/**
		 * 
		 */
		//Viewport& GetViewport();

		/**
		* if pViewport_ == nullptr, viewport by default is used
		*/
		//void SetViewport(Viewport *pViewport_);

	private:

		EngineInfo();
		~EngineInfo();

	private:
		//Viewport *m_pCurrentViewport;
		//Viewport m_DefaultViewport;
	};

} // namespace CasaEngine

#endif // ENGINEINFO_H_
