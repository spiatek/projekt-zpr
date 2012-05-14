#pragma once

#include <string>
#include <qwt_plot_curve.h>
#include <qwt_text.h>
#include <qstring.h>

class Curve {

public:
	Curve(int _type, double _auc, const QwtText _title) : 
	  title_(_title), type_(_type), auc_(_auc), isHidden_(false) {}

	/*Curve(const QwtPlotCurve& _curve, int _type, double _auc) : 
		curve_(_curve), type_(_type), auc_(_auc), isHidden_(false) {}*/

	int getType();
	double getAUC();

private:
	int type_;					//typ krzywej
	double auc_;				//pole pod krzyw¹
	//QwtPlotCurve curve_;		//krzywa
	bool isHidden_;				//czy ukryta
	QwtText title_;
};	