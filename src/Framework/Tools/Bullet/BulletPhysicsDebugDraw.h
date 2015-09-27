#ifndef BULLETPHYSICSDEBUGDRAW_H_
#define BULLETPHYSICSDEBUGDRAW_H_

#include "CA_Export.h"
#include "LinearMath\btIDebugDraw.h"
#include "Game\Line3DRendererComponent.h"
#include "Memory\MemoryAllocation.h"
#include "CompilationMacro.h"

namespace CasaEngine
{

class CA_EXPORT BulletPhysicsDebugDraw : 
	public btIDebugDraw,
	public AllocatedObject<BulletPhysicsDebugDraw>
{
private:
	int m_debugMode;

public:
	BulletPhysicsDebugDraw();
	~BulletPhysicsDebugDraw();

	void Initialize();

	void drawLine( const btVector3& from,const btVector3& to,const btVector3& color ) OVERRIDE;

	void drawContactPoint( const btVector3& PointOnB,const btVector3& normalOnB,btScalar distance,int lifeTime,const btVector3& color ) OVERRIDE;

	void reportErrorWarning( const char* warningString ) OVERRIDE;

	void draw3dText( const btVector3& location,const char* textString ) OVERRIDE;

	void setDebugMode( int debugMode ) OVERRIDE;

	int getDebugMode() const override;

private:
	Line3DRendererComponent *m_pLineRenderer;
};

} // namespace CasaEngine

#endif // BULLETPHYSICSDEBUGDRAW_H_
