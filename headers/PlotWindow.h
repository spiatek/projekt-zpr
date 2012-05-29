#pragma once
#include "..\headers\Plot.h"
#include <qmainwindow.h>
#include <qpoint.h>

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
	bool saveAs();
	void about();
	void plotWasModified();
	void coordinates(QPoint);
	void switchPlot();

#ifndef QT_NO_PRINTER
    void print();
#endif

	void exportDocument();
	
signals:
	void plotRefresh();

private:
	void createActions();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool maybeSave();
	void loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);

	QString curFile;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
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

    Panel *panel;
	Plot *roc_plot;
	Plot *pr_plot;
	Plot *current_plot;
};