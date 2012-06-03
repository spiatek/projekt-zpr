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


#include "../headers/FunctionData.h"

/**
 * Constructor of FunctionData class
 * @param _dataPoints vector of points to be displayed in the plot
 */
FunctionData::FunctionData(QVector<QPointF> *_dataPoints){
	dataPoints=_dataPoints;
}
     
/**
 * Return i-th smaple from QPointF vector
 * @param _size_t which sample to return
 * @return i-th smaple
 */
QPointF FunctionData::sample(size_t i) const{
	return (*dataPoints)[i];
}
/**
 * Return size of vector of QPointF points
 * @return size of vector of QPointF points
 */
size_t FunctionData::size() const{
	return dataPoints->size();
}

/**
 *
 * @return
 */
QRectF FunctionData::boundingRect() const
{
	return QRectF();
}

