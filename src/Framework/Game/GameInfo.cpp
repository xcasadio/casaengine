#include "Base.h"
#include "GameInfo.h"
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
		CA_ASSERT(m_pCamera != nullptr, "GameInfo::GetActiveCamera() : camera is nullptr");
		return m_pCamera;
	}

	void GameInfo::SetActiveCamera(CameraComponent* val)
	{
		CA_ASSERT(val != nullptr, "GameInfo::SetActiveCamera() : camera is nullptr");

		m_pCamera = val;
		const Viewport& viewport = m_pCamera->GetViewport();

		//todo in graphics or in renderer
		bgfx::setViewRect(0,
			viewport.X() * static_cast<float>(Game::Instance().GetWindowSize().x),
			viewport.Y() * static_cast<float>(Game::Instance().GetWindowSize().y),
			viewport.Width() * static_cast<float>(Game::Instance().GetWindowSize().x),
			viewport.Height() * static_cast<float>(Game::Instance().GetWindowSize().y));
	}
}
