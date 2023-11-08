#pragma once

#include "CA_Export.hpp"
#include  "GameTime.hpp"
#include  "DrawableGameComponent.hpp"
#include  "Line3DRendererComponent.hpp"
#include  "Maths/Matrix4.hpp"
#include  "Graphics/Mesh/Mesh.hpp"

#include  "Graphics/Effects/Program.hpp"


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
