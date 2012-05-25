#pragma once
#include "..\headers\Plot.h"
//#include "CurveManager.h"
#include <qmainwindow.h>
#include <qpoint.h>

class QAction;
class QMenu;
class QPlainTextEdit;
class Panel;

class PlotWindow : public QMainWindow 
{	
	Q_OBJECT

public:
	PlotWindow();

protected:
	void closeEvent(QCloseEvent*);
	//bool eventFilter(QObject *obj, QEvent *event);

private slots:
	void open();
	bool save();
	void quit();
	//void newFile();
	bool saveAs();
	void about();
	void plotWasModified();
	void coordinates(QPoint);

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
	
	//QPlainTextEdit *textEdit;
	QString curFile;

	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *helpMenu;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	QAction *newAct;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAct;
	QAction *printAction;
	QAction *exportAction;
	QAction *exitAction;
	//QAction *cutAct;
	//QAction *copyAct;
	//QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	//CurveManager *manager;
    Panel *panel;
	Plot *roc_plot;
	Plot *pr_plot;
};