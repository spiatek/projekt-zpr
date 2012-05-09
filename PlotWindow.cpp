#include "PlotWindow.h"
#include <qlayout.h>
#include <qaction.h>
#include <qtextcodec.h>
#include <qapplication.h>
#include <qmenubar.h>

PlotWindow::PlotWindow()
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));		//nie do koñca dzia³a
    openAction = new QAction(tr("&Otwórz"), this);
	saveAction = new QAction(tr("Zapi&sz"), this);
	exitAction = new QAction(tr("&WyjdŸ"), this);

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

void PlotWindow::quit()
{
}

void PlotWindow::save()
{
}

void PlotWindow::open()
{
}