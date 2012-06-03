/**
 * @file
 * @author  Szymon PiÄ…tek, Mateusz Matuszewski
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

#include "../headers/Plot.h"
#include "../headers/FunctionData.h"
#include "../headers/Curve.h"

#include <iostream>
#include <qstring.h>
#include <qtextcodec.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_item.h>
#include <qwt_legend_item.h>
#include <qevent.h>
#include <qmessagebox.h>

using namespace std;

/**
<<<<<<< HEAD
* Grid class inherits from QwtPlotGrid and specify grid properties for a plot.
*/
class Grid: public QwtPlotGrid
{
public:
	///Grid class constructor
    Grid()
    {
=======
 * Grid class
 */
class Grid: public QwtPlotGrid{
public:
    Grid(){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
        enableXMin(true);
		enableYMin(true);
        setMajPen(QPen(Qt::white, 0, Qt::DotLine));
        setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    }

<<<<<<< HEAD
	///method which specify grid scale for both X and Y axis
    virtual void updateScaleDiv(const QwtScaleDiv &xMap, const QwtScaleDiv &yMap)
    {
=======
    virtual void updateScaleDiv(const QwtScaleDiv &xMap,const QwtScaleDiv &yMap){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
        QList<double> ticksX[QwtScaleDiv::NTickTypes];
        ticksX[QwtScaleDiv::MajorTick] = xMap.ticks(QwtScaleDiv::MediumTick);
        ticksX[QwtScaleDiv::MinorTick] = xMap.ticks(QwtScaleDiv::MinorTick);

		QList<double> ticksY[QwtScaleDiv::NTickTypes];
        ticksY[QwtScaleDiv::MajorTick] = yMap.ticks(QwtScaleDiv::MediumTick);
        ticksY[QwtScaleDiv::MinorTick] = yMap.ticks(QwtScaleDiv::MinorTick);

		QwtPlotGrid::updateScaleDiv(
            QwtScaleDiv(xMap.lowerBound(), xMap.upperBound(), ticksX),
            QwtScaleDiv(yMap.lowerBound(), yMap.upperBound(), ticksY) );
    }
};

/**
<<<<<<< HEAD
* Zoomer class inherits from QwtPlotZoomer and specify zoomer properties for a plot.
*/
class Zoomer: public QwtPlotZoomer
{
public:
	///Zoomer class constructor
    Zoomer(QPointer<QwtPlotCanvas> canvas):
        QwtPlotZoomer(canvas)
    {
        setTrackerMode(AlwaysOn);
    }

	///text tracker for Zoomer class
    virtual QwtText trackerTextF(const QPointF &pos) const
    {
=======
 * Zoomer class
 */
class MyZoomer: public QwtPlotZoomer{
public:
    MyZoomer(QwtPlotCanvas *canvas): QwtPlotZoomer(canvas){
        setTrackerMode(AlwaysOn);
    }

    virtual QwtText trackerTextF(const QPointF &pos) const {
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
        QColor bg(Qt::white);
        bg.setAlpha(200);

        QwtText text = QwtPlotZoomer::trackerTextF(pos);
        text.setBackgroundBrush(QBrush(bg));
        return text;
    }
};

<<<<<<< HEAD
/**
* Plot class constructor
* @param parent QPointer to the parent QWidget
* @param _type Plot type 
*/
Plot::Plot(QPointer<QWidget> parent, int _type):
    QwtPlot( parent ), type(_type)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));
	setObjectName("Porównanie krzywych");
=======
Plot::Plot(QWidget *parent, int _type): QwtPlot( parent ), type(_type){
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));		//tu trzeba poprawiÃ¦ dla innych systemÃ³w
	setObjectName("PorÃ³wnanie krzywych");
	if(type == 0)
		setTitle("PorÃ³wnanie krzywych ROC");
	else
		setTitle("PorÃ³wnanie krzywych PR");
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb

	///Getting information about plot type (ROC, PR)
	try {
		if(type == ROC_CURVE)
			setTitle("Porównanie krzywych ROC");
		else if(type == PR_CURVE)
			setTitle("Porównanie krzywych PR");
		else {
			QString w = QString("Nieznany rodzaj krzywej");
			throw w;
		}
	}
	catch(QString& w) {
		QMessageBox::about(this, tr("Nieobs³ugiwany typ wykresu"), w);
	}

	///Initialize table containing color values
	const int qtc[] = { 3, 2, 7, 13, 8, 14, 9, 15, 10, 16, 11, 17, 12, 18, 5, 4, 6, 19, 0, 1 };
	itColor = 0;
	QtColors = qtc;

	///Set background properties
    setAutoFillBackground(true);
    setPalette(QPalette(QColor(185, 213, 248)));

	///Insert legend
	legend = QPointer<QwtLegend> (new QwtLegend);
    legend->setItemMode(QwtLegend::CheckableItem);
    insertLegend(legend, QwtPlot::RightLegend);

	///Auto replot after legend modification
    connect(this, SIGNAL(legendChecked(QPointer<QwtPlotItem>, bool)), SLOT(showItem(QPointer<QwtPlotItem>, bool)));
    setAutoReplot(true);

    ///Set axis name 
    try {
		if(type == ROC_CURVE) {
			setAxisTitle(xBottom, "False Positive Rate" );
			setAxisTitle(yLeft, "True Positive Rate");
		}
		else if(type == PR_CURVE) {
			setAxisTitle(xBottom, "Recall" );
			setAxisTitle(yLeft, "Precision");
		}
		else {
			QString w = QString("Nieznany rodzaj krzywej");
			throw w;
		}
	}
	catch(QString& w) {
		QMessageBox::about(this, tr("Nieobs³ugiwany typ wykresu"), w);
	}

	///Set axis ranges
	setAxisScale(xBottom, 0.0, 1.0);
    setAxisScale(yLeft, 0.0, 1.0);

	///Set grid
	grid = new Grid;
    grid->attach(this);

	///Set zoomer properties
	///LeftButton for the zooming
    ///MidButton for the panning
    ///RightButton: zoom out by 1
    ///Ctrl+RighButton: zoom out to full size
    QPointer<QwtPlotZoomer> zoomer = new Zoomer(canvas());
	zoomer->setRubberBandPen(QColor(Qt::black));
    zoomer->setTrackerPen(QColor(Qt::black));
    zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::RightButton, Qt::ControlModifier);
    zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::RightButton );

	///Set panner
	QPointer<QwtPlotPanner> panner = new QwtPlotPanner(canvas());
    panner->setMouseButton(Qt::MidButton);

	///Set plot canvas
    canvas()->setLineWidth(1);
    canvas()->setFrameStyle(QFrame::Box | QFrame::Plain);
    canvas()->setBorderRadius(15);

	///Set canvas color
    QPalette canvasPalette(Qt::white);
    canvasPalette.setColor(QPalette::Foreground, QColor(133, 190, 232));
    canvas()->setPalette(canvasPalette);

	///Install event filter
	QWidget::setMouseTracking(true);
	installEventFilter(this);
	
	///Initialize curve counter
	curve_counter = 0;
}

<<<<<<< HEAD
/**
* Plot class addCurve method is called while adding a curve to the plot
* It emits curveAdded signal with color, AUC and color as parameters, while curve is added
* @param fileName n of a file containing curve points
* @param _type type of a curve (ROC, PR)
* @param _auc area under the curve
*/
int Plot::addCurve(QString fileName, int _type, double _auc)
{	
	QSharedPointer<ProxyFile> _proxy;
=======
int Plot::addCurve(QString fileName, int _type){	
	double _auc=0.0;

	ProxyFile *_proxy;
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	QColor color;
	QString name;
	QSharedPointer<Curve> curve;

	///check number of attached curves
	int atchn = 0;
	for(int i=0; i<curves_.size(); i++) 
	{
		if ((curves_[i])->isAttached()) {
			atchn++;
		}
	}
	//qDebug()<<"attached1:"<<atchn;

	///check if requested curve already exists
	bool exists=false;
<<<<<<< HEAD
	for (int i=0; i<proxies_.size(); i++)
	{
		if ((proxies_[i])->real_file_path==fileName) {
			//qDebug()<<"already exists";
			curve=(curves_[i]);
			
			///check if requested curve is already attached to a plot
			if (curve->isAttached()) {
				//qDebug()<<"already attached";
				QMessageBox::about(this, tr("Niepowodzenie wczytania krzywej"), tr("Nie mo¿na drugi raz wczytaæ tej samej krzywej"));
=======
	for (int i=0; i<proxies_.size(); i++){
		if ((proxies_[i])->real_file_path==fileName){
			curve=(curves_[i]);
			if (curve->attached)
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
				return 0;
			exists=true;
			_proxy=proxies_[i];
			(curves_[i])->attach(this);
			color = (curves_[i])->getColor();
			_auc = (curves_[i])->getAUC();
			name = ((curves_[i])->getTitle()).text();
			curve->setAttached(true);
		}
	}
<<<<<<< HEAD

	///load new curve
	if(exists==false) {

		//qDebug()<<"loading";

		///generate curve properties
		name = generateName();
		curve = QSharedPointer<Curve> (new Curve(name));
		curve->setAttached(true);
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);

		///generate color
		color = generateColor();
		curve->setPen(QPen(color));
		curve->attach(this);
	
		//qDebug()<<"DOESNT EXIST";

		///register new proxy
		_proxy = QSharedPointer<ProxyFile> (new ProxyFile(fileName));

		///load data
		QVector<QPointF>* dPoints;
		dPoints=_proxy->getData();

		curve->setData(new FunctionData(dPoints));

		///initialize curve
		curve->init(_auc, color);

		curves_.push_back(curve);
		proxies_.push_back(_proxy);
	}

	curve->setIndex((itemList(QwtPlotItem::Rtti_PlotCurve)).size() - 1);
	//qDebug()<<"curve position:"<<curve->getIndex();
	
	curve_counter++;
	//qDebug()<<"QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve)";
	
	///add curve to plot legend
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for(int i = 0; i < items.size(); i++)
    {
		if(i == items.size() - 1) {
=======
	if (exists==false){
		name = generateName();
		curve = new Curve(name);
		curve->attached=true;
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);

		color = generateColor();
		curve->setPen(QPen(color));
		curve->attach(this);
		
		_proxy = new ProxyFile(fileName);
	
		QVector<QPointF>* dPoints;
		dPoints=_proxy->getData();


		if (dPoints->size()<2){
			throw 1003;
		}
		else{
			for (int i=0; i<dPoints->size()-1; i++){
				_auc+=1.0/2.0*( (*dPoints)[i].y()+(*dPoints)[i+1].y() ) * ( (*dPoints)[i+1].x()-(*dPoints)[i].x() );
			}
		}
		curve->setData(new FunctionData(dPoints));	
		curve->init(_type, _auc, color);
		curves_.push_back(curve);
		proxies_.push_back(_proxy);
	
	}
	curve->position=(itemList(QwtPlotItem::Rtti_PlotCurve)).size()-1;
	curve_counter++;
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for ( int i = 0; i < items.size(); i++ ){
		if ( i == items.size() - 1 ){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
			QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
            if(legendItem) {
				legendItem->setChecked(true);
			}
            items[i]->setVisible(true);
        }
    }
<<<<<<< HEAD

	//qDebug()<<"emit";
	emit curveAdded(name, color, _auc);
	
	//qDebug()<<"emited cc:"<<curve_counter;
	
	///check number of attached curves
	atchn=0;
	for (int i=0; i<curves_.size(); i++){
		if ((curves_[i])->isAttached()){
			atchn++;
		}
	}
	//qDebug()<<"attached2:"<<atchn;
	
	return 0;
}

/*
int Plot::modifyCurveColor(int _id, QColor color)
{
	vector<QSharedPointer<Curve>>::iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) 
	{
		if((*it)->getIndex() == _id) {
=======
	emit curveAdded(name, color, _auc);
	return 0;
}

int Plot::modifyCurveColor(int _id, QColor color){
	vector<Curve*>::iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) {
		if((*it)->getId() == _id)
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
			(*it)->setPen(color);
	}
	return 0;
}*/

<<<<<<< HEAD
/**
* Plot class generateColor method is used to generate color of a curve while adding to a plot.
* It uses QtColors table values, which are mapped to QColors by setRgb function
*/
QColor Plot::generateColor()
{
=======
QColor Plot::generateColor(){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	QColor color;
	color.setRgb(QtColors[itColor]);
	itColor++;
	if(itColor == sizeof(QtColors)) {
		itColor = 0;
	}
	return color;
}

<<<<<<< HEAD
/**
* Plot class generateName method is used to generate name of a curve.
*/
QString Plot::generateName()
{
=======
QString Plot::generateName(){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	int curveNr = curves_.size() + 1;
	QString name = QString("krzywa_%1").arg(curveNr);
	return name;
}

<<<<<<< HEAD
/**
* Plot class resizeEvent method is used to capture QResizeEvent
* @param event Event which is activated while resizing a plot window
*/
void Plot::resizeEvent(QResizeEvent* event)
{
    QwtPlot::resizeEvent(event);
}

/**
* Plot class eventFilter method is used to capture MouseMove events
* It emits coordinatesAssembles signal with current mouse position specified
* @param obj
* @param event Event which is activated while moving a mouse
*/
bool Plot::eventFilter(QObject *obj, QEvent *event)
{
	if(event->type() == QEvent::MouseMove)
	{
		QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
		emit coordinatesAssembled(mouseEvent->pos());
	}
	return false;
}

/**
* Plot class showItem slot is to change visibility of a curve after pushing a legend button
* @param item Pointer to a current curve
* @param _state Boolean value defining desirable visibility state
*/
void Plot::showItem(QwtPlotItem* item, bool _state)
{
	item->setVisible(_state);
}

/**
* Plot class changeName slot is called by PlotWindow if curve name was modified in panel
* @param _pos Curve identifier
* @param _newName New curve name
*/
void Plot::changeName(int _pos, QString _newName)
{
=======
void Plot::insertMarkers(){
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

void Plot::updateGradient(){
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

void Plot::resizeEvent( QResizeEvent *event ){
    QwtPlot::resizeEvent( event );
#ifdef Q_WS_X11
    //updateGradient();
#endif
}

void Plot::refreshEvent(){
	replot();
}

bool Plot::eventFilter(QObject *obj, QEvent *event){
	if(event->type() == QEvent::MouseMove){
	    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
		emit coordinatesAssembled(mouseEvent->pos());
	}
	return false;
}

void Plot::showItem(QwtPlotItem *item, bool on){
	item->setVisible(on);
}

void Plot::cAdded(void){}

void Plot::changeName(int _pos, QString _newName){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	items[_pos]->setTitle(_newName);
	legend->repaint();
}

<<<<<<< HEAD
/**
* Plot class changeColor slot is called by PlotWindow if curve color was modified in panel
* @param _id Curve identifier
* @param _newColor New curve color
*/
void Plot::changeColor(int _id, QColor _newColor)
{
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	vector<QSharedPointer<Curve>>::const_iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) 
	{	
		if((*it)->getIndex() == _id) {
=======
void Plot::changeColor(QString _name, QColor _newColor){
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	vector<Curve*>::const_iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) {	
		if((*it)->title() == _name)
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
			(*it)->setPen(_newColor);
	}
	legend->repaint();
}

<<<<<<< HEAD
/**
* Plot class getColAuc slot is called by PlotWindow to display color and AUC info in panel.
* It emits resendColorAuc signal with color and AUC as parameters
* @param _id Curve identifier
*/
void Plot::getColAuc(int _id)
{
=======
void Plot::getColAuc(QString _name){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	QColor color;
	double auc=-1.0;
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
<<<<<<< HEAD
	vector<QSharedPointer<Curve>>::const_iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) 
	{	
		if((*it)->getIndex() == _id) {
=======
	vector<Curve*>::const_iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) {	
		if((*it)->title() == _name) {
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
			color = (*it)->getColor();
			auc = (*it)->getAUC();
		}
	}
	emit resendColorAuc(color, auc);
}

<<<<<<< HEAD
/**
* Plot class deleteCurve slot is called by PlotWindow to delete curve with specified id.
* @param _id Curve identifier
*/
void Plot::deleteCurve(int _id)
{
	//qDebug()<<"DETACH curve id:"<<_id;
	
	///detaching curve from plot
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	//qDebug()<<items.size()<<" count pre:"<<curve_counter<<" "<<curves_.size()<<"  "<<proxies_.size();
=======
//usuniÃªcie krzywej o danym id
void Plot::deleteCurve(int _id){	
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	items[_id]->detach();
	legend->repaint();
	curve_counter--;
	replot();	
<<<<<<< HEAD
	//qDebug()<<"curve counter:"<<curve_counter;
	
	int atchn=0, index;
	for (int i=0; i<curves_.size(); i++){
		index = (curves_[i])->getIndex();
		if (index == _id){
			curves_[i]->setAttached(false);
		}
		if (index > _id){
			curves_[i]->setIndex(index - 1);
		}
	}
	for (int i=0; i<curves_.size(); i++){
		if ((curves_[i])->isAttached()){
			atchn++;
		}
	}
	
	//qDebug()<<"DELETE number of attached:"<<atchn;
}

/**
* Plot class leaveOneUnhided slot is called by PlotWindow when button in panel was activated
* It sets unvisible all curves except of the one with given id
* @param _pos Curve identifier
*/
void Plot::leaveOneUnhided(int _pos)
{
=======
	
	for (int i=0; i<curves_.size(); i++){
		if ((curves_[i])->position==_id)
			curves_[i]->attached=false;
		if (curves_[i]->position>_id)
			curves_[i]->position--;
	}
}

void Plot::leaveOneUnhided(int _pos){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for(int i = 0; i < items.size(); i++){
		QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
		if(i == _pos){
            if(legendItem)
                legendItem->setChecked(true);
            items[i]->setVisible(true);
        }
		else {
			if(legendItem)
                legendItem->setChecked(false);
			items[i]->setVisible(false);
		}
    }
}

<<<<<<< HEAD
/**
* Plot class clearAll slot is called by PlotWindow when button in panel was activated
* It detaches all curves from a plot
*/
void Plot::clearAll()
{
=======
void Plot::clearAll(){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for(int i = 0; i < items.size(); i++){
		QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
		if(legendItem)
			legendItem->setChecked(false);
<<<<<<< HEAD
		}
		items[i]->setVisible(false);
		curves_[i]->setAttached(false);
=======
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
		items[i]->detach();
	}
	legend->repaint();
	replot();
}

<<<<<<< HEAD
/**
* Plot class modifyBackgroundColor slot is called by PlotWindow when background color was set in panel
* @param _color New bacground color
*/
void Plot::modifyBackgroundColor(QColor _color)
{
=======
void Plot::modifyBackgroundColor(QColor _color){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	setPalette(QPalette(_color));
	replot();
}

<<<<<<< HEAD
/**
* Plot class changePlotName slot is called by PlotWindow when plot name was modified in panel
* @param _name New plot name
*/
void Plot::changePlotName(QString _name)
{
=======
void Plot::changePlotName(QString _name){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	setTitle(_name);
	replot();
}

<<<<<<< HEAD
/**
* Plot class getColAuc slot is called by PlotWindow when plot labels were mofified in panel
* @param _labelX New X label
* @param _labelY New Y label
*/
void Plot::changePlotLabels(QString _labelX, QString _labelY)
{
=======
void Plot::changePlotLabels(QString _labelX, QString _labelY){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	setAxisTitle(xBottom, _labelX);
	setAxisTitle(yLeft, _labelY);
	replot();
}

<<<<<<< HEAD
/**
* Plot class changeGridState slot is called by PlotWindow when grid checkbox value in panel changed
* @param _state Current state of grid checkbox in panel
*/
void Plot::changeGridState(int _state)
{
=======
void Plot::changeGridState(int _state){
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb
	if(_state == 0)
		grid->detach();
	else
		grid->attach(this);
	replot();
}

