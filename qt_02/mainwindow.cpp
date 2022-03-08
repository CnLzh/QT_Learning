#include<QtWidgets>

#include"mainwindow.h"
#include"finddialog.h"
#include"gotocelldialog.h"
#include"sortdialog.h"
#include"spreadsheet.h"

MainWindow::MainWindow()
{
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    setAttribute(Qt::WA_DeleteOnClose);

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
    connect(newAction,SIGNAL(triggered(bool)),this,SLOT(newFile()));

    openAction = new QAction(tr("&Open"),this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));

    saveAction = new QAction(tr("&Save"),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the spreadshhet file"));
    connect(saveAction,SIGNAL(triggered(bool)),this,SLOT(save()));

    saveAsAction = new QAction(tr("Save &As"),this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save as the spreadshhet file"));
    connect(saveAsAction,SIGNAL(triggered(bool)),this,SLOT(saveAs()));

    for(int i = 0; i < MaxRecentFiles; i++){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i],SIGNAL(triggered()),this,SLOT(openRecentFile()));
    }

    cutAction = new QAction(tr("&Cut"),this);
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut cells"));
    connect(cutAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(cut()));

    copyAction = new QAction(tr("&Copy"),this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy cells"));
    connect(copyAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"),this);
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste cells"));
    connect(pasteAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(paste()));

    deleteAction = new QAction(tr("&Delete cells"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete cells"));
    connect(deleteAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(del()));

    closeAction = new QAction(tr("&Close"),this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close this application"));
    connect(closeAction,SIGNAL(triggered(bool)),this,SLOT(close()));

    exitAction = new QAction(tr("E&xit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction,SIGNAL(triggered(bool)),qApp,SLOT(closeAllWindows()));

    selectRowAction = new QAction(tr("&Row"),this);
    selectRowAction->setStatusTip(tr("Select row the cells in the spreadsheet"));
    connect(selectRowAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(selectCurrentRow()));

    selectColumnAction = new QAction(tr("&Column"),this);
    selectColumnAction->setStatusTip(tr("Select column the cells in the spreadsheet"));
    connect(selectColumnAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(selectCurrentColumn()));

    selectAllAction = new QAction(tr("&All"),this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(selectAll()));

    findAction = new QAction(tr("&Find"),this);
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("Find the cells int the spreadsheet"));
    connect(findAction,SIGNAL(triggered(bool)),this,SLOT(find()));

    goToCellAction = new QAction(tr("&Go to Cell"),this);
    goToCellAction->setShortcut(tr("Ctrl+G"));
    goToCellAction->setStatusTip(tr("Go to the Cell"));
    connect(goToCellAction,SIGNAL(triggered(bool)),this,SLOT(goToCell()));

    recalculateAction = new QAction(tr("&Recalculate"),this);
    recalculateAction->setShortcut(tr("F9"));
    recalculateAction->setStatusTip(tr("Recalculate the spreadsheet's grid"));
    connect(recalculateAction,SIGNAL(triggered(bool)),spreadsheet,SLOT(recalculate()));

    sortAction = new QAction(tr("&Sort"),this);
    sortAction->setStatusTip(tr("Sort the Cell"));
    connect(sortAction,SIGNAL(triggered(bool)),this,SLOT(sort()));

    showGridAction = new QAction(tr("&Show Grid"),this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction,SIGNAL(toggled(bool)),spreadsheet,SLOT(setShowGrid(bool)));

    autoRecalcAction = new QAction(tr("&Auto-Recalculate"),this);
    autoRecalcAction->setCheckable(true);
    autoRecalcAction->setChecked(spreadsheet->autoRecalculate());
    autoRecalcAction->setStatusTip(tr("Auto recalculate the spreadsheet's grid"));
    connect(autoRecalcAction,SIGNAL(toggled(bool)),spreadsheet,SLOT(setAutoRecalculate(bool)));

    aboutAction = new QAction(tr("&About"),this);
    aboutAction->setStatusTip(tr("Shwo the library's About box"));
    connect(aboutAction,SIGNAL(triggered(bool)),this,SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"),this);
    aboutQtAction->setStatusTip(tr("Shwo the Qt library's About box"));
    connect(aboutQtAction,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator();
    for(int i = 0; i < MaxRecentFiles; i++)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select"));
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Option"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}

void MainWindow::createContexMenu()
{
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel,1);

    connect(spreadsheet,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(updateStatusBar()));
    connect(spreadsheet,SIGNAL(modified()),this,SLOT(spreadsheetModified()));
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void MainWindow::newFile()
{
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
}

bool MainWindow::okToContinue()
{
    if(isWindowModified()){
        int r = QMessageBox::warning(this,tr("Spreadsheet"),
                                     tr("The document has been modified.\n"
                                        "Do you want to save your changes?"),
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes)
            return save();
        else if(r == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::open()
{
    if(okToContinue()){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Spreadshhet"),",",
                                                        tr("Spreadsheet filese (*.sp"));
        if(!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    if(spreadsheet->readFile(fileName)){
        statusBar()->showMessage(tr("Loading canceled"),2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"),2000);
    return true;
}

bool MainWindow::save()
{
    if(curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(!spreadsheet->writeFile(fileName)){
        statusBar()->showMessage(tr("Saving canceled"),2000);
        return false;
    }
   setCurrentFile(fileName);
   statusBar()->showMessage(tr("File saved"),2000);
   return true;
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Spreadsheet"),".",
                                                    tr("Spreadsheet files (*.sp"));
    if(fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinue()){
        writeSettings();
        event->accept();
    }
    else
        event->ignore();
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString showName = tr("Untitled");
    if(!curFile.isEmpty()){
        showName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        for (QWidget *widget : QApplication::topLevelWidgets())
            if(MainWindow *mainWin = qobject_cast<MainWindow *>(widget))
                mainWin->updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(showName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while(i.hasNext()){
        if(!QFile::exists(i.next()))
            i.remove();
    }

    for(int j=0; j < MaxRecentFiles; j++){
        if(j < recentFiles.count()){
            QString text = tr("&%1 %2")
                    .arg(j + 1)
                    .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
            recentFileActions[j]->setVisible(false);
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile()
{
    if(okToContinue()){
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::find()
{
    if(!findDialog){
        findDialog = new FindDialog(this);
        connect(findDialog,SIGNAL(findNext(const QString &,Qt::CaseSensitivity)),
                spreadsheet,SLOT(findNext(const QString &,Qt::CaseSensitivity)));
        connect(findDialog,SIGNAL(findPrevious(const QString &,Qt::CaseSensitivity)),
                spreadsheet,SLOT(findPrevious(const QString &,Qt::CaseSensitivity)));
    }
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::goToCell()
{
    GoToCellDialog dialog(this);
    if(dialog.exec()){
        QString str = dialog.getCellLocation().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,
                                    str[0].unicode() - 'A');
    }
}

void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange(QChar('A' + range.leftColumn()),
                          QChar('A' + range.rightColumn()));
    if(dialog.exec()){
        SpreadsheetCompare compare;
        compare.keys[0] =
                dialog.getPrimaryColumnCombo()->currentIndex();
        compare.keys[1] =
                dialog.getSecondaryColumnCombo()->currentIndex() - 1;
        compare.keys[2] =
                dialog.getTertiaryColumnCombo()->currentIndex() - 1;
        compare.ascending[0] =
                (dialog.getPrimaryOrderCombo()->currentIndex() == 0);
        compare.ascending[1] =
                (dialog.getSecondaryOrderCombo()->currentIndex() == 0);
        compare.ascending[2] =
                (dialog.getTertiaryOrderCombo()->currentIndex() == 0);
        spreadsheet->sort(compare);
    }
}

 void MainWindow::about()
 {
     QMessageBox::about(this,tr("About Spreadsheet"),
                        tr("<h2>Spreadsheet 1.1</h2>"
                           "<p>Copyright &copy; 2008 Software Inc."
                           "<p>Spreadsheet is a small application that "
                           "demonstrates QAction, QMainWinodw, QmenuBar ,"
                           "QStatusBar, QTableWidget, QToolBar, and many other "
                           "Qt classes."));
 }

 void MainWindow::writeSettings()
 {
     QSettings settings("Software Inc.","Spreadsheet");

     settings.setValue("geometry",saveGeometry());
     settings.setValue("recentFiles",recentFiles);
     settings.setValue("showGrid",showGridAction->isChecked());
     settings.setValue("autoRecalc",autoRecalcAction->isChecked());
 }

 void MainWindow::readSettings()
 {
     QSettings settings("Software Inc.","Spreadsheet");
     restoreGeometry(settings.value("geometry").toByteArray());

     recentFiles = settings.value("recentFiles").toStringList();
     for (QWidget *widget : QApplication::topLevelWidgets())
         if(MainWindow *mainWin = qobject_cast<MainWindow *>(widget))
             mainWin->updateRecentFileActions();

     bool showGrid = settings.value("showGrid",true).toBool();
     for (QWidget *widget : QApplication::topLevelWidgets())
         if(MainWindow *mainWin = qobject_cast<MainWindow *>(widget))
             mainWin->showGridAction->setChecked(showGrid);


     bool autoRecalc = settings.value("autoRecalc",true).toBool();
     for (QWidget *widget : QApplication::topLevelWidgets())
         if(MainWindow *mainWin = qobject_cast<MainWindow *>(widget))
             mainWin->autoRecalcAction->setChecked(autoRecalc);
 }
