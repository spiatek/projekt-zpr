#include "..\headers\PlotWindow.h"
#include "..\headers\FunctionData.h"
#include "..\headers\Panel.h"
#include <qlayout.h>
#include <qaction.h>
#include <qtextcodec.h>
#include <qapplication.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qimagewriter.h>
#include <qprinter.h>
#include <qstatusbar.h>
#include <qstyleoption.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qevent.h>
#include <qsettings.h>
#include <qfileinfo.h>
#include <qfiledialog.h>
#include <qprintdialog.h>
#include <qwt_plot_renderer.h>

PlotWindow::PlotWindow()
 {
     //textEdit = new QPlainTextEdit;
     //setCentralWidget(textEdit);
	 
	 QWidget *w = new QWidget(this);
	 roc_plot = new Plot(w);
	 //pr_plot = new Plot(w);
	 panel = new Panel(w);

	 QHBoxLayout *hLayout = new QHBoxLayout(w);
	 hLayout->addWidget(panel);
	 hLayout->addWidget(roc_plot,10);
	 
	 setCentralWidget(w);

     createActions();
     createMenus();
     createToolBars();
     createStatusBar();

     readSettings();

     connect(roc_plot, SIGNAL(contentsChanged()), this, SLOT(plotWasModified()));
	 connect(roc_plot, SIGNAL(coordinatesAssembled(QPoint)), this, SLOT(coordinates(QPoint)));
	 connect(this, SIGNAL(plotRefresh()), roc_plot, SLOT(refreshEvent()));
	 connect(roc_plot, SIGNAL(curveAdded(QString, QColor, double)), panel, SLOT(addCurve(QString, QColor, double)));

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

void PlotWindow::quit()
{
}

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

	 emit plotRefresh();
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
 
 void PlotWindow::plotWasModified()
 {
     //setWindowModified(plot->document()->isModified());
 }

 void PlotWindow::createActions()
 {
	 newAct = new QAction(QIcon("images/new.png"), tr("&New"), this);
     newAct->setShortcuts(QKeySequence::New);
     newAct->setStatusTip(tr("Create a new file"));
     //connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

     openAction = new QAction(QIcon("images/open.png"), tr("&Open..."), this);
     openAction->setShortcuts(QKeySequence::Open);
     openAction->setStatusTip(tr("Open an existing file"));
     connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

     saveAction = new QAction(QIcon("images/save.png"), tr("&Save"), this);
     saveAction->setShortcuts(QKeySequence::Save);
     saveAction->setStatusTip(tr("Save the document to disk"));
     //connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

     saveAsAct = new QAction(tr("Save &As..."), this);
     saveAsAct->setShortcuts(QKeySequence::SaveAs);
     saveAsAct->setStatusTip(tr("Save the document under a new name"));
     //connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

     exitAction = new QAction(tr("E&xit"), this);
     exitAction->setShortcuts(QKeySequence::Quit);
     exitAction->setStatusTip(tr("Exit the application"));
     connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

#ifndef QT_NO_PRINTER
	 printAction = new QAction(QIcon("images/print.png"), tr("Print"), this);
	 printAction->setShortcuts(QKeySequence::Print);
	 printAction->setStatusTip(tr("Print plot"));
	 connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
#endif

     exportAction = new QAction(QIcon("images/save.png"), tr("&Export"), this);
     exportAction->setStatusTip(tr("Export document"));
     connect(exportAction, SIGNAL(triggered()), this, SLOT(exportDocument()));

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
     //fileMenu->addAction(newAct);
     fileMenu->addAction(openAction);
     //fileMenu->addAction(saveAction);
     //fileMenu->addAction(saveAsAct);
#ifndef QT_NO_PRINTER
     fileMenu->addAction(printAction);
#endif
     fileMenu->addAction(exportAction);
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

 void PlotWindow::coordinates(QPoint point)
 {
     statusBar()->showMessage(QString("Wspó³rzêdne (%1,%2)").arg(point.x()).arg(point.y()));
 }

 void PlotWindow::createToolBars()
 {
     fileToolBar = addToolBar(tr("File"));
     //fileToolBar->addAction(newAct);
     fileToolBar->addAction(openAction);
     //fileToolBar->addAction(saveAction);
#ifndef QT_NO_PRINTER
	 fileToolBar->addAction(printAction);
#endif
	 fileToolBar->addAction(exportAction);


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


#ifndef QT_NO_PRINTER

void PlotWindow::print()
{
    QPrinter printer(QPrinter::HighResolution);

    QString docName = roc_plot->title().text();
    if ( !docName.isEmpty() )
    {
        docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
        printer.setDocName (docName);
    }

    printer.setCreator("Plot example");
    printer.setOrientation(QPrinter::Landscape);

    QPrintDialog dialog(&printer);
    if ( dialog.exec() )
    {
        QwtPlotRenderer renderer;

        if ( printer.colorMode() == QPrinter::GrayScale )
        {
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }

        renderer.renderTo(roc_plot, printer);
    }
}

#endif

void PlotWindow::exportDocument()
{
#ifndef QT_NO_PRINTER
    QString fileName = "plot.pdf";
#else
    QString fileName = "plot.png";
#endif
	
#ifndef QT_NO_FILEDIALOG
    const QList<QByteArray> imageFormats = QImageWriter::supportedImageFormats();
	
    QStringList filter;
    filter += "PDF Documents (*.pdf)";
#ifndef QWT_NO_SVG
    filter += "SVG Documents (*.svg)";
#endif
    filter += "Postscript Documents (*.ps)";

    if ( imageFormats.size() > 0 )
    {
        QString imageFilter("Images (");
        for ( int i = 0; i < imageFormats.size(); i++ )
        {
            if ( i > 0 )
                imageFilter += " ";
            imageFilter += "*.";
            imageFilter += imageFormats[i];
        }
        imageFilter += ")";

        filter += imageFilter;
    }

    fileName = QFileDialog::getSaveFileName(
        this, "Export File Name", fileName,
        filter.join(";;"), NULL, QFileDialog::DontConfirmOverwrite);
#endif
	
    if ( !fileName.isEmpty() )
    {
        QwtPlotRenderer renderer;
		
        // flags to make the document look like the widget
        renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, false);
        renderer.setLayoutFlag(QwtPlotRenderer::KeepFrames, true);

        renderer.renderDocument(roc_plot, fileName, QSizeF(300, 200), 85);
	}
}
