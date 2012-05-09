#include "Plot.h"
#include "FunctionData.h"

#include <qstring.h>
#include <qtextcodec.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>


Plot::Plot(QWidget *parent):
    QwtPlot( parent )
{
    // panning with the left mouse button
    (void) new QwtPlotPanner( canvas() );

    // zoom in/out with the wheel
    (void) new QwtPlotMagnifier( canvas() );

    setAutoFillBackground( true );
    setPalette( QPalette( QColor( 185, 213, 248 ) ) );
    //updateGradient();

	//QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));		//tu trzeba poprawiæ dla innych systemów
    setTitle("Wykres przedstawiaj¹cy porównanie krzywych");
    insertLegend(new QwtLegend(), QwtPlot::RightLegend);

    // axes 
    setAxisTitle(xBottom, "x" );
    setAxisScale(xBottom, 0.0, 10.0);

    setAxisTitle(yLeft, "y");
    setAxisScale(yLeft, -1.0, 1.0);

    // canvas
    canvas()->setLineWidth( 1 );
    canvas()->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas()->setBorderRadius( 15 );

    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
    canvas()->setPalette( canvasPalette );

    //populate();
}

void Plot::populate()
{
	//przyk³ad dla krzywych sin i cos

    // Insert new curves
    QwtPlotCurve *cSin = new QwtPlotCurve("y = sin(x)");
    cSin->setRenderHint(QwtPlotItem::RenderAntialiased);
    cSin->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
    cSin->setPen(QPen(Qt::red));
    cSin->attach(this);

    QwtPlotCurve *cCos = new QwtPlotCurve("y = cos(x)");
    cCos->setRenderHint(QwtPlotItem::RenderAntialiased);
    cCos->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
    cCos->setPen(QPen(Qt::blue));
    cCos->attach(this);

    // Create sin and cos data
    cSin->setData(new FunctionData(::sin));
    cCos->setData(new FunctionData(::cos));

    // Insert markers
    
    //  ...a horizontal line at y = 0...
    QwtPlotMarker *mY = new QwtPlotMarker();
    mY->setLabel(QString::fromLatin1("y = 0"));
    mY->setLabelAlignment(Qt::AlignRight|Qt::AlignTop);
    mY->setLineStyle(QwtPlotMarker::HLine);
    mY->setYValue(0.0);
    mY->attach(this);

    //  ...a vertical line at x = 2 * pi
    QwtPlotMarker *mX = new QwtPlotMarker();
    mX->setLabel(QString::fromLatin1("x = 2 pi"));
    mX->setLabelAlignment(Qt::AlignLeft | Qt::AlignBottom);
    mX->setLabelOrientation(Qt::Vertical);
    mX->setLineStyle(QwtPlotMarker::VLine);
    mX->setLinePen(QPen(Qt::black, 0, Qt::DashDotLine));
    mX->setXValue(2.0 * M_PI);
    mX->attach(this);
}

void Plot::updateGradient()
{
	//zabawy z gradientowym wyœwietlaniem kolorów

    QPalette pal = palette();

    const QColor buttonColor = pal.color( QPalette::Button );

#ifdef Q_WS_X11
    // Qt 4.7.1: QGradient::StretchToDeviceMode is buggy on X11

    QLinearGradient gradient( rect().topLeft(), rect().bottomLeft() );
    gradient.setColorAt( 0.0, Qt::white );
    gradient.setColorAt( 0.7, buttonColor );
    gradient.setColorAt( 1.0, buttonColor );
#else
    QLinearGradient gradient( 0, 0, 0, 1 );
    gradient.setCoordinateMode( QGradient::StretchToDeviceMode );
    gradient.setColorAt( 0.0, Qt::white );
    gradient.setColorAt( 0.7, buttonColor );
    gradient.setColorAt( 1.0, buttonColor );
#endif

    pal.setBrush( QPalette::Window, gradient );
    setPalette( pal );
}

void Plot::resizeEvent( QResizeEvent *event )
{
    QwtPlot::resizeEvent( event );
#ifdef Q_WS_X11
    //updateGradient();
#endif
}