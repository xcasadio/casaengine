#include "GameThread.h"
#include "Memory\MemoryAllocation.h"

GameThread::GameThread(QObject *parent, GameView *pGameView_)
	: QThread(parent),
	m_pGameEditor(nullptr),
	m_pGameView(pGameView_)
{
	m_HWnd = reinterpret_cast<CasaEngine::WindowHandle>(pGameView_->winId());
}

GameThread::~GameThread()
{
	if (m_pGameEditor != nullptr)
	{
		DELETE_AO m_pGameEditor;
	}
}


/**
 * 
 */
void GameThread::CreateGame()
{
	//m_pGameEditor = NEW_AO CasaEngine::GameEditor(m_HWnd);
	//m_pGameView->GameEditor(m_pGameEditor);
}

/**
 * 
 */
void GameThread::GameRun()
{
	start(QThread::NormalPriority);
}

/**
 * 
 */
void GameThread::run()
{
	m_pGameEditor = NEW_AO CasaEngine::GameEditor(m_HWnd);
	m_pGameView->GameEditor(m_pGameEditor);
	m_pGameEditor->Run();
}

/**
 * 
 */
void GameThread::GameExit()
{
	if (m_pGameEditor != nullptr)
	{
		m_pGameView->GameEditor(nullptr);
		m_pGameEditor->Exit();
	}
}

/**
 * 
 */
CasaEngine::GameEditor * GameThread::GameEditor() const
{
	return m_pGameEditor;
}
