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


#include "../headers/Curve.h"

#include <string>
#include <qwt_text.h>
#include <qstring.h>
#include <qcolor.h>

using namespace std;

int Curve::id_ = 0;

/**
 * Constructor
 * @param _title name of curve
 */
Curve::Curve(const QwtText &_title) : QwtPlotCurve(_title){}

/**
 * Initialize the curve
 * @param _type curve type AUC or PR
 * @param _auc area unde the curveAdd
 * @param _color curve color
 */
void Curve::init(int _type, double _auc, QColor _color){
	type_ = _type;
	auc_ = _auc;
	color_ = _color;
	isHidden_ = false;
}

/**
 * @return curve id
 */
int Curve::getId(){
	return id_;
}

/**
 * @return curve type
 */
int Curve::getType(){
	return type_;
}

/**
 * @return curve AUC
 */
double Curve::getAUC(){
	return auc_;
}

/**
 * @return curve color
 */
QColor Curve::getColor(){
	return color_;
}

/**
 * @return curve title
 */
QwtText Curve::getTitle(){
	return this->title();
}

