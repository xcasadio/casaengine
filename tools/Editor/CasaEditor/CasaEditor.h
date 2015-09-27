#ifndef CASAEDITOR_H
#define CASAEDITOR_H

#include <QtWidgets/QMainWindow>
#include "ui_CasaEditor.h"
#include "GameThread.h"
#include "qevent.h"

class CasaEditor : public QMainWindow
{
	Q_OBJECT

public:
	CasaEditor(QWidget *parent = 0);
	~CasaEditor();

private:
	Ui::CasaEditorClass ui;
	GameThread *m_pGameThread;

protected:
	void showEvent(QShowEvent *event);
	void closeEvent(QCloseEvent *event);

	//void keyPressEvent( QKeyEvent *event);

	bool event(QEvent *event);


	void contextMenuEvent(QContextMenuEvent *event);

private slots:
	void OpenProjectItemMenuClicked();
	void SaveProjectItemMenuClicked();
	void SaveAsProjectItemMenuClicked();
	void ContextMenuClicked(QPoint &point_);
};

#endif // CASAEDITOR_H
