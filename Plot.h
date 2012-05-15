#pragma once
#include <vector>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "Curve.h"

class Plot : public QwtPlot
{
	Q_OBJECT

public:
    Plot(QWidget *parent = NULL);

	int addCurve(QwtSeriesData<QPointF> *, int, double);	//dodanie krzywej do wykresu
	int deleteCurve(int);									//usuniêcie krzywej o danym id
	int hideCurve(int);										//ukrycie krzywej z wykresu
	int unhideCurve(int);									//odkrycie ukrytej krzywej
	int modifyCurveColor(int, QColor);						//zmiana koloru krzywej

protected:
    virtual void resizeEvent(QResizeEvent*);
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void coordinatesAssembled(QPoint);

private:
	QColor generateColor(QwtPlotCurve&);
	QString generateName();
    void insertMarkers();
    void updateGradient();

	int type;						//typ krzywej (ROC, PR)
	std::vector<Curve> curves_;

	const int* QtColors;
	int itColor;
};

