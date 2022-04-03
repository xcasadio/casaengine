#include "Tools/DebugSystem.h"
#include "Game/Game.h"
#include "GameTime.h"
#include "Entities/Events/DebugToolEvents.h"
#include "EventHandler/GlobalEventSet.h"

namespace CasaEngine
{
	DebugSystem::DebugSystem(): m_fFPSTime(0.0f), m_iFPSCount(0), m_fFPSLastDelta(0.0f), m_iLastFPSCount(0)
	{
	}

	void DebugSystem::Update( const GameTime& gameTime_ )
	{
		m_fFPSTime += gameTime_.FrameTime();
		m_iFPSCount++;
		
		if (m_fFPSTime >= 1.0f)
		{
			//AverageDrawCalls = drawCallThisSecond / m_iFPSCount;
			//AverageTrianglesDrawn = trianglesDrawnThisSecond / m_iFPSCount;
			//Reset startSecondTick and repaintCountSecond

			m_fFPSTime -= 1.0f;
			float FPSDelta = static_cast<float>(m_iFPSCount) * m_fFPSTime;			
			//FPS - delta, to reduce the calculation to 1 second precisely
			m_iLastFPSCount = static_cast<int>(static_cast<float>(m_iFPSCount) - FPSDelta + m_fFPSLastDelta);

			m_iFPSCount = 0;
			m_fFPSLastDelta = FPSDelta;
			//drawCallThisSecond = 0;
			//trianglesDrawnThisSecond = 0;

			//CA_TRACE("FPS %d\n", m_iLastFPSCount);

			Game::Instance().GetGlobalEventSet().fireEvent(
				FPSChangeEvent::FPSChangeEventName,
				FPSChangeEvent(m_iLastFPSCount));
		}
	}

	int DebugSystem::GetFPS() const
	{
		return m_iLastFPSCount;
	}
}
