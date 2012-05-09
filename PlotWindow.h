#pragma once
#include "Plot.h"
#include <qmainwindow.h>

class PlotWindow : public QMainWindow 
{	
	Q_OBJECT

public:
	PlotWindow();

private slots:
	void open();
	void save();
	void quit();

private:
	Plot *plot;

	QAction *openAction;
	QAction *saveAction;
	QAction *exitAction;

	QMenu *fileMenu;
};