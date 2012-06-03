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
 *
 */


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

	int addCurve(QString, int);							//add curve to the plot
	int modifyCurveColor(int, QColor);					//change curve color

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
	void deleteCurve(int);								//remove curve
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

	int type;											//curve type (ROC, PR)
	int curve_counter;
	std::vector<Curve*> curves_;
	std::vector<ProxyFile*> proxies_;
	QwtLegend *legend;
	QwtPlotGrid *grid;

	const int* QtColors;
	int itColor;
};

