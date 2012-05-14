#pragma once
#include "Plot.h"
//#include "CurveManager.h"
#include <qmainwindow.h>

class QAction;
class QMenu;
class QPlainTextEdit;

class PlotWindow : public QMainWindow 
{	
	Q_OBJECT

public:
	PlotWindow();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void open();
	bool save();
	void quit();
	//void newFile();
	bool saveAs();
	void about();
	//void plotWasModified();

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
	QAction *exitAction;
	//QAction *cutAct;
	//QAction *copyAct;
	//QAction *pasteAct;
	QAction *aboutAct;
	QAction *aboutQtAct;

	//CurveManager *manager;
	Plot *roc_plot;
	Plot *pr_plot;
};