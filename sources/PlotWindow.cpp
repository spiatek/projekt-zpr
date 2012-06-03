/**
 * @file
 * @author  Szymon Piątek, Mateusz Matuszewski
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 */

#include "../headers/PlotWindow.h"
#include "../headers/FunctionData.h"
#include "../headers/Panel.h"
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
#include <QErrorMessage>

/**
* PlotWindow class constructor
*/
PlotWindow::PlotWindow()
{
	w = new QWidget(this);

	///create plot and panel objects for each type
	roc_plot = new Plot(w, 0);
	pr_plot = new Plot(w, 1);
	roc_panel = new Panel(w, 0);
	pr_panel = new Panel(w, 0);

	///set pr_plot as current plot
	current_plot = pr_plot;
	current_panel = pr_panel;
	plot_type = 1;

	///add widget layout
	hLayout = new QHBoxLayout(w);
	hLayout->addWidget(current_panel);
	hLayout->addWidget(current_plot,10);
	 
	setCentralWidget(w);

	///create actions, menus and bars
	createActions();
	createMenus();
	createToolBars();
	createStatusBar();

	///call switch plot method, activate signals and slots
	switched = 0;
	switchPlot();

	setUnifiedTitleAndToolBarOnMac(true);
}

/**
* Plot class closeEvent method is called while QCloseEvent was captured
* @param event 
*/
void PlotWindow::closeEvent(QCloseEvent *event)
{
	event->accept();
}
 
void PlotWindow::switchPlot()
{
	///hide current panel and plot
	current_panel->hide();
	current_plot->hide();

	///display the other one
	plot_type = (plot_type + 1) % 2;
	current_panel = (plot_type == 0) ? roc_panel : pr_panel;
	current_panel->setVisible(true);
	current_plot = (plot_type == 0) ? roc_plot : pr_plot;
	current_plot->setVisible(true);

	///restore layout
	hLayout->addWidget(current_panel);
	hLayout->addWidget(current_plot,10);
	switchAction->setChecked(false);

	///connect signals to slots while switching by the first time
	if(switched < 2) {
		
		///activate signals sent from Plot to Panel
		connect(current_plot,	SIGNAL(curveAdded(QString, QColor, double)),	current_panel,	SLOT(addCurve(QString, QColor, double)));
		connect(current_plot,	SIGNAL(resendColorAuc(QColor, double)),			current_panel,	SLOT(readColorAuc(QColor, double)));
		
		///activate signals sent from Panel to Plot
		connect(current_panel,	SIGNAL(nameChange(int, QString)),				current_plot,	SLOT(changeName(int, QString)));
		connect(current_panel,	SIGNAL(colorChange(int, QColor)),				current_plot,	SLOT(changeColor(int, QColor)));
		connect(current_panel,	SIGNAL(getColorAuc(int)),						current_plot,	SLOT(getColAuc(int)));
		connect(current_panel,	SIGNAL(curveDelete(int)),						current_plot,	SLOT(deleteCurve(int)));
		connect(current_panel,	SIGNAL(hideAllExceptOfThis(int)),				current_plot,	SLOT(leaveOneUnhided(int)));
		connect(current_panel,	SIGNAL(clearPlot()),							current_plot,	SLOT(clearAll()));
		connect(current_panel,	SIGNAL(changeBackgroundColor(QColor)),			current_plot,	SLOT(modifyBackgroundColor(QColor)));
		connect(current_panel,	SIGNAL(plotNameChange(QString)),				current_plot,	SLOT(changePlotName(QString)));
		connect(current_panel,	SIGNAL(labelsChange(QString, QString)),			current_plot,	SLOT(changePlotLabels(QString, QString)));
		connect(current_panel,	SIGNAL(gridChange(int)),						current_plot,	SLOT(changeGridState(int)));

		///activate signal sent from PlotWindow to Plot
		connect(clearAction,	SIGNAL(triggered()),							current_plot,	SLOT(clearAll()));
	}
	switched++;
}

/**
* Plot class open slot is called when open button was clicked
*/
void PlotWindow::open()
{
	///display open file window
	QString fileName = QFileDialog::getOpenFileName(this,
	 	tr("Open File"), QDir::currentPath(), tr("ROC files (*.roc);;PR files (*.pr);;all files (*.*)"));

	if (fileName.isEmpty()){
		return;
	}

	QStringList field = fileName.split(".", QString::SkipEmptyParts);
	
	QStringList::const_iterator constIterator;
    constIterator = --field.constEnd();
    
	///check file format, if roc or pr - load data
	try {
		if (constIterator->compare("roc",Qt::CaseInsensitive)==0){
			roc_plot->addCurve(fileName, 0);
		}
		else if (constIterator->compare("pr",Qt::CaseInsensitive)==0){ 
			pr_plot->addCurve(fileName, 1);
		}
		else {
			throw 1000;
		}
	}
	catch(int e){
		QErrorMessage errorMessage;
		if (e==1000)
			errorMessage.showMessage("error. unknown file extension");
		else if (e==1001)
			errorMessage.showMessage("error parsing the file. unsupported structure of file");
		else if (e==1002)
			errorMessage.showMessage("error parsing the file. data conversion failed");
		else if (e==1003)
			errorMessage.showMessage("error parsing the file. to little data points");
		errorMessage.exec();
	}
}

/**
* Plot class about slot is called when about option was set
*/
void PlotWindow::about()
{	
	QMessageBox::about(this, tr("About program"), 
		tr("Program enables loading curves from files with .roc and .pr extensions."));
}

/**
* Plot class createActions method is called by PlotWindow constructor.
* It creates PlotWindow actions and connect them to specified slots
*/
void PlotWindow::createActions()
{
	///create openAction, load an icon, and connect it to slot open()
	openAction = new QAction(QIcon("images/open.png"), tr("&Open..."), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	///create exitAction, load an icon, and connect it to slot close()
	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	///create printAction, load an icon, and connect it to slot print()
#ifndef QT_NO_PRINTER
	printAction = new QAction(QIcon("images/print.png"), tr("Print"), this);
	printAction->setShortcuts(QKeySequence::Print);
	printAction->setStatusTip(tr("Print plot"));
	connect(printAction, SIGNAL(triggered()), this, SLOT(print()));
#endif

	///create exportAction, load an icon, and connect it to slot exportDocument()
	exportAction = new QAction(QIcon("images/save.png"), tr("&Export"), this);
	exportAction->setStatusTip(tr("Export plot"));
	connect(exportAction, SIGNAL(triggered()), this, SLOT(exportDocument()));

	///create switchAction, load an icon, and connect it to slot switchPlot()
	switchAction = new QAction(QIcon("images/switch.png"), tr("Switch"), this);
	switchAction->setStatusTip(tr("Switch plot"));
	connect(switchAction, SIGNAL(triggered()), this, SLOT(switchPlot()));
	
	///create clearAction and  load an icon
	clearAction = new QAction(QIcon("images/clear.png"), tr("Clear"), this);
	clearAction->setStatusTip(tr("Clear plot"));

	///create aboutAction, load an icon, and connect it to slot about()
	aboutAct = new QAction(tr("&About"), this);
	aboutAct->setStatusTip(tr("Show the application's About box"));
	connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

/**
* Plot class createMenus method is called by PlotWindow constructor. It creates menu bar for PlotWindow.
*/
void PlotWindow::createMenus()
{
	///create file menu on menu bar
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);

#ifndef QT_NO_PRINTER
    fileMenu->addAction(printAction);
#endif

	fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    menuBar()->addSeparator();

 	///create plot menu on menu bar
    plotMenu = menuBar()->addMenu(tr("&Plot"));
	plotMenu->addAction(switchAction);
	plotMenu->addAction(clearAction);

	///create help menu on menu bar
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

/**
* Plot class createToolBars method is called by PlotWindow constructor. It creates toolbar for PlotWindow.
*/
void PlotWindow::createToolBars()
{
	///create file toolbar
	fileToolBar = addToolBar(tr("File"));

	///add actions
	fileToolBar->addAction(openAction);
	fileToolBar->addSeparator();
	fileToolBar->addAction(switchAction);
	fileToolBar->addAction(clearAction);
	fileToolBar->addSeparator();

#ifndef QT_NO_PRINTER
	fileToolBar->addAction(printAction);
#endif

	fileToolBar->addAction(exportAction);
}

/**
* Plot class createStatusBar method
*/
void PlotWindow::createStatusBar()
{
	statusBar()->showMessage(tr("Ready"));
}

#ifndef QT_NO_PRINTER

/**
* Plot class print slot is called while clicking a button on a bar. It is used to print current plot.
*/
void PlotWindow::print()
{
    QPrinter printer(QPrinter::HighResolution);

    QString docName = current_plot->title().text();
    if ( !docName.isEmpty() ){
        docName.replace (QRegExp (QString::fromLatin1 ("\n")), tr (" -- "));
        printer.setDocName (docName);
    }

    printer.setCreator("Plot example");
    printer.setOrientation(QPrinter::Landscape);

    QPrintDialog dialog(&printer);
    if ( dialog.exec() ){
        QwtPlotRenderer renderer;

        if ( printer.colorMode() == QPrinter::GrayScale ){
            renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground);
            renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales);
        }
        renderer.renderTo(current_plot, printer);
    }
}

#endif

/**
* Plot class exportDocument slot is called while clicking a button on a bar. 
* It is used to export current plot to a file. Format is specified in export document window.
*/
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

    if ( imageFormats.size() > 0 ){
        QString imageFilter("Images (");
        for ( int i = 0; i < imageFormats.size(); i++ ){
            if ( i > 0 )
                imageFilter += " ";
            imageFilter += "*.";
            imageFilter += imageFormats[i];
        }
        imageFilter += ")";
        filter += imageFilter;
    }
    fileName = QFileDialog::getSaveFileName(this, "Export File Name", fileName, filter.join(";;"), NULL, QFileDialog::DontConfirmOverwrite);
#endif
	
    if ( !fileName.isEmpty() ){
        QwtPlotRenderer renderer;
		
        // flags to make the document look like the widget
        renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, false);
        renderer.setLayoutFlag(QwtPlotRenderer::KeepFrames, true);

        renderer.renderDocument(current_plot, fileName, QSizeF(300, 200), 85);
	}
}
