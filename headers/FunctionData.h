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

#pragma once
#include <qwt_plot_curve.h>
#include <cmath>

class FunctionData:  public QwtSeriesData<QPointF> {

public:
	FunctionData(QVector<QPointF> *_dataPoints);
    QPointF sample(size_t i) const;
    size_t size() const;
	QRectF boundingRect() const;  

private:
	QVector<QPointF> *dataPoints;

};
