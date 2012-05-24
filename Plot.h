#pragma once
#include <list>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "Curve.h"

class Plot : public QwtPlot
{
	Q_OBJECT

public:
    Plot(QWidget *parent = NULL);

	int addCurve(QwtSeriesData<QPointF> *, int, double);	//dodanie krzywej do wykresu
	int deleteCurve(int);									//usuniêcie krzywej o danej nazwie
	int hideCurve(int);										//ukrycie krzywej  o danej nazwie z wykresu
	int unhideCurve(int);									//odkrycie ukrytej krzywej o danej nazwie
	int modifyCurveColor(int, QColor);						//zmiana koloru krzywej o danej nazwie

protected:
    virtual void resizeEvent(QResizeEvent*);
	bool eventFilter(QObject *obj, QEvent *event);

public slots:	
	void refreshEvent();

signals:
	void coordinatesAssembled(QPoint);

private:
	QColor generateColor();
	QString generateName();
    void insertMarkers();
    void updateGradient();

	int type;						//typ krzywej (ROC, PR)
	list<Curve*> curves_;

	const int* QtColors;
	int itColor;
};

