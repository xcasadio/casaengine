#pragma once

#include "CA_Export.hpp"
#include  "GameTime.hpp"
#include  "DrawableGameComponent.hpp"
#include  "Maths/Matrix4.hpp"
#include  "Graphics/Mesh/Mesh.hpp"

#include <vector>
#include  "Graphics/Effects/Program.hpp"


namespace CasaEngine
{
	class Game;

	class CA_EXPORT MeshRendererGameComponent :
		public DrawableGameComponent
	{
	private:
		class ModelRendererData
		{
		public:
			Mesh *pModel;
			Matrix4 pMatWorld;
			bgfx::ProgramHandle handle;
		};

	public:
		void OnLoadContent() override;
		void Update( const GameTime& gameTime_ ) override;
		void Draw() override;

		void AddModel(Mesh *pModel_, Matrix4 &pMatWorld_, Program *pProgram_);

		//EventHandler<int> DrawOrderChanged;

		MeshRendererGameComponent(Game* pGame_);
		~MeshRendererGameComponent() override;

	private:
		std::vector<ModelRendererData *> m_Datas;
	};

}
