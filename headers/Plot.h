/**
* @file Plot.h
* @brief This header file contains Plot class definition.
* Plot class inherits from QwtPlot class.
*
* @author Szymon Pi¹tek
*
* @date 3/6/2012
*/

#pragma once

#include <vector>
#include <qpointer.h>
#include <QSharedPointer>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "../headers/Curve.h"
#include "../headers/fileProxy.h"

#define CURVE_LIMIT 20

class QwtPlotGrid;

using namespace std;

class Plot : public QwtPlot
{
	Q_OBJECT

public:
    Plot(QPointer<QWidget> parent = NULL, int _type = 0);

	int addCurve(QString, int, double);						//dodanie krzywej do wykresu

	enum { ROC_CURVE = 0, PR_CURVE = 1 };

protected:
    virtual void resizeEvent(QResizeEvent*);
	bool eventFilter(QObject*, QEvent*);

public slots:	
	void showItem(QwtPlotItem*, bool);
	void changeName(int, QString);
	void changeColor(int, QColor);
	void getColAuc(int);
	void deleteCurve(int);
	void leaveOneUnhided(int);
	void clearAll();
	void modifyBackgroundColor(QColor);
	void changePlotName(QString);
	void changePlotLabels(QString, QString);
	void changeGridState(int);
	
signals:
	void coordinatesAssembled(QPoint);
	void curveAdded(QString, QColor, double);
	void curveAdd();
	void resendColorAuc(QColor, double);

private:
	QColor generateColor();
	QString generateName();

	int type;						//typ krzywej (ROC, PR)
	int curve_counter;
	vector<QSharedPointer<Curve>> curves_;
	vector<QSharedPointer<ProxyFile>> proxies_;

	QPointer<QwtLegend> legend;
	QwtPlotGrid* grid;

	const int* QtColors;
	int itColor;
};

