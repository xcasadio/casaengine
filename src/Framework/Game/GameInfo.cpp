#include "Base.h"
#include "GameInfo.h"
#include "Project/ProjectManager.h"
#include "Graphics/Renderer/Renderer.h"
#include "Game.h"

namespace CasaEngine
{
	GameInfo::GameInfo() :
		m_pWorld(nullptr),
		m_pCamera(nullptr)
	{
	}

	GameInfo::~GameInfo()
	{
	}

	ProjectManager& GameInfo::GetProjectManager()
	{
		return m_ProjectManager;
	}

	World* GameInfo::GetWorld() const
	{
		return m_pWorld;
	}

	void GameInfo::SetWorld(World* val)
	{
		m_pWorld = val;
	}

	CameraComponent* GameInfo::GetActiveCamera() const
	{
		//CA_ASSERT("GameInfo::GetActiveCamera() : camera is nullptr", m_pCamera != nullptr);
		return m_pCamera;
	}

	void GameInfo::SetActiveCamera(CameraComponent* val)
	{
		CA_ASSERT(val != nullptr, "GameInfo::SetActiveCamera() : camera is nullptr");

		m_pCamera = val;
		Viewport& viewport = m_pCamera->GetViewport();

		//todo in graphics or in renderer
		bgfx::setViewRect(0,
			viewport.X() * static_cast<float>(Game::Instance().GetWindowSize().x),
			viewport.Y() * static_cast<float>(Game::Instance().GetWindowSize().y),
			viewport.Width() * static_cast<float>(Game::Instance().GetWindowSize().x),
			viewport.Height() * static_cast<float>(Game::Instance().GetWindowSize().y));
	}
}
