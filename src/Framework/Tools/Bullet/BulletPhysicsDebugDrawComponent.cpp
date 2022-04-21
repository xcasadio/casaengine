#include "BulletPhysicsDebugDrawComponent.h"

#include "Log\LogManager.h"
#include "CA_Assert.h"
#include "Game\Game.h"

#include "Graphics\Color.h"

namespace CasaEngine
{
	BulletPhysicsDebugDrawComponent::BulletPhysicsDebugDrawComponent(Game* game) :
		DrawableGameComponent(game),
		m_pLineRenderer(nullptr),
		m_debugMode(DBG_DrawWireframe)
	{
	}

	void BulletPhysicsDebugDrawComponent::Initialize()
	{
		m_pLineRenderer = Game::Instance().GetGameComponent<Line3DRendererComponent>();
		CA_ASSERT(m_pLineRenderer != nullptr, "BulletPhysicsDebugDrawComponent::Initialize() : Line3DRendererComponent is nullptr");
	}

	void BulletPhysicsDebugDrawComponent::OnLoadContent()
	{
		DrawableGameComponent::OnLoadContent();
	}

	void BulletPhysicsDebugDrawComponent::Update(const GameTime& gameTime_)
	{
		//clearLines();
	}

	void BulletPhysicsDebugDrawComponent::Draw()
	{
		for (auto & line : lines)
		{
			m_pLineRenderer->AddLine(line.start, line.end, line.color);
		}
	}

	void BulletPhysicsDebugDrawComponent::clearLines()
	{
		lines.clear();
		btIDebugDraw::clearLines();
	}

	void BulletPhysicsDebugDrawComponent::flushLines()
	{
		//Draw();
		btIDebugDraw::flushLines();
	}

	void BulletPhysicsDebugDrawComponent::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		CA_ASSERT(m_pLineRenderer != nullptr, "BulletPhysicsDebugDrawComponent : please call Initialize() before call drawXXX() function");
		Vector3 start(from.x(), from.y(), from.z());
		Vector3 end(to.x(), to.y(), to.z());
		Color ccolor;
		ccolor.SetFloats(color.x(), color.y(), color.z());
		AddLine(start, end, ccolor);
	}

	void BulletPhysicsDebugDrawComponent::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
	{
		CA_ASSERT(m_pLineRenderer != nullptr, "BulletPhysicsDebugDrawComponent : please call Initialize() before call drawXXX() function");
		//		glRasterPos3f(from.x(),  from.y(),  from.z());
		//		char buf[12];
		//		sprintf(buf," %d",lifeTime);
		//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),buf);
		btVector3 to = PointOnB + normalOnB * 1;//distance;
		const btVector3& from = PointOnB;

		Vector3 start(from.x(), from.y(), from.z());
		Vector3 end(to.x(), to.y(), to.z());
		Color ccolor;
		ccolor.SetFloats(color.x(), color.y(), color.z());
		AddLine(start, end, ccolor);
	}

	void BulletPhysicsDebugDrawComponent::reportErrorWarning(const char* warningString)
	{
		CA_WARN("bullet : %s\n", warningString);
	}

	void BulletPhysicsDebugDrawComponent::draw3dText(const btVector3& location, const char* textString)
	{
		/*
		glRasterPos3f(location.x(),  location.y(),  location.z());
		//BMF_DrawString(BMF_GetFont(BMF_kHelvetica10),textString);
		*/
	}

	void BulletPhysicsDebugDrawComponent::setDebugMode(int debugMode)
	{
		m_debugMode = debugMode; // see btIDebugDraw::DebugDrawModes
	}

	int BulletPhysicsDebugDrawComponent::getDebugMode() const
	{
		return m_debugMode;
	}

	void BulletPhysicsDebugDrawComponent::AddLine(const Vector3& start, const Vector3& end, const Color& color)
	{
		lines.push_back({ start, end, color });
	}
}
