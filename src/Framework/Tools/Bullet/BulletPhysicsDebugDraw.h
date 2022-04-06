#ifndef BULLETPHYSICSDEBUGDRAW_H_
#define BULLETPHYSICSDEBUGDRAW_H_

#include "CA_Export.h"
#include "LinearMath\btIDebugDraw.h"
#include "Game\Line3DRendererComponent.h"

namespace CasaEngine
{
	class CA_EXPORT BulletPhysicsDebugDraw :
		public btIDebugDraw
	{
	public:
		BulletPhysicsDebugDraw();
		~BulletPhysicsDebugDraw();

		void Initialize();
		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
		void reportErrorWarning(const char* warningString) override;
		void draw3dText(const btVector3& location, const char* textString) override;
		void setDebugMode(int debugMode) override;
		int getDebugMode() const override;

	private:
		Line3DRendererComponent* m_pLineRenderer;
		int m_debugMode;
	};
}

#endif
