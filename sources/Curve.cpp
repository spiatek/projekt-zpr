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
<<<<<<< HEAD
* Curve class constructor calls QwtPlotCurve constructor.
* @param _title Plot title
*/
Curve::Curve(const QwtText &_title) : QwtPlotCurve(_title) { }

/**
* Curve class init method initialize value of an area under the curve and curve color.
* @param _auc area under the curve
* @param _color curve color
*/
void Curve::init(double _auc, QColor _color)
{
	auc_ = _auc;
	color_ = _color;
}

/**
* Curve class setAttached method is used to store information 
* if the curve is attached to the plot.
* @param _attached boolean value which terms if a curve is attached to a plot or not
*/
void Curve::setAttached(bool _attached)
{
	attached_ = _attached;
}

/**
* Curve class setIndex method is used to store information about curve index in plot curve vector
* @param _index index of curve in a plot curve vector
*/
void Curve::setIndex(int _index)
{
	index_ = _index;
}

/**
* Curve class getId method is used to receive an index of a curve in plot curve vector
*/
int Curve::getId()
{
	return id_;
}
	
/**
* Curve class getAUC method is used to receive a value of an area under the curve
*/
double Curve::getAUC()
{
=======
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
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	return auc_;
}

/**
<<<<<<< HEAD
* Curve class getColor method is used to receive a color of the curve
*/
QColor Curve::getColor()
{
=======
 * @return curve color
 */
QColor Curve::getColor(){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	return color_;
}

/**
<<<<<<< HEAD
* Curve class getTitle method is used to receive a title of a curve
*/
QwtText Curve::getTitle()
{
	return this->title();
}

/**
* Curve class isAttached method is used to receive a boolean value
* which terms if a curve is attached to a plot or not
*/
bool Curve::isAttached()
{
	return attached_;
}

/**
* Curve class getIndex method is used to receive an index of a curve in plot curve vector
*/
int Curve::getIndex()
{
	return index_;
}
=======
 * @return curve title
 */
QwtText Curve::getTitle(){
	return this->title();
}

>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
