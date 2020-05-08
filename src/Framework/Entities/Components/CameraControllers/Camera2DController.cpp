#include "Base.h"

#include <string>

#include "Camera2DController.h"
#include "Maths/Matrix4.h"
#include "Game/Game.h"
#include "StringUtils.h"
#include "CameraController.h"


namespace CasaEngine
{

/**
 * 
 */
Camera2DController::Camera2DController(CameraComponent* pCamera)
	: ICameraController(pCamera),
	//m_bRecomputeViewMatrix(false),
	m_vPosition(Vector3F::Zero()),
	m_fRotation(0.0f)
{
	m_ViewMatrix.Identity();
}

/**
 * 
 */
Camera2DController::~Camera2DController()
{
}

/**
 * 
 */
void Camera2DController::Update(const GameTime& /*gameTime_*/)
{
	/*Matrix4 mat = m_pTransform->GetWorldMatrix();
	Vector3F pos3 = mat.GetTranslation();
	Vector2F pos(pos3.x, pos3.y);*/
}

/**
 * 
 */
void Camera2DController::Initialize()
{
	//m_pInputManager = Game::Instance()->GetGameComponent<InputManagerComponent>();
	//CA_ASSERT(m_pInputManager != nullptr && "ArcBallCameraController::Initialize() InputManagerComponent is nullptr");
}

/**
 *
 */
void Camera2DController::ViewMatrix(Matrix4& viewMatrix_)
{
}

/**
 * 
 */
/*void ICameraController::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void Camera2DController::Write(std::ostream& os)
{
	CA_UNUSED_1(os)
}

/**
 * 
 */
void Camera2DController::Read (std::ifstream& is)
{
	CA_UNUSED_1(is)
}

/**
 * 
 */
void Camera2DController::Write(tinyxml2::XMLElement& xmlElt) 
{
	CA_UNUSED_1(xmlElt)
}

/**
 * 
 */
void Camera2DController::Read (const tinyxml2::XMLElement& xmlElt)
{
	CA_UNUSED_1(xmlElt)
}

}
