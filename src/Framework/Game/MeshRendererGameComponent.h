#ifndef _MeshRendererGameComponent_H_
#define _MeshRendererGameComponent_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "DrawableGameComponent.h"
#include "Maths/Matrix4.h"
#include "Graphics/Mesh/Mesh.h"

#include <vector>
#include "Graphics/Effects/Program.h"


namespace CasaEngine
{
	class Game;

	class CA_EXPORT MeshRendererGameComponent :
		public DrawableGameComponent
	{
	private:
		class ModelRendererData : 
			public AllocatedObject<ModelRendererData>
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

#endif
