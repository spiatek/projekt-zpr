#pragma once
#include <list>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "../headers/Curve.h"
#include "../headers/fileProxy.h"

#define CURVE_LIMIT 20

class QwtPlotGrid;

class Plot : public QwtPlot
{
	Q_OBJECT

public:
    Plot(QWidget *parent = NULL, int _type = 0);

	int addCurve(QString, int, double);	//dodanie krzywej do wykresu
	int modifyCurveColor(int, QColor);						//zmiana koloru krzywej o danej nazwie

protected:
    virtual void resizeEvent(QResizeEvent*);
	bool eventFilter(QObject *obj, QEvent *event);

public slots:	
	void refreshEvent();
	void cAdded();
	void showItem(QwtPlotItem*, bool);
	void changeName(int, QString);
	void changeColor(QString, QColor);
	void getColAuc(QString);
	void deleteCurve(int);									//usuniÍcie krzywej o danej nazwie
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
    void insertMarkers();
    void updateGradient();

	int type;						//typ krzywej (ROC, PR)
	int curve_counter;
	std::vector<Curve*> curves_;
	std::vector<ProxyFile*> proxies_;
	QwtLegend *legend;
	QwtPlotGrid *grid;

	const int* QtColors;
	int itColor;
};

