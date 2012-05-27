#include "..\headers\Curve.h"

#include <string>
#include <qwt_text.h>
#include <qstring.h>
#include <qcolor.h>

using namespace std;

int Curve::id_ = 0;

Curve::Curve(const QwtText &_title) : QwtPlotCurve(_title)
{
}

/*
Curve& Curve::operator= (const Curve &_curve)
{
	QwtPlotCurve& ref_qpc = *this;
	ref_qpc = _curve;
	type_ = _curve.type_;
	auc_ = _curve.auc_;
	isHidden_ = _curve.isHidden_;
	return *this;
}
*/
void Curve::init(int _type, double _auc, QColor _color)
{
	type_ = _type;
	auc_ = _auc;
	color_ = _color;
	isHidden_ = false;
}

int Curve::getId()
{
	return id_;
}

int Curve::getType()
{
	return type_;
}
	
double Curve::getAUC()
{
	return auc_;
}

QColor Curve::getColor()
{
	return color_;
}