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
 * The ProxyFile class and RealFile class are implementation of Proxy Design
 * Pattern with lazy reading.
 */

#pragma once

#include "../headers/FunctionData.h"
#include <string>
#include "qwt_math.h"
#include <qwt_series_data.h>
#include <QString>
#include <QPointF>

class RealFile{
	private:
		QVector<QPointF> data_points;
		QString path;
		
	public:
		RealFile(QString _path); //constructor
		~RealFile(); //destructor
		QVector<QPointF>* getData();

};

class ProxyFile{
	private:
		RealFile *p_real_file;
	
	public:
		QString real_file_path;
	
		ProxyFile();
		ProxyFile(QString _path);
		~ProxyFile();
		
		ProxyFile* init_path(QString _path);
		QVector<QPointF>* getData();
};

