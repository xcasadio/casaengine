#include "CasaEditor.h"

#include <QtWidgets/QGraphicsAnchorLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QListWidget>

CasaEditor::CasaEditor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QDockWidget *dock = new QDockWidget(tr("Customers"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QListWidget *customerList = new QListWidget(dock);
	customerList->addItems(QStringList()
		<< "John Doe, Harmony Enterprises, 12 Lakeside, Ambleton"
		<< "Jane Doe, Memorabilia, 23 Watersedge, Beaton"
		<< "Tammy Shea, Tiblanka, 38 Sea Views, Carlton"
		<< "Tim Sheen, Caraba Gifts, 48 Ocean Way, Deal"
		<< "Sol Harvey, Chicos Coffee, 53 New Springs, Eccleston"
		<< "Sally Hobart, Tiroli Tea, 67 Long River, Fedula");
	dock->setWidget(customerList);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	m_pGameThread = new GameThread(this, ui.graphicsView);
	//m_pGameThread->CreateGame();
	
	ui.graphicsView->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.graphicsView, SIGNAL(customContextMenuRequested(const QPoint&)),
		this, SLOT(ContextMenuClicked(const QPoint&)));
}

CasaEditor::~CasaEditor()
{
	//delete m_pGameThread; // why bug ??
}

/**
 * 
 */
void CasaEditor::showEvent( QShowEvent *event )
{
	if (m_pGameThread != nullptr)
	{
		m_pGameThread->GameRun();
	}

	QMainWindow::showEvent(event);
}

/**
 * 
 */
void CasaEditor::closeEvent( QCloseEvent *event )
{
	if (m_pGameThread != nullptr)
	{
		m_pGameThread->GameExit();
		m_pGameThread->wait();
	}

	QMainWindow::closeEvent(event);
}

/**
 * 
 *
void CasaEngineEditor::keyPressEvent(QKeyEvent *event)
{
	int x = 0;
	x = 0;
}*/

/**
 * 
 */
bool CasaEditor::event(QEvent *event)
{
	bool res = QWidget::event(event);

	if (dynamic_cast<QKeyEvent *>(event) != nullptr)
	{
		res = false;
	}

	return res;
}

void CasaEditor::contextMenuEvent(QContextMenuEvent *event)
{

}

void CasaEditor::OpenProjectItemMenuClicked()
{

}

void CasaEditor::SaveProjectItemMenuClicked()
{

}

void CasaEditor::SaveAsProjectItemMenuClicked()
{

}

void CasaEditor::ContextMenuClicked(QPoint &point_)
{
	QMenu menu;
}
