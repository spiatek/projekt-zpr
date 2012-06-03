#pragma once
#include <qwt_plot_curve.h>
#include <cmath>

class FunctionData:  public QwtSeriesData<QPointF> //
{
public:
	QVector<QPointF> *dataPoints;
	



//TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	FunctionData(QVector<QPointF> *_dataPoints)
    {
    	dataPoints=_dataPoints;
    }
    
   // const SignalData &values() const;
    
   // SignalData &values();
    
    virtual QPointF sample(size_t i) const{
    	return (*dataPoints)[i];
    }
    
    virtual size_t size() const
    {
    	return dataPoints->size();
    }

    virtual QRectF boundingRect() const{
		return QRectF();
    }
    
    





////////////////////////
/*


    FunctionData(double(*y)(double)):
        QwtSyntheticPointData(100),
        d_y(y)
    {
    }



//CALCULATE Y VALUE FOR A X VALUE
    virtual double y(double x) const
    {
    	if (!dataPoints){
    		qDebug()<<"!dp";
    	    return 0.0;
    	}
    	else if (x<0.0){
    		qDebug()<<"x<0";
    		return 0.0;
    	}
    	else if (x>1.0){
    		qDebug()<<"x>1";
    		return 1.0;
    	}
    	else{
    	//qDebug()<<"dpontssize:"<< dataPoints->size();
    		QPointF pf;
    		double closest=10.0,closesty;
    		for (int i = 0; i < dataPoints->size(); ++i) {
    			pf = (*dataPoints)[i];
    			double pt = pf.x();	
    			double d1 = closest;
    			double d2 = fabs(pt-x);
    			//qDebug()<<"  i:"<<i<<"  x:"<<x<<"  pt:"<<pt<<"  d1:"<<d1<<"  d2"<<d2<<"   clos"<<closest<<"   cly"<<closesty;
     			if ( d2 < closest ){	
     				closest=d2;
     				closesty=pf.y();
     			}
     			//qDebug()<<"  i:"<<i<<"  x:"<<x<<"  pt:"<<pt<<"  d1:"<<d1<<"  d2"<<d2<<"   clos"<<closest<<"   cly"<<closesty;
       		}
       		//qDebug()<<"  x:"<<x<<"  closest:"<<closest<<"  y:"<<closesty;
         	return closesty;
    }
}

private:
    double(*d_y)(double);
    */
};
