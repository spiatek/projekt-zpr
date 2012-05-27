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
	//Curve& operator= (const Curve&);

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

private:

	static int id_;
	int type_;					//typ krzywej
	double auc_;				//pole pod krzyw¹
	bool isHidden_;				//czy ukryta
	QColor color_;

};