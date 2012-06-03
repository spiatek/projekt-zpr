/**
 * @file
 * @author  Szymon PiÄ…tek, Mateusz Matuszewski
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
 * This header file contains Curve class definition.
 * Curve class derives from QwtPlotCurve class.
 * It provides an access to some of QwtPlotCurve methods
 * and some other features which are not provided by QwtPlotCurve
 *
 */

#pragma once

#include <qwt_plot_curve.h>
#include <QColor>

class QwtPlotCurve;
class QColor;

class Curve : QwtPlotCurve {

public:
	Curve() { ++id_; }
	Curve(double _auc) : auc_(_auc) { ++id_; }
	Curve(const QwtText&);

	using QwtPlotCurve::setRenderHint;
	using QwtPlotCurve::setPen;
    using QwtPlotCurve::attach;
	using QwtPlotCurve::setData;
	using QwtPlotCurve::setVisible;
	using QwtPlotCurve::title;
	using QwtPlotCurve::setTitle;

	void init(double, QColor);
	void setAttached(bool);
	void setIndex(int);

	double getAUC();
	QColor getColor();
	QwtText getTitle();
	bool isAttached();
	int getIndex();

private:

	static int id_;
	double auc_;				//pole pod krzyw¹
	QColor color_;
	bool attached_;
	int index_;
};

