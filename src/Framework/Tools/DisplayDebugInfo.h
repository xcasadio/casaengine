#ifndef _DISPLAYDEBUGINFO_H_
#define _DISPLAYDEBUGINFO_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "Graphics\Effects\Program.h"
#include "Graphics\Vertices\VertexType.h"


namespace CasaEngine
{
	class CA_EXPORT DisplayDebugInfo
	{
	public:
		DisplayDebugInfo();
		~DisplayDebugInfo();

		void Initialize();
		void Release();
		void Update(const GameTime& gameTime_);
		void Draw();

	private:
		Program *m_pProgram;
		bgfx::VertexBufferHandle m_VertexBuffer;
		VertexPositionColor m_Vertices[6];
	};
}

#endif
