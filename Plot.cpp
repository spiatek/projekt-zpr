#include "Plot.h"
#include "FunctionData.h"
#include "Curve.h"

#include <iostream>
#include <qstring.h>
#include <qtextcodec.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qevent.h>

Plot::Plot(QWidget *parent):
    QwtPlot( parent )
{
	const int qtc[] = { 3,2,7,13,8,14,9, 15, 10, 16, 11, 17, 12, 18, 5, 4, 6, 19, 0, 1 };
	itColor = 0;
	QtColors = qtc;

	// panning with the left mouse button
    //(void) new QwtPlotPanner( canvas() );

    // zoom in/out with the wheel
    (void) new QwtPlotMagnifier( canvas() );

    setAutoFillBackground( true );
    setPalette( QPalette( QColor( 185, 213, 248 ) ) );
    //updateGradient();

	//QTextCodec::setCodecForTr (QTextCodec::codecForName ("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));		//tu trzeba poprawić dla innych systemów
    setTitle("Wykres przedstawiający porównanie krzywych");
    insertLegend(new QwtLegend(), QwtPlot::RightLegend);

    // axes 
    setAxisTitle(xBottom, "x" );
    setAxisScale(xBottom, 0.0, 1.0);

    setAxisTitle(yLeft, "y");
    setAxisScale(yLeft, 0.0, 1.0);

    // canvas
    canvas()->setLineWidth( 1 );
    canvas()->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas()->setBorderRadius( 15 );

    QPalette canvasPalette( Qt::white );
    canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
    canvas()->setPalette( canvasPalette );

	QWidget::setMouseTracking(true);
	installEventFilter(this);

    //populate();
}

int Plot::addCurve(QwtSeriesData<QPointF> *_points, int _type, double _auc)
{	
	QwtPlotCurve *qcurve = new QwtPlotCurve(generateName());
	
	qcurve->setLegendAttribute(QwtPlotCurve::LegendShowLine, true);
	qcurve->setRenderHint(QwtPlotItem::RenderAntialiased);
	qcurve->setPen(QPen(generateColor(*qcurve)));
    qcurve->attach(this);

	if(itColor%2 == 0) {
		qcurve->setData(new FunctionData(::sin));
	}
	else {
		qcurve->setData(new FunctionData(::cos));
	}
	
	Curve *curve = new Curve(_type, _auc, qcurve->title());
	curves_.push_back(*curve);

	return 0;
}

QColor Plot::generateColor(QwtPlotCurve& qpc)
{
	QColor color;
	color.setRgb(QtColors[itColor]);
	itColor++;
	if(itColor == sizeof(QtColors)) {
		itColor = 0;
	}
	return color;
}

QString Plot::generateName()
{
	int curveNr = curves_.size() + 1;
	QString name = QString("krzywa_%1").arg(curveNr);
	return name;
}

void Plot::insertMarkers()
{
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
	//zabawy z gradientowym wyświetlaniem kolorów

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

bool Plot::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
	emit coordinatesAssembled(mouseEvent->pos());
  }
  return false;
}
