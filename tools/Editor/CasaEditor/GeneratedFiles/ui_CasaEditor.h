/********************************************************************************
** Form generated from reading UI file 'CasaEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASAEDITOR_H
#define UI_CASAEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GameView.h"

QT_BEGIN_NAMESPACE

class Ui_CasaEditorClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionExit;
    QAction *actionClose_project;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionButtonToolTest;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    GameView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuWindows;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;

    void setupUi(QMainWindow *CasaEditorClass)
    {
        if (CasaEditorClass->objectName().isEmpty())
            CasaEditorClass->setObjectName(QStringLiteral("CasaEditorClass"));
        CasaEditorClass->resize(924, 558);
        CasaEditorClass->setAnimated(false);
        CasaEditorClass->setTabShape(QTabWidget::Rounded);
        actionOpen = new QAction(CasaEditorClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(CasaEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave_as = new QAction(CasaEditorClass);
        actionSave_as->setObjectName(QStringLiteral("actionSave_as"));
        actionExit = new QAction(CasaEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionClose_project = new QAction(CasaEditorClass);
        actionClose_project->setObjectName(QStringLiteral("actionClose_project"));
        actionUndo = new QAction(CasaEditorClass);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(CasaEditorClass);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionCut = new QAction(CasaEditorClass);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        actionCopy = new QAction(CasaEditorClass);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        actionPaste = new QAction(CasaEditorClass);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        actionButtonToolTest = new QAction(CasaEditorClass);
        actionButtonToolTest->setObjectName(QStringLiteral("actionButtonToolTest"));
        centralWidget = new QWidget(CasaEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new GameView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMouseTracking(false);
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setContextMenuPolicy(Qt::DefaultContextMenu);

        verticalLayout->addWidget(graphicsView);

        CasaEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CasaEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 924, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuWindows = new QMenu(menuBar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        CasaEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CasaEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CasaEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CasaEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CasaEditorClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(CasaEditorClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setFloating(false);
        dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        CasaEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuWindows->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionClose_project);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        mainToolBar->addAction(actionButtonToolTest);

        retranslateUi(CasaEditorClass);

        QMetaObject::connectSlotsByName(CasaEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CasaEditorClass)
    {
        CasaEditorClass->setWindowTitle(QApplication::translate("CasaEditorClass", "Casa editor", 0));
        actionOpen->setText(QApplication::translate("CasaEditorClass", "Open", 0));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("CasaEditorClass", "Open a project", 0));
#endif // QT_NO_TOOLTIP
        actionOpen->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("CasaEditorClass", "Save the current project", 0));
        actionSave->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+S", 0));
        actionSave_as->setText(QApplication::translate("CasaEditorClass", "Save as...", 0));
        actionExit->setText(QApplication::translate("CasaEditorClass", "Exit", 0));
        actionClose_project->setText(QApplication::translate("CasaEditorClass", "Close project", 0));
#ifndef QT_NO_TOOLTIP
        actionClose_project->setToolTip(QApplication::translate("CasaEditorClass", "Close the current project", 0));
#endif // QT_NO_TOOLTIP
        actionUndo->setText(QApplication::translate("CasaEditorClass", "Undo the last action", 0));
        actionUndo->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("CasaEditorClass", "Redo the last action", 0));
        actionRedo->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+Y", 0));
        actionCut->setText(QApplication::translate("CasaEditorClass", "Cut", 0));
        actionCut->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+X", 0));
        actionCopy->setText(QApplication::translate("CasaEditorClass", "Copy", 0));
        actionCopy->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+C", 0));
        actionPaste->setText(QApplication::translate("CasaEditorClass", "Paste", 0));
        actionPaste->setShortcut(QApplication::translate("CasaEditorClass", "Ctrl+V", 0));
        actionButtonToolTest->setText(QApplication::translate("CasaEditorClass", "test button tool", 0));
#ifndef QT_NO_TOOLTIP
        actionButtonToolTest->setToolTip(QApplication::translate("CasaEditorClass", "sdvsd", 0));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("CasaEditorClass", "File", 0));
        menuEdit->setTitle(QApplication::translate("CasaEditorClass", "Edit", 0));
        menuWindows->setTitle(QApplication::translate("CasaEditorClass", "Windows", 0));
        menuHelp->setTitle(QApplication::translate("CasaEditorClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class CasaEditorClass: public Ui_CasaEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASAEDITOR_H
