#include "CameraController.h"
#include "Game/Game.h"
#include "StringUtils.h"

namespace CasaEngine
{
	ICameraController::ICameraController(CameraComponent* pCamera)
		: m_pCamera(pCamera)
	{

	}

	ICameraController::~ICameraController()
	{
	}

	void ICameraController::Update(const GameTime& /*gameTime_*/)
	{
	}

	CameraComponent* ICameraController::Camera() const
	{
		return m_pCamera;
	}

	void ICameraController::Write(std::ostream& os)
	{

	}

	void ICameraController::Read(std::ifstream& is)
	{

	}

	void ICameraController::Read(const tinyxml2::XMLElement& xmlElt)
	{

	}

	void ICameraController::Write(tinyxml2::XMLElement& xmlElt)
	{

	}

}
