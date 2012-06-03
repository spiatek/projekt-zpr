/**
* @file Curve.h
* @brief This header file contains Curve class definition.
* Curve class inherits from QwtPlotCurve class.
* It provides an access to some of QwtPlotCurve methods
* and some other features which are not provided by QwtPlotCurve
*
* @author Szymon Pi¹tek
*
* @date 3/6/2012
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

	int getId();
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
