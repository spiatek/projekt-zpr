#include "..\headers\Curve.h"

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
void Curve::init(int _type, double _auc)
{
	type_ = _type;
	auc_ = _auc;
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