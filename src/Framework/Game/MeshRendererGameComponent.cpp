//==========================================================
// En-têtes
//==========================================================
#include "Base.h"

#include "Game/MeshRendererGameComponent.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Graphics/Mesh/Mesh.h"
#include "Maths/Matrix4.h"
#include "Graphics/Renderer/Renderer.h"
#include "Graphics/Renderer/Enums.h"
#include "GameInfo.h"
#include "Entities/Components/CameraComponent.h"


#include "Memory/MemoryAllocation.h"
#include "bx/fpumath.h"


namespace CasaEngine
{
	/**
	 * 
	 */
	MeshRendererGameComponent::MeshRendererGameComponent(Game* pGame_) : 
		DrawableGameComponent(pGame_)
	{
		DrawOrder(0);
		UpdateOrder(0);

		m_Datas.reserve(50);
	}

	/**
	 * 
	 */
	MeshRendererGameComponent::~MeshRendererGameComponent()
	{
	}

	/**
	 * 
	 */
	void MeshRendererGameComponent::OnLoadContent() 
	{ 
	}

	/**
	 * 
	 */
	void MeshRendererGameComponent::Update(const GameTime& /*gameTime_*/)
	{ 
		std::vector<ModelRendererData *>::iterator it;
		
		for (it = m_Datas.begin();
			it != m_Datas.end();
			it++)
		{
			::delete (*it);
		}
		
		m_Datas.clear();
	}

	/**
	 * 
	 */
	void MeshRendererGameComponent::Draw()
	{
		CameraComponent *pCamera = GameInfo::Instance().GetActiveCamera();
		bgfx::setViewTransform(0, pCamera->GetViewMatrix(), pCamera->GetProjectionMatrix());

		std::vector<ModelRendererData *>::iterator it;

		for (it = m_Datas.begin();
			it != m_Datas.end();
			it++)
		{
			(*it)->pModel->Render((*it)->handle, (*it)->pMatWorld);
		}
	}

	/**
	 * 
	 */
	void MeshRendererGameComponent::AddModel(Mesh *pModel_, Matrix4 &pMatWorld_, Program *pProgram_)
	{
		CA_ASSERT(pModel_ != nullptr, "MeshRendererGameComponent::AddModel() : Mesh is nullptr");
		CA_ASSERT(pProgram_ != nullptr, "MeshRendererGameComponent::AddModel() : Program is nullptr");

		ModelRendererData *pData = ::new ModelRendererData();
		pData->pModel = pModel_;
		pData->pMatWorld = pMatWorld_;
		pData->handle = pProgram_->Handle();
		m_Datas.push_back(pData);
	}

} // namespace CasaEngine
