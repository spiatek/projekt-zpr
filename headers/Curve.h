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
 * class describing a curve, derived from QwtPlotCurve
 */


#pragma once

#include <qwt_plot_curve.h>
#include <QColor>
#include <iostream>

class QwtPlotCurve;
class QColor;

class Curve : QwtPlotCurve {

public:
	Curve() { ++id_; }
	Curve(int _type, double _auc) : type_(_type), auc_(_auc), isHidden_(false) { ++id_; }
	Curve(const QwtText&);

	using QwtPlotCurve::setLegendAttribute;
	using QwtPlotCurve::setRenderHint;
	using QwtPlotCurve::setPen;
    using QwtPlotCurve::attach;
	using QwtPlotCurve::setData;
	using QwtPlotCurve::hide;
	using QwtPlotCurve::setVisible;
	using QwtPlotCurve::title;
	using QwtPlotCurve::setTitle;

	void init(int, double, QColor);
	int getId();
	int getType();
	double getAUC();
	QColor getColor();
	QwtText getTitle();
	bool attached;				//is attached to plot
	int position;				//position in menu

private:

	static int id_;				//curve id
	int type_;					//curve type
	double auc_;				//area under the curve
	bool isHidden_;				//hidden
	QColor color_;				//plot color

};

