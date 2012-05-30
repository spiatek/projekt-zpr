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
	bool save();
	void quit();
	void about();
	void switchPlot();

#ifndef QT_NO_PRINTER
    void print();
#endif

	void exportDocument();
	
signals:
	void plotRefresh();
	void plotSwitched(int);

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);

	QMenu *fileMenu;
	QMenu *switchMenu;
	QMenu *helpMenu;

	QToolBar *fileToolBar;
	
	QAction *openAction;
	QAction *printAction;
	QAction *switchAction;
	QAction *exportAction;
	QAction *exitAction;
	QAction *aboutAct;
	QAction *aboutQtAct;

	int plot_type;

	QWidget *w;
	QHBoxLayout *hLayout;

    Panel *roc_panel;
    Panel *pr_panel;
	Panel *current_panel;

	Plot *roc_plot;
	Plot *pr_plot;
	Plot *current_plot;
	
	//wywalic
	ProxyFile *pFile;
	QVector<QPointF>* dPoints;
};
