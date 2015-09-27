#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include "Game\Editor\GameEditor.h"

/**
 * 
 */
class GameView : public QGraphicsView
{
	Q_OBJECT

public:
	GameView(QWidget *parent);
	~GameView();

	CasaEngine::GameEditor * GameEditor() const;
	void GameEditor(CasaEngine::GameEditor * val);

	void contextMenuEvent(QContextMenuEvent *event);
	void mousePressEvent( QMouseEvent *event);
	void mouseReleaseEvent( QMouseEvent *event);
	void mouseDoubleClickEvent( QMouseEvent *event);
	void mouseMoveEvent( QMouseEvent *event);
	void wheelEvent( QWheelEvent *event);
	void keyPressEvent( QKeyEvent *event);
	void keyReleaseEvent( QKeyEvent *event);
	void focusInEvent( QFocusEvent *event);
	void focusOutEvent( QFocusEvent *event);
	void enterEvent( QEvent *event);
	void leaveEvent( QEvent *event);
	void moveEvent( QMoveEvent *event);
	void resizeEvent( QResizeEvent *event);
	void closeEvent( QCloseEvent *event);
	void dragEnterEvent( QDragEnterEvent *event);
	void dragMoveEvent( QDragMoveEvent *event);
	void dragLeaveEvent( QDragLeaveEvent *event);
	void dropEvent( QDropEvent *event);
	void showEvent( QShowEvent *event);
	void hideEvent( QHideEvent *event);

private slots:

	void CutMenuClicked();

private:
	CasaEngine::Key::Code VirtualKeyCodeToSF(int val_);

	CasaEngine::GameEditor *m_pGameEditor;	
};

#endif // GAMEVIEW_H
