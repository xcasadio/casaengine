#pragma once

#include "CA_Export.h"
#include "GameTime.h"
#include "DrawableGameComponent.h"
#include "Line3DRendererComponent.h"
#include "Maths/Matrix4.h"
#include "Graphics/Mesh/Mesh.h"

#include "Graphics/Effects/Program.h"


namespace CasaEngine
{
#if EDITOR
	class Game;

	enum class GridOrientation
	{
		XY,
		XZ,
		YZ
	};

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

		Line3DRendererComponent* m_Line3DRenderer;
		GridOrientation m_Orientation;
	};
#endif
}
