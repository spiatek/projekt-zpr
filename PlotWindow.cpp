#include "PlotWindow.h"
#include "FunctionData.h"
#include <qlayout.h>
#include <qaction.h>
#include <qtextcodec.h>
#include <qapplication.h>
#include <qmenubar.h>
#include <qstyleoption.h>
#include <qmessagebox.h>
/*
PlotWindow::PlotWindow()
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));		//nie do koñca dzia³a
    openAction = new QAction(tr("£aduj z pliku"), this);
	saveAction = new QAction(tr("Zapisz wykres"), this);
	exitAction = new QAction(tr("Zakoñcz"), this);

	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));
	connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	fileMenu = menuBar()->addMenu(tr("&Plik"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	plot = new Plot();
    setCentralWidget(plot);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));		//nie do koñca dzia³a
	setWindowTitle(tr("Narzêdzie do porównywania wykresów"));
}

 bool PlotWindow::maybeSave()
 {
	//if (textEdit->document()->isModified()) {
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, tr("Application"),
					tr("The document has been modified.\n"
                         "Do you want to save your changes?"),
		QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
     //}
     //return true;
 }

 void PlotWindow::writeSettings()
 {
     QSettings settings("Trolltech", "Application Example");
     settings.setValue("pos", pos());
     settings.setValue("size", size());
 }

void PlotWindow::closeEvent(QCloseEvent *event)
 {
     if (maybeSave()) {
         writeSettings();
         event->accept();
     } else {
         event->ignore();
     }
 }
*/
void PlotWindow::quit()
{
}
/*
void PlotWindow::save()
{
}

void PlotWindow::open()
{
}*/

#include <QtGui>

 #include "PlotWindow.h"

PlotWindow::PlotWindow()
 {
     //textEdit = new QPlainTextEdit;
     //setCentralWidget(textEdit);

	 roc_plot = new Plot();
	 pr_plot = new Plot();
	 setCentralWidget(roc_plot);

     createActions();
     createMenus();
     createToolBars();
     createStatusBar();

     readSettings();

     //connect(plot, SIGNAL(contentsChanged()), this, SLOT(plotWasModified()));

     setCurrentFile("");
     setUnifiedTitleAndToolBarOnMac(true);
 }

 void PlotWindow::closeEvent(QCloseEvent *event)
 {
     //if (maybeSave()) {
         writeSettings();
         event->accept();
     //} else {
     //    event->ignore();
     //}
 }
/*
 void PlotWindow::newFile()
 {
     if (maybeSave()) {
         plot->;
         setCurrentFile("");
     }
 }*/

 void PlotWindow::open()
 {
     //if (maybeSave()) {
         /*QString fileName = QFileDialog::getOpenFileName(this);
         if (!fileName.isEmpty())
             loadFile(fileName);*/
	//TODO: pobieranie krzywej
	 //type = proxy.getType();
	 //auc = proxy.getAuc();
	 if(/*type == ROC*/1) {
		roc_plot->addCurve(new FunctionData(::sin), 0, 1.0/*, auc*/);
	 }
	 else {
		 pr_plot->addCurve(new FunctionData(::sin), 1, 0.7/*, auc*/);
	 }
     //}
 }

 bool PlotWindow::save()
 {
     if (curFile.isEmpty()) {
         return saveAs();
     } else {
         return saveFile(curFile);
     }
 }

 bool PlotWindow::saveAs()
 {
     QString fileName = QFileDialog::getSaveFileName(this);
     if (fileName.isEmpty())
         return false;

     return saveFile(fileName);
 }

 void PlotWindow::about()
 {
    QMessageBox::about(this, tr("O programie"),
             tr("Program pozwala na importowanie danych w formacie AUC,"
				" wyœwietlanie i porównywanie wykresów oraz zapisywanie"
				" ich do pliku."));
 }
 /*
 void PlotWindow::plotWasModified()
 {
     setWindowModified(plot->document()->isModified());
 }*/

 void PlotWindow::createActions()
 {
     newAct = new QAction(QIcon(":/images/new.png"), tr("&New"), this);
     newAct->setShortcuts(QKeySequence::New);
     newAct->setStatusTip(tr("Create a new file"));
     //connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     openAction = new QAction(QIcon(":/images/open.png"), tr("&Open..."), this);
     openAction->setShortcuts(QKeySequence::Open);
     openAction->setStatusTip(tr("Open an existing file"));
     connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

     saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
     saveAction->setShortcuts(QKeySequence::Save);
     saveAction->setStatusTip(tr("Save the document to disk"));
     connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

     saveAsAct = new QAction(tr("Save &As..."), this);
     saveAsAct->setShortcuts(QKeySequence::SaveAs);
     saveAsAct->setStatusTip(tr("Save the document under a new name"));
     connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

     exitAction = new QAction(tr("E&xit"), this);
     exitAction->setShortcuts(QKeySequence::Quit);
     exitAction->setStatusTip(tr("Exit the application"));
     connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	 /*
     cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
     cutAct->setShortcuts(QKeySequence::Cut);
     cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                             "clipboard"));
     connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

     copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
     copyAct->setShortcuts(QKeySequence::Copy);
     copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                              "clipboard"));
     connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

     pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
     pasteAct->setShortcuts(QKeySequence::Paste);
     pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                               "selection"));
     connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));
	 */
     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	 /*
     cutAct->setEnabled(false);
     copyAct->setEnabled(false);
     connect(textEdit, SIGNAL(copyAvailable(bool)), cutAct, SLOT(setEnabled(bool)));
     connect(textEdit, SIGNAL(copyAvailable(bool)), copyAct, SLOT(setEnabled(bool)));*/
 }

 void PlotWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(newAct);
     fileMenu->addAction(openAction);
     fileMenu->addAction(saveAction);
     fileMenu->addAction(saveAsAct);
     fileMenu->addSeparator();
     fileMenu->addAction(exitAction);

    /* editMenu = menuBar()->addMenu(tr("&Edit"));
     editMenu->addAction(cutAct);
     editMenu->addAction(copyAct);
     editMenu->addAction(pasteAct);*/

     menuBar()->addSeparator();

     helpMenu = menuBar()->addMenu(tr("&Help"));
     helpMenu->addAction(aboutAct);
     helpMenu->addAction(aboutQtAct);
 }

 void PlotWindow::createToolBars()
 {
     fileToolBar = addToolBar(tr("File"));
     fileToolBar->addAction(newAct);
     fileToolBar->addAction(openAction);
     fileToolBar->addAction(saveAction);

/*     editToolBar = addToolBar(tr("Edit"));
     editToolBar->addAction(cutAct);
     editToolBar->addAction(copyAct);
     editToolBar->addAction(pasteAct);*/
 }

 void PlotWindow::createStatusBar()
 {
     statusBar()->showMessage(tr("Ready"));
 }

 void PlotWindow::readSettings()
 {
     QSettings settings("Trolltech", "Application Example");
     QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
     QSize size = settings.value("size", QSize(400, 400)).toSize();
     resize(size);
     move(pos);
 }

 void PlotWindow::writeSettings()
 {
     QSettings settings("Trolltech", "Application Example");
     settings.setValue("pos", pos());
     settings.setValue("size", size());
 }
 /*
 bool PlotWindow::maybeSave()
 {
     if (textEdit->document()->isModified()) {
         QMessageBox::StandardButton ret;
         ret = QMessageBox::warning(this, tr("Application"),
                      tr("The document has been modified.\n"
                         "Do you want to save your changes?"),
                      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         if (ret == QMessageBox::Save)
             return save();
         else if (ret == QMessageBox::Cancel)
             return false;
     }
     return true;
 }
 */
 void PlotWindow::loadFile(const QString &fileName)
 {
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream in(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     //textEdit->setPlainText(in.readAll());
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
 }

 bool PlotWindow::saveFile(const QString &fileName)
 {
/*     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot write file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return false;
     }

     QTextStream out(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     out << textEdit->toPlainText();
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File saved"), 2000);*/
     return true;
 }

 void PlotWindow::setCurrentFile(const QString &fileName)
 {/*
     curFile = fileName;
     textEdit->document()->setModified(false);
     setWindowModified(false);

     QString shownName = curFile;
     if (curFile.isEmpty())
         shownName = "untitled.txt";
     setWindowFilePath(shownName);*/
 }

 QString PlotWindow::strippedName(const QString &fullFileName)
 {
     return QFileInfo(fullFileName).fileName();
 }