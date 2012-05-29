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
	 w = new QWidget(this);
	 roc_plot = new Plot(w, 0);
	 pr_plot = new Plot(w, 1);
	 panel = new Panel(w);

	 pr_plot->hide();
	 current_plot = roc_plot;
	 plot_type = 0;

	 hLayout = new QHBoxLayout(w);
	 hLayout->addWidget(panel);
	 hLayout->addWidget(current_plot,10);
	 
	 setCentralWidget(w);

     createActions();
     createMenus();
     createToolBars();
     createStatusBar();

     readSettings();

     connect(current_plot, SIGNAL(contentsChanged()), this, SLOT(plotWasModified()));
	 connect(current_plot, SIGNAL(curveAdded(QString, QColor, double)), panel, SLOT(addCurve(QString, QColor, double)));
	 connect(panel, SIGNAL(nameChange(int, QString)), current_plot, SLOT(changeName(int, QString)));
	 connect(panel, SIGNAL(colorChange(QString, QColor)), current_plot, SLOT(changeColor(QString, QColor)));
	 connect(panel, SIGNAL(getColorAuc(QString)), current_plot, SLOT(getColAuc(QString)));
	 connect(current_plot, SIGNAL(resendColorAuc(QColor, double)), panel, SLOT(readColorAuc(QColor, double)));
	 connect(panel, SIGNAL(curveDelete(int)), current_plot, SLOT(deleteCurve(int)));
	 connect(panel, SIGNAL(hideAllExceptOfThis(int)), current_plot, SLOT(leaveOneUnhided(int)));
	 connect(panel, SIGNAL(changeBackgroundColor(QColor)), current_plot, SLOT(modifyBackgroundColor(QColor)));
	 connect(panel, SIGNAL(plotNameChange(QString)), current_plot, SLOT(changePlotName(QString)));
	 connect(panel, SIGNAL(labelsChange(QString, QString)), current_plot, SLOT(changePlotLabels(QString, QString)));
	 connect(panel, SIGNAL(gridChange(int)), current_plot, SLOT(changeGridState(int)));

     setCurrentFile("");
     setUnifiedTitleAndToolBarOnMac(true);
 }

 void PlotWindow::closeEvent(QCloseEvent *event)
 {
	writeSettings();
	event->accept();
 }

void PlotWindow::quit()
{
}

void PlotWindow::switchPlot()
{
	current_plot->hide();
	plot_type = (plot_type + 1) % 2;
	current_plot = (plot_type == 0) ? roc_plot : pr_plot;
	current_plot->setVisible(true);
	hLayout->addWidget(current_plot,10);
}

void PlotWindow::open()
{
	if(plot_type == 0) {
		current_plot->addCurve(new FunctionData(::sin), 0, 1.0);
	}
	else {
		current_plot->addCurve(new FunctionData(::sin), 1, 0.7);
	}
	
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
 }

 void PlotWindow::createActions()
 {
     openAction = new QAction(QIcon("images/open.png"), tr("&Open..."), this);
     openAction->setShortcuts(QKeySequence::Open);
     openAction->setStatusTip(tr("Open an existing file"));
     connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

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

	 switchAction = new QAction(QIcon("images/switch.png"), tr("Switch"), this);
	 switchAction->setStatusTip(tr("Switch plot"));
	 connect(switchAction, SIGNAL(triggered()), this, SLOT(switchPlot()));

     aboutAct = new QAction(tr("&About"), this);
     aboutAct->setStatusTip(tr("Show the application's About box"));
     connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

     aboutQtAct = new QAction(tr("About &Qt"), this);
     aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
     connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
 }

 void PlotWindow::createMenus()
 {
     fileMenu = menuBar()->addMenu(tr("&File"));
     fileMenu->addAction(openAction);

#ifndef QT_NO_PRINTER
     fileMenu->addAction(printAction);
#endif

	 fileMenu->addAction(exportAction);
     fileMenu->addSeparator();
     fileMenu->addAction(exitAction);

     menuBar()->addSeparator();

     fileMenu = menuBar()->addMenu(tr("&Plot"));
	 fileMenu->addAction(switchAction);

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
     fileToolBar->addAction(openAction);
     
#ifndef QT_NO_PRINTER
	 fileToolBar->addAction(printAction);
#endif

	 fileToolBar->addAction(exportAction);
	 fileToolBar->addAction(switchAction);
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
     return true;
 }

 void PlotWindow::setCurrentFile(const QString &fileName)
 {
 }

 QString PlotWindow::strippedName(const QString &fullFileName)
 {
     return QFileInfo(fullFileName).fileName();
 }

#ifndef QT_NO_PRINTER

void PlotWindow::print()
{
    QPrinter printer(QPrinter::HighResolution);

    QString docName = current_plot->title().text();
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

        renderer.renderTo(current_plot, printer);
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

        renderer.renderDocument(current_plot, fileName, QSizeF(300, 200), 85);
	}
}
