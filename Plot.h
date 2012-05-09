#pragma once
#include <qwt_plot.h>

class Plot :
	public QwtPlot
{
public:
    Plot(QWidget *parent = NULL);

protected:
    virtual void resizeEvent( QResizeEvent * );

private:
    void populate();
    void updateGradient();
};

