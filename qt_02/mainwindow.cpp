#include<QIcon>
#include<QAction>
#include<QLabel>
#include<QMenu>
#include<QToolBar>

#include"mainwindow.h"
#include"finddialog.h"
#include"gotocelldialog.h"
#include"sortdialog.h"
#include"spreadsheet.h"

MainWindow::MainWindow()
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContexMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDialog = nullptr;

    setWindowIcon(QIcon("/images/icon.png"));
    setCurrentFile("");
}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"),this);
    newAction->setIcon(QIcon(":/iamges/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));

    for(int i = 0; i < MaxRecentFiles; i++){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }

    exitAction = new QAction(tr("E&xit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    selectAllAction = new QAction(tr("&All"),this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction,SIGNAL(toggled()),spreadsheet,SLOT(setShowGrid()));

    showGridAction = new QAction(tr("&Show Grid"),this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction,SIGNAL(toggled()),spreadsheet,SLOT(setShowGrid()));

    aboutQtAction = new QAction(tr("About &Qt"),this);
    aboutQtAction->setStatusTip(tr("Shwo the Qt library's About box"));
    connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));

}
