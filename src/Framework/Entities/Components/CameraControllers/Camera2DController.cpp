#include "Camera2DController.h"
#include "Maths/Matrix4.h"
#include "Game/Game.h"
#include "StringUtils.h"
#include "CameraController.h"


namespace CasaEngine
{
	Camera2DController::Camera2DController(CameraComponent* pCamera)
		: ICameraController(pCamera),
		//m_bRecomputeViewMatrix(false),
		m_vPosition(Vector3F::Zero()),
		m_fRotation(0.0f)
	{
		m_ViewMatrix.Identity();
	}

	Camera2DController::~Camera2DController()
	{
	}

	void Camera2DController::Update(const GameTime& /*gameTime_*/)
	{
	}

	void Camera2DController::Initialize()
	{
	}

	void Camera2DController::ViewMatrix(Matrix4& viewMatrix_)
	{
	}

	void Camera2DController::Write(std::ostream& os)
	{

	}

	void Camera2DController::Read(std::ifstream& is)
	{

	}
	void Camera2DController::Write(tinyxml2::XMLElement& xmlElt)
	{

	}
	void Camera2DController::Read(const tinyxml2::XMLElement& xmlElt)
	{

	}
}
