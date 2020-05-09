#include "BulletPhysicsDebugDraw.h"
#include "Log\LogManager.h"
#include "CA_Assert.h"
#include "Game\Game.h"
#include "Macro.h"
#include "Graphics\Color.h"

namespace CasaEngine
{

BulletPhysicsDebugDraw::BulletPhysicsDebugDraw()
{
	m_pLineRenderer = nullptr;
}


BulletPhysicsDebugDraw::~BulletPhysicsDebugDraw()
{
}

void BulletPhysicsDebugDraw::Initialize()
{
	m_pLineRenderer = Game::Instance().GetGameComponent<Line3DRendererComponent>();
	CA_ASSERT(m_pLineRenderer != nullptr, "BulletPhysicsDebugDraw::Initialize() : Line3DRendererComponent is nullptr");
}

void BulletPhysicsDebugDraw::drawLine( const btVector3& from,const btVector3& to,const btVector3& color )
{
	CA_ASSERT(m_pLineRenderer != nullptr, "BulletPhysicsDebugDraw : please call Initialize() before call drawXXX() function");
	Vector3F start(from.x(), from.y(), from.z());
	Vector3F end(to.x(), to.y(), to.z());
	CColor ccolor;
	ccolor.SetFloats(color.x(), color.y(),color.z());
	m_pLineRenderer->AddLine(start, ccolor, end, ccolor);
}

void BulletPhysicsDebugDraw::drawContactPoint( const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color )
{
	CA_ASSERT(m_pLineRenderer != nullptr, "BulletPhysicsDebugDraw : please call Initialize() before call drawXXX() function");
		//		glRasterPos3f(from.x(),  from.y(),  from.z());
		//		char buf[12];
		//		sprintf(buf," %d",lifeTime);
		//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
	btVector3 to = PointOnB + normalOnB*1;//distance;
	const btVector3 &from = PointOnB;

	Vector3F start(from.x(), from.y(), from.z());
	Vector3F end(to.x(), to.y(), to.z());
	CColor ccolor;
	ccolor.SetFloats(color.x(), color.y(),color.z());
	m_pLineRenderer->AddLine(start, ccolor, end, ccolor);
}

/**
 * 
 */
void BulletPhysicsDebugDraw::reportErrorWarning( const char* warningString )
{
	CA_WARN("%s\n",warningString);
}

/**
 * 
 */
void BulletPhysicsDebugDraw::draw3dText( const btVector3& location,const char* textString )
{
	CA_UNUSED(location, textString)
	/*
	glRasterPos3f(location.x(),  location.y(),  location.z());
	//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
	*/
}

/**
 * 
 */
void BulletPhysicsDebugDraw::setDebugMode( int debugMode )
{
	m_debugMode = debugMode;
}

/**
 * 
 */
int BulletPhysicsDebugDraw::getDebugMode() const
{
	return m_debugMode;
}

}
