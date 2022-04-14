#pragma once

#include "CA_Export.h"
#include "GameTime.h"
#include "DrawableGameComponent.h"
#include "Maths/Matrix4.h"
#include "Graphics/Mesh/Mesh.h"

#include "Graphics/Effects/Program.h"


namespace CasaEngine
{
	class Game;

	class CA_EXPORT DisplayDebugInfoGameComponent :
		public DrawableGameComponent
	{
	public:
		DisplayDebugInfoGameComponent(Game* pGame_);
		~DisplayDebugInfoGameComponent() override;

		void OnLoadContent() override;
		void Update( const GameTime& gameTime_ ) override;
		void Draw() override;
		
	private:
		Program* m_pProgram;
		bgfx::VertexBufferHandle m_VertexBuffer;
		VertexPositionColor m_Vertices[6];
	};
}
