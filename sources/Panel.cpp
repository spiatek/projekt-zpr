#include "../headers/Panel.h"
#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qwt_plot_curve.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qtextcodec.h>

/**
* Panel class constructor
* @param parent QPointer to the parent QWidget
* @param _type Plot type 
*/
Panel::Panel(QPointer<QWidget> parent, int _type):
    QTabWidget(parent)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));	
    setTabPosition(QTabWidget::North);

	///set panel type (ROC, PR)
	type = _type;

	///add tabs for curve and plot properties
	addTab(createCurveTab(this), "Curve Properties");
	addTab(createPlotTab(this), "Plot Properties");
}

/**
* Panel class createCurveTab method is used to create tab for curve properties
* It creates widgets, sets tab layout and connect Panel classes signals to the slots
* @param parent QPointer to the parent QWidget
*/
QPointer<QWidget> Panel::createCurveTab(QPointer<QWidget> parent)
{
	///create curve tab
	curvesTab = new QWidget(parent);

	///create curve tab layout
	curvesLayout = new QGridLayout(curvesTab);

	int row = 0;

	///create combo box for curves
	curvesCombo = new QComboBox(parent);
    curvesLayout->addWidget(new QLabel("Choose curve:", parent), row++, 0 );
    curvesLayout->addWidget(curvesCombo, row++, 0);

	///create line edit and button for curve name change
	QPointer<QLabel> label1 = new QLabel("Title:", curvesTab);
	lineEdit = new QLineEdit("", curvesTab);
	curvesLayout->addWidget(label1, row++, 0);
	curvesLayout->addWidget(lineEdit, row++, 0);
	nameButton = new QPushButton(tr("Change title"));
	curvesLayout->addWidget(nameButton, row++, 0);

	///create labels and button for curve color change
	QPointer<QLabel> label2 = new QLabel("Color:", curvesTab);
	curvesLayout->addWidget(label2, row++, 0);
	colorLabel = new QLabel();
	curvesLayout->addWidget(colorLabel, row++, 0);
	colorButton = new QPushButton(tr("Change color"));
	curvesLayout->addWidget(colorButton, row++, 0);

	///create labels for curve AUC display
	QPointer<QLabel> label3 = new QLabel("AUC:", curvesTab);
	curvesLayout->addWidget(label3, row++, 0);
	aucLabel = new QLabel();
	curvesLayout->addWidget(aucLabel, row++, 0);

	///create delete, hideAll and clear buttons
	deleteButton = new QPushButton(tr("Delete curve"));
	hideAllButton = new QPushButton(tr("Hide all except of this"));
	clearButton = new QPushButton(tr("Clear all"));
	curvesLayout->addWidget(deleteButton, row++, 0);
	curvesLayout->addWidget(hideAllButton, row++, 0);
	curvesLayout->addWidget(clearButton, row++, 0);

	curvesLayout->setColumnStretch(1, 10);
    curvesLayout->setRowStretch(row, 20);

	///connect signals to the slots
	connect(curvesCombo,	SIGNAL(currentIndexChanged(const QString&)),	SLOT(edited(const QString&)));
	connect(nameButton,		SIGNAL(clicked()),				this,			SLOT(changeName()));
	connect(colorButton,	SIGNAL(clicked()),				this,			SLOT(setColor()));
	connect(deleteButton,	SIGNAL(clicked()),				this,			SLOT(deleteCurve()));
	connect(hideAllButton,	SIGNAL(clicked()),				this,			SLOT(hideAll()));
	connect(clearButton,	SIGNAL(clicked()),				this,			SLOT(clearAll()));

	curvesTab->repaint();

	return curvesTab;
}

/**
* Panel class createPlotTab method is used to create tab for plot properties
* It creates widgets, sets tab layout and connect Panel classes signals to the slots
* @param parent QPointer to the parent QWidget
*/
QPointer<QWidget> Panel::createPlotTab(QPointer<QWidget> parent)
{
	///create tab and layout for plot properties
	plotTab = new QWidget(parent);
	plotLayout = new QGridLayout(plotTab);

	int row = 0;

	///create line edit and button for plot name change
	QPointer<QLabel> label1 = new QLabel("Title:", plotTab);
	plotName = new QLineEdit("", plotTab);
	plotLayout->addWidget(label1, row++, 0);
	plotLayout->addWidget(plotName, row++, 0);
	plotNameButton = new QPushButton(tr("Change title"));
	plotLayout->addWidget(plotNameButton, row++, 0);

	///create labels and button for plot color change
	QPointer<QLabel> label2 = new QLabel("Background color:", plotTab);
	plotLayout->addWidget(label2, row++, 0);
	plotBcgColorLabel = new QLabel();
	plotLayout->addWidget(plotBcgColorLabel, row++, 0);
	plotBcgColorButton = new QPushButton(tr("Change background color"));
	plotLayout->addWidget(plotBcgColorButton, row++, 0);

	///create line edits and button for plot label change
	QPointer<QLabel> label3 = new QLabel("GridX:", plotTab);
	QPointer<QLabel> label4 = new QLabel("GridY:", plotTab);
	labelX = new QLineEdit("", plotTab);
	labelY = new QLineEdit("", plotTab);
	plotLayout->addWidget(label3, row++, 0);
	plotLayout->addWidget(labelX, row++, 0);
	plotLayout->addWidget(label4, row++, 0);
	plotLayout->addWidget(labelY, row++, 0);
	labelButton = new QPushButton(tr("Change axis labels"));
	plotLayout->addWidget(labelButton, row++, 0);

	///create checkbox for grid visibility change
	gridCheckBox = new QCheckBox("Grid", plotTab);
	gridCheckBox->setChecked(true);
	plotLayout->addWidget(gridCheckBox, row++, 0);

	plotLayout->setColumnStretch(1, 10);
    plotLayout->setRowStretch(row, 20);

	///connect signals to the slots
	connect(plotNameButton,		SIGNAL(clicked()),			this,	SLOT(changePlotName()));
	connect(plotBcgColorButton,	SIGNAL(clicked()),			this,	SLOT(setBcgColor()));
	connect(labelButton,		SIGNAL(clicked()),			this,	SLOT(changeLabels()));
	connect(gridCheckBox,		SIGNAL(stateChanged(int)),	this,	SLOT(changeGrid(int)));

	return plotTab;
}

/**
* Panel class addCurve slot is called while adding curve to a plot.
* The curve is also added to a curve panel.
* @param _name Specify a title of the curve which was added
* @param _color Specify a color of the curve which was added
* @param _auc Specify an area under the curve which was added
*/
void Panel::addCurve(QString _name, QColor _color, double _auc)
{
	///add item to the combo box
	curvesCombo->addItem(_name);
	curvesCombo->setCurrentIndex(curvesCombo->count() - 1);
	lineEdit->setText(_name);
	
	///fill color label with a color of the curve which was added
	colorLabel->setPalette(QPalette(_color));
	colorLabel->setAutoFillBackground(true);

	///fill AUC label with a value of an area under the curve which was added
	QString auc = QString("%1").arg(_auc);
	aucLabel->clear();
	aucLabel->setText(auc);

	curvesTab->repaint();
}

/**
* Panel class edited slot is called while switching value of combo box.
* It emits getColorAuc signal due to get an information about color and AUC from Plot
* @param which An index of the chosen option in combo box
*/
void Panel::edited(const QString& which)
{
	lineEdit->setText(which);
	int index = curvesCombo->currentIndex();
	emit getColorAuc(index);
}

/**
* Panel class readColorAuc slot is called while information about color and AUC
* of the specified curve are available
* @param _color A color of the curve
* @param _auc An area under the curve
*/
void Panel::readColorAuc(QColor _color, double _auc)
{
	///fill color label with a color of the curve
	colorLabel->setPalette(QPalette(_color));
	colorLabel->setAutoFillBackground(true);

	///fill AUC label with a value of an area under the curve
	QString auc = QString("%1").arg(_auc);
	aucLabel->clear();
	aucLabel->setText(auc);

	curvesTab->repaint();
}

/**
* Panel class changeName slot is called while nameButton was checked.
* It emits nameChange signal which is used to upgrade legend info
*/
void Panel::changeName()
{
	///check if curve is specified
	if(curvesCombo->count() == 0) {
		return;
	}

	///get a text from lineEdit and current combo box index
	int index = curvesCombo->currentIndex();
	QString name = lineEdit->text();
	curvesCombo->setItemText(index, name);
	nameButton->setChecked(false);
	emit nameChange(index, name);
}

/**
* Panel class changePlotName slot is called while plotNameButton was checked.
* It emits plotNameChange signal which is used to upgrade plot title
*/
void Panel::changePlotName()
{
	QString name = plotName->text();
	plotNameButton->setChecked(false);
	emit plotNameChange(name);
}

/**
* Panel class changeLabels slot is called while labelButton was checked.
* It emits labelsChange signal which is used to upgrade axis labels
*/
void Panel::changeLabels()
{
	QString nameX = labelX->text();
	QString nameY = labelY->text();
	labelButton->setChecked(false);
	emit labelsChange(nameX, nameY);

}

/**
* Panel class changeGrid slot is called while grid check box was checked.
* It emits gridChange signal which is used to change visibility of grid lines on a plot
* @param _state Boolean value which represents visibility state of grid lines on a plot
*/
void Panel::changeGrid(int _state)
{
	gridCheckBox->setChecked(false);
	emit gridChange(_state);
}

/**
* Panel class setColor slot is called while color button was checked. It opens a color dialog.
* While clicking a button in this dialog, colorChange signal is emited.
* It is used to change the color of a curve on a plot.
*/
void Panel::setColor()
{
	///check if curve is specified
	if(curvesCombo->count() == 0) {
		return;
	}
	
	///choose color from color dialog
    QColor color;
	color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

	///auto fill color label
    if (color.isValid()) {
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }

	int index = curvesCombo->currentIndex();
	colorButton->setChecked(false);
	emit colorChange(index, color);
 }

/**
* Panel class setBcgColor slot is called while plot color button was checked. It opens a color dialog.
* While clicking a button in this dialog, changeBackgroundColor signal is emited.
* It is used to change the color of a plot background.
*/
void Panel::setBcgColor()
{
	///choose color from color dialog
    QColor color;
	color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);

	///auto fill color background label
	if (color.isValid()) {
        plotBcgColorLabel->setPalette(QPalette(color));
        plotBcgColorLabel->setAutoFillBackground(true);
    }

	plotBcgColorButton->setChecked(false);
	emit changeBackgroundColor(color);
 }

/**
* Panel class deleteCurve slot is called while delete curve button was checked.
* It emits curveDelete signal, which is used to delete curve from plot and legend.
* It emits getColotAuc signal, which is used to get color and AUC of a curve,
* which will be displayed in a panel
*/
void Panel::deleteCurve()
{
	///check if curve is specified
	if(curvesCombo->count() == 0) {
		return;
	}

	///emit a signal for Plot
	int index = curvesCombo->currentIndex();
	curvesCombo->removeItem(index);
	deleteButton->setChecked(false);
	emit curveDelete(index);

	///clear panel if it was an only curve
	if(curvesCombo->count() == 0) {
		lineEdit->clear();
		colorLabel->setPalette(QPalette(Qt::white));
		aucLabel->clear();
		return;
	}
	
	///after delete display first curve from combo box in a panel
	curvesCombo->setCurrentIndex(0);
	QString which = curvesCombo->currentText();
	lineEdit->setText(which);
	emit getColorAuc(index);
}

/**
* Panel class hideAll slot is called while hideAll curve button was checked.
* It emits hideAllExceptOfThis signal, which is used to hide all curves
* from the plot, except of the one, which is checked.
*/
void Panel::hideAll()
{
	int index = curvesCombo->currentIndex();
	hideAllButton->setChecked(false);
	emit hideAllExceptOfThis(index);
}

/**
* Panel class clearAll slot is called while clearAll curve button was checked.
* It emits clearPlot signal, which is used to detach all curves from the plot and legend.
*/
void Panel::clearAll()
{
	clearButton->setChecked(false);
	curvesCombo->clear();
	lineEdit->clear();
	colorLabel->setPalette(QPalette(Qt::white));
	aucLabel->clear();
	emit clearPlot();
}