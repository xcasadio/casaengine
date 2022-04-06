#include "Base.h"

#include "Game/MeshRendererGameComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Graphics/Mesh/Mesh.h"
#include "Maths/Matrix4.h"
#include "GameInfo.h"
#include "Entities/Components/CameraComponent.h"


#include "bx/math.h"


namespace CasaEngine
{
	MeshRendererGameComponent::MeshRendererGameComponent(Game* pGame_) : 
		DrawableGameComponent(pGame_)
	{
		DrawOrder(0);
		UpdateOrder(0);

		m_Datas.reserve(50);
	}

	MeshRendererGameComponent::~MeshRendererGameComponent()
	{
	}

	void MeshRendererGameComponent::OnLoadContent() 
	{ 
	}

	void MeshRendererGameComponent::Update(const GameTime& /*gameTime_*/)
	{
		for (auto it = m_Datas.begin();
		     it != m_Datas.end();
		     ++it)
		{
			delete (*it); //TODO : no delete in real time
		}
		
		m_Datas.clear();
	}

	void MeshRendererGameComponent::Draw()
	{
		CameraComponent *pCamera = Game::Instance().GetGameInfo().GetActiveCamera();
		//if (pCamera != nullptr)
		{
			bgfx::setViewTransform(0, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());
			for (auto *data : m_Datas)
			{
				data->pModel->Render(data->handle, data->pMatWorld);
			}
		}
		/*else
		{
			CA_WARN("No active camera defined\n");
		}*/
	}

	void MeshRendererGameComponent::AddModel(Mesh *pModel_, Matrix4 &pMatWorld_, Program *pProgram_)
	{
		CA_ASSERT(pModel_ != nullptr, "MeshRendererGameComponent::AddModel() : Mesh is nullptr");
		CA_ASSERT(pProgram_ != nullptr, "MeshRendererGameComponent::AddModel() : Program is nullptr");

		auto pData = new ModelRendererData();//TODO : no new in real time
		pData->pModel = pModel_;
		pData->pMatWorld = pMatWorld_;
		pData->handle = pProgram_->Handle();
		m_Datas.push_back(pData);
	}

}
