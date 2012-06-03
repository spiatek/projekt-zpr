/**
* @file Plot.h
* @brief This header file contains PlotWindow class definition.
* PlotWindow class inherits from QwtMainWindow class.
*
* @author Szymon Pi¹tek
*
* @date 3/6/2012
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

class PlotWindow : public QMainWindow 
{	
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
	//QAction *aboutQtAct;

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
