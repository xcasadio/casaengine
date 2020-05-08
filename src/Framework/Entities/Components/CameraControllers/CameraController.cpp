#include "Base.h"

#include <string>

#include "CameraController.h"
#include "Maths/Matrix4.h"
#include "Game/Game.h"
#include "StringUtils.h"


namespace CasaEngine
{

/**
 * 
 */
ICameraController::ICameraController(CameraComponent* pCamera)
	: m_pCamera(pCamera)
{
	
}

/**
 * 
 */
ICameraController::~ICameraController()
{
}

/**
 * 
 */
void ICameraController::Update(const GameTime& /*gameTime_*/)
{
}

/**
 * 
 */
/*void ICameraController::HandleEvent(const Event* pEvent_)
{

}*/

CameraComponent* ICameraController::Camera() const 
{ 
	return m_pCamera; 
}

/**
 * 
 */
void ICameraController::Write(std::ostream& os)
{
	CA_UNUSED_1(os)
}

/**
 * 
 */
void ICameraController::Read (std::ifstream& is)
{
	CA_UNUSED_1(is)
}

/**
 * 
 */
void ICameraController::Read (const tinyxml2::XMLElement& xmlElt)
{
	CA_UNUSED_1(xmlElt)
}

/**
 * 
 */
void ICameraController::Write(tinyxml2::XMLElement& xmlElt)
{
	CA_UNUSED_1(xmlElt)
}

}
