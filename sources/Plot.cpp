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
 * This header file contains Plot class definition.
 * Plot class inherits from QwtPlot class.
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
* Grid class inherits from QwtPlotGrid and specify grid properties for a plot.
*/
class Grid: public QwtPlotGrid
{
public:
	///Grid class constructor
    Grid()
    {
        enableXMin(true);
		enableYMin(true);
        setMajPen(QPen(Qt::white, 0, Qt::DotLine));
        setMinPen(QPen(Qt::gray, 0 , Qt::DotLine));
    }

	///method which specify grid scale for both X and Y axis
    virtual void updateScaleDiv(const QwtScaleDiv &xMap, const QwtScaleDiv &yMap) 
	{
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
        QColor bg(Qt::white);
        bg.setAlpha(200);

        QwtText text = QwtPlotZoomer::trackerTextF(pos);
        text.setBackgroundBrush(QBrush(bg));
        return text;
    }
};

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

/**
* Plot class addCurve method is called while adding a curve to the plot
* It emits curveAdded signal with color, AUC and color as parameters, while curve is added
* @param fileName n of a file containing curve points
* @param _type type of a curve (ROC, PR)
* @param _auc area under the curve
*/
int Plot::addCurve(QString fileName, int _type)
{		
	double _auc = 0.0;

	QSharedPointer<ProxyFile> _proxy;
	QColor color;
	QString name;
	QSharedPointer<Curve> curve;

	///check if requested curve already exists
	bool exists=false;

	for (int i=0; i<proxies_.size(); i++)
	{
		if ((proxies_[i])->real_file_path==fileName) {
			//qDebug()<<"already exists";
			curve=(curves_[i]);
			
			///check if requested curve is already attached to a plot
			if (curve->isAttached()) {
				return 0;
			}

			exists=true;
			_proxy=proxies_[i];
			(curves_[i])->attach(this);
			color = (curves_[i])->getColor();
			_auc = (curves_[i])->getAUC();
			name = ((curves_[i])->getTitle()).text();
			curve->setAttached(true);
		}
	}

	///load new curve
	if(exists==false) {

		///generate curve properties
		name = generateName();
		curve = QSharedPointer<Curve> (new Curve(name));
		curve->setAttached(true);
		curve->setRenderHint(QwtPlotItem::RenderAntialiased);

		///generate color
		color = generateColor();
		curve->setPen(QPen(color));
		curve->attach(this);
		
		///register new proxy
		_proxy = QSharedPointer<ProxyFile> (new ProxyFile(fileName));

		///load data
		QVector<QPointF>* dPoints;
		dPoints=_proxy->getData();

		///count AUC
		if (dPoints->size()<2){
			throw 1003;
		}
		else{
			for (int i=0; i<dPoints->size()-1; i++){
				_auc+=1.0/2.0*( (*dPoints)[i].y()+(*dPoints)[i+1].y() ) * ( (*dPoints)[i+1].x()-(*dPoints)[i].x() );
			}
		}

		curve->setData(new FunctionData(dPoints));

		///initialize curve
		curve->init(_auc, color);

		curves_.push_back(curve);
		proxies_.push_back(_proxy);
	}

	curve->setIndex((itemList(QwtPlotItem::Rtti_PlotCurve)).size() - 1);
	
	curve_counter++;
	
	///add curve to plot legend
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for(int i = 0; i < items.size(); i++)
    {
		if(i == items.size() - 1) {
			QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
            if(legendItem) {
				legendItem->setChecked(true);
			}
            items[i]->setVisible(true);
        }
    }

	emit curveAdded(name, color, _auc);
	return 0;
}

/**
* Plot class generateColor method is used to generate color of a curve while adding to a plot.
* It uses QtColors table values, which are mapped to QColors by setRgb function
*/
QColor Plot::generateColor()
{
	QColor color;
	color.setRgb(QtColors[itColor]);
	itColor++;
	if(itColor == sizeof(QtColors)) {
		itColor = 0;
	}
	return color;
}

/**
* Plot class generateName method is used to generate name of a curve.
*/
QString Plot::generateName(){
	int curveNr = curves_.size() + 1;
	QString name = QString("krzywa_%1").arg(curveNr);
	return name;
}

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
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	items[_pos]->setTitle(_newName);
	legend->repaint();
}

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
			(*it)->setPen(_newColor);
		}
	}
	legend->repaint();
}

/**
* Plot class getColAuc slot is called by PlotWindow to display color and AUC info in panel.
* It emits resendColorAuc signal with color and AUC as parameters
* @param _id Curve identifier
*/
void Plot::getColAuc(int _id)
{
	QColor color;
	double auc=-1.0;
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	vector<QSharedPointer<Curve>>::const_iterator it;
	for(it = curves_.begin(); it != curves_.end(); ++it) 
	{	
		if((*it)->getIndex() == _id) {
			color = (*it)->getColor();
			auc = (*it)->getAUC();
		}
	}
	emit resendColorAuc(color, auc);
}

/**
* Plot class deleteCurve slot is called by PlotWindow to delete curve with specified id.
* @param _id Curve identifier
*/
void Plot::deleteCurve(int _id)
{
	///detaching curve from plot
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	items[_id]->detach();
	legend->repaint();
	curve_counter--;
	replot();	
	
	///upgrade attachement settings in curve properties vector
	int index;
	for (int i=0; i<curves_.size(); i++){
		index = (curves_[i])->getIndex();
		if (index == _id){
			curves_[i]->setAttached(false);
		}
		if (index > _id){
			curves_[i]->setIndex(index - 1);
		}
	}
}

/**
* Plot class leaveOneUnhided slot is called by PlotWindow when button in panel was activated
* It sets unvisible all curves except of the one with given id
* @param _pos Curve identifier
*/
void Plot::leaveOneUnhided(int _id)
{
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for(int i = 0; i < items.size(); i++){
		QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
		if(i == _id){
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

/**
* Plot class clearAll slot is called by PlotWindow when button in panel was activated
* It detaches all curves from a plot
*/
void Plot::clearAll()
{
	QwtPlotItemList items = itemList(QwtPlotItem::Rtti_PlotCurve);
	for(int i = 0; i < items.size(); i++){
		QwtLegendItem *legendItem = (QwtLegendItem *)legend->find(items[i]);
		if(legendItem) {
			legendItem->setChecked(false);
		}
		//items[i]->setVisible(false);
		curves_[i]->setAttached(false);
		items[i]->detach();
	}
	legend->repaint();
	replot();
}

/**
* Plot class modifyBackgroundColor slot is called by PlotWindow when background color was set in panel
* @param _color New bacground color
*/
void Plot::modifyBackgroundColor(QColor _color)
{
	setPalette(QPalette(_color));
	replot();
}

/**
* Plot class changePlotName slot is called by PlotWindow when plot name was modified in panel
* @param _name New plot name
*/
void Plot::changePlotName(QString _name)
{
	setTitle(_name);
	replot();
}

/**
* Plot class changePlotLabels slot is called by PlotWindow when plot labels were mofified in panel
* @param _labelX New X label
* @param _labelY New Y label
*/
void Plot::changePlotLabels(QString _labelX, QString _labelY){
	setAxisTitle(xBottom, _labelX);
	setAxisTitle(yLeft, _labelY);
	replot();
}

/**
* Plot class changeGridState slot is called by PlotWindow when grid checkbox value in panel changed
* @param _state Current state of grid checkbox in panel
*/
void Plot::changeGridState(int _state){
	if(_state == 0)
		grid->detach();
	else
		grid->attach(this);
	replot();
}

