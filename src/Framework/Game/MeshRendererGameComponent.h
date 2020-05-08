
#ifndef _MeshRendererGameComponent_H_
#define _MeshRendererGameComponent_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "DrawableGameComponent.h"
#include "Maths/Matrix4.h"
#include "Graphics/Mesh/Mesh.h"
#include "Memory/ObjectPool.h"

#include <vector>
#include "Graphics/Effects/Program.h"


namespace CasaEngine
{
	class Game;

	/////////////////////////////////////////////////////////////
	/// CMeshRendererGameComponent
	/////////////////////////////////////////////////////////////
	class CA_EXPORT MeshRendererGameComponent :
		public DrawableGameComponent
	{
	private:
		class ModelRendererData : 
			public ObjectPool<ModelRendererData>
		{
		public:
			Mesh *pModel;
			Matrix4 pMatWorld;
			bgfx::ProgramHandle handle;
		};

	public:
		void OnLoadContent();
		void Update( const GameTime& gameTime_ );
		void Draw();

		void AddModel(Mesh *pModel_, Matrix4 &pMatWorld_, Program *pProgram_);

		//EventHandler<int> DrawOrderChanged;

		MeshRendererGameComponent(Game* pGame_);
		virtual ~MeshRendererGameComponent();

	private:
		std::vector<ModelRendererData *> m_Datas;
	};

}

#endif // _MeshRendererGameComponent_H_
