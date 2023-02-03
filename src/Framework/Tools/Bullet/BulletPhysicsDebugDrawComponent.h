#pragma once

#include "CA_Export.h"
#include "LinearMath/btIDebugDraw.h"
#include "Game/Line3DRendererComponent.h"

namespace CasaEngine
{
	class CA_EXPORT BulletPhysicsDebugDrawComponent :
		public btIDebugDraw, public DrawableGameComponent
	{
	public:
		BulletPhysicsDebugDrawComponent(Game* game);

		void Initialize() override;
		void OnLoadContent() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		void clearLines() override;
		void flushLines() override;
		void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
		void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
		void reportErrorWarning(const char* warningString) override;
		void draw3dText(const btVector3& location, const char* textString) override;
		void setDebugMode(int debugMode) override;
		int getDebugMode() const override;

	private:
		struct LineData
		{
			Vector3 start, end;
			Color color;
		};

		Line3DRendererComponent* m_pLineRenderer;
		int m_debugMode;
		std::vector<LineData> lines;

		void AddLine(const Vector3& start, const Vector3& end, const Color& color);
	};
}
