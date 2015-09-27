#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include <QThread>
#include "SFML/Window/Window.hpp"
#include "Game\Editor\GameEditor.h"
#include "GameView.h"

class GameThread : public QThread
{
	Q_OBJECT

public:
	GameThread(QObject *parent, GameView *pGameView_);
	~GameThread();

	void CreateGame();
	void GameRun();
	void GameExit();

	virtual void run();

	CasaEngine::GameEditor *GameEditor() const;

private:
	sf::WindowHandle m_HWnd;
	CasaEngine::GameEditor *m_pGameEditor;
	GameView *m_pGameView;
	
};

/*

class Worker : public QObject
{
Q_OBJECT
QThread workerThread;

public slots:
void doWork(const QString &parameter) {
// ...
emit resultReady(result);
}

signals:
void resultReady(const QString &result);
};

class Controller : public QObject
{
Q_OBJECT
QThread workerThread;
public:
Controller() {
Worker *worker = new Worker;
worker->moveToThread(&workerThread);
connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
connect(this, SIGNAL(operate(QString)), worker, SLOT(doWork(QString)));
connect(worker, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
workerThread.start();
}
~Controller() {
workerThread.quit();
workerThread.wait();
}
public slots:
void handleResults(const QString &);
signals:
void operate(const QString &);
};

*/

#endif // GAMETHREAD_H
