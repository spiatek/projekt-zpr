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
 * This header file contains Plot class definition.
 * Plot class derives from QwtPlot class.
 */

#pragma once

#include <vector>
#include <qpointer.h>
#include <QSharedPointer>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include "../headers/Curve.h"
#include "../headers/fileProxy.h"

class QwtPlotGrid;

using namespace std;

class Plot : public QwtPlot
{
	Q_OBJECT

public:
    Plot(QPointer<QWidget> parent = NULL, int _type = 0);

	int addCurve(QString, int);

	enum { ROC_CURVE = 0, PR_CURVE = 1 };
	enum { CURVE_LIMIT = 20 };

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

	int type;
	int curve_counter;
	vector<QSharedPointer<Curve>> curves_;
	vector<QSharedPointer<ProxyFile>> proxies_;

	QPointer<QwtLegend> legend;
	QwtPlotGrid* grid;

	const int* QtColors;
	int itColor;
};
