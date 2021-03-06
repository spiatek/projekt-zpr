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
 * This header file contains PlotWindow class definition.
 * PlotWindow class inherits from QwtMainWindow class. 
 */

#pragma once
#include "../headers/Plot.h"
#include <qmainwindow.h>
#include <qpoint.h>
#include "../headers/fileProxy.h"

class QAction;
class QMenu;
class QPlainTextEdit;
class Panel;
class QHBoxLayout;

class PlotWindow : public QMainWindow{	
	Q_OBJECT

public:
	PlotWindow();

protected:
	void closeEvent(QCloseEvent*);

private slots:
	void open();
	void about();
	void switchPlot();
	void exportDocument();

#ifndef QT_NO_PRINTER
    void print();
#endif

signals:
	void plotSwitched(int);

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);

	QMenu *fileMenu;
	QMenu *plotMenu;
	QMenu *helpMenu;

	QToolBar *fileToolBar;
	
	QAction *openAction;
	QAction *printAction;
	QAction *switchAction;
	QAction *clearAction;
	QAction *exportAction;
	QAction *exitAction;
	QAction *aboutAct;

	int plot_type;
	int switched;

	QWidget *w;
	QHBoxLayout *hLayout;

    Panel *roc_panel;
    Panel *pr_panel;
	Panel *current_panel;

	Plot *roc_plot;
	Plot *pr_plot;
	Plot *current_plot;
};
