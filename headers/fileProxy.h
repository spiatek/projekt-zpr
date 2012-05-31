#pragma once

#include "../headers/FunctionData.h"
#include <string>
#include "qwt_math.h"
#include <qwt_series_data.h>
#include <QString>
//#include <QVector2D>
#include <QPointF>

class RealFile{//: public QwtPointArrayData{
	private:
		 //QVector<QVector2D> coordinates;
		//FunctionData* data_points;
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
		
		//QString real_file_last_mod;
	
	public:
		QString real_file_path;
	
		ProxyFile();
		ProxyFile(QString _path);
		~ProxyFile();
		
		ProxyFile* init_path(QString _path);
		QVector<QPointF>* getData();
};
