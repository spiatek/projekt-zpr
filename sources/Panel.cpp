#include "..\headers\Panel.h"
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

Panel::Panel(QWidget *parent):
    QTabWidget(parent)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));	
    setTabPosition(QTabWidget::North);
		
	addTab(createCurveTab(this), "Curve Properties");
	addTab(createPlotTab(this), "Plot Properties");
}

QWidget *Panel::createCurveTab(QWidget *parent)
{
	curvesTab = new QWidget(parent);

	curveCombo = new QComboBox(parent);
	curvesLayout = new QGridLayout(curvesTab);

	int row = 0;

    curvesLayout->addWidget(new QLabel("Choose curve:", parent), row++, 0 );
    curvesLayout->addWidget(curveCombo, row++, 0);

	QLabel *label1 = new QLabel("Title:", curvesTab);
	lineEdit = new QLineEdit("", curvesTab);
	curvesLayout->addWidget(label1, row++, 0);
	curvesLayout->addWidget(lineEdit, row++, 0);
	nameButton = new QPushButton(tr("Change title"));
	curvesLayout->addWidget(nameButton, row++, 0);

	QLabel *label2 = new QLabel("Color:", curvesTab);
	curvesLayout->addWidget(label2, row++, 0);
	colorLabel = new QLabel();
	curvesLayout->addWidget(colorLabel, row++, 0);
	colorButton = new QPushButton(tr("Change color"));
	curvesLayout->addWidget(colorButton, row++, 0);

	QLabel *label3 = new QLabel("AUC:", curvesTab);
	curvesLayout->addWidget(label3, row++, 0);
	aucLabel = new QLabel();
	curvesLayout->addWidget(aucLabel, row++, 0);

	deleteButton = new QPushButton(tr("Delete curve"));
	curvesLayout->addWidget(deleteButton, row++, 0);

	hideAllButton = new QPushButton(tr("Hide all except of this"));
	curvesLayout->addWidget(hideAllButton, row++, 0);

	curvesLayout->setColumnStretch(1, 10);
    curvesLayout->setRowStretch(row, 20);

	connect(curveCombo, SIGNAL(currentIndexChanged(const QString&)), SLOT(edited(const QString&)));
	connect(nameButton, SIGNAL(clicked()), this, SLOT(changeName()));
	connect(colorButton, SIGNAL(clicked()), this, SLOT(setColor()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteCurve()));
	connect(hideAllButton, SIGNAL(clicked()), this, SLOT(hideAll()));

	curvesTab->repaint();

	return curvesTab;
}

QWidget *Panel::createPlotTab(QWidget *parent)
{
	plotTab = new QWidget(parent);
	plotLayout = new QGridLayout(plotTab);

	int row = 0;

	QLabel *label1 = new QLabel("Title:", plotTab);
	plotName = new QLineEdit("", plotTab);
	plotLayout->addWidget(label1, row++, 0);
	plotLayout->addWidget(plotName, row++, 0);
	plotNameButton = new QPushButton(tr("Change title"));
	plotLayout->addWidget(plotNameButton, row++, 0);

	QLabel *label2 = new QLabel("Background color:", plotTab);
	plotLayout->addWidget(label2, row++, 0);
	plotBcgColorLabel = new QLabel();
	plotLayout->addWidget(plotBcgColorLabel, row++, 0);
	plotBcgColorButton = new QPushButton(tr("Change background color"));
	plotLayout->addWidget(plotBcgColorButton, row++, 0);

	QLabel *label3 = new QLabel("GridX:", plotTab);
	QLabel *label4 = new QLabel("GridY:", plotTab);
	labelX = new QLineEdit("", plotTab);
	labelY = new QLineEdit("", plotTab);
	plotLayout->addWidget(label3, row++, 0);
	plotLayout->addWidget(labelX, row++, 0);
	plotLayout->addWidget(label4, row++, 0);
	plotLayout->addWidget(labelY, row++, 0);
	labelButton = new QPushButton(tr("Change axis labels"));
	plotLayout->addWidget(labelButton, row++, 0);

	gridCheckBox = new QCheckBox("Grid", plotTab);
	gridCheckBox->setChecked(true);
	plotLayout->addWidget(gridCheckBox, row++, 0);

	plotLayout->setColumnStretch(1, 10);
    plotLayout->setRowStretch(row, 20);

	connect(plotNameButton, SIGNAL(clicked()), this, SLOT(changePlotName()));
	connect(plotBcgColorButton, SIGNAL(clicked()), this, SLOT(setBcgColor()));
	connect(labelButton, SIGNAL(clicked()), this, SLOT(changeLabels()));
	connect(gridCheckBox, SIGNAL(stateChanged(int)), this, SLOT(changeGrid(int)));

	return plotTab;
}

void Panel::addCurve(QString _name, QColor _color, double _auc)
{
	curveCombo->addItem(_name);
	curveCombo->setCurrentIndex(curveCombo->count() - 1);
	lineEdit->setText(_name);
	
	colorLabel->setPalette(QPalette(_color));
	colorLabel->setAutoFillBackground(true);

	QString auc = QString("%1").arg(_auc);
	aucLabel->clear();
	aucLabel->setText(auc);
	curvesTab->repaint();
}

void Panel::edited(const QString& which)
{
	lineEdit->setText(which);
	emit getColorAuc(which);
}

void Panel::readColorAuc(QColor _color, double _auc)
{
	colorLabel->setPalette(QPalette(_color));
	colorLabel->setAutoFillBackground(true);

	QString auc = QString("%1").arg(_auc);
	aucLabel->clear();
	aucLabel->setText(auc);

	curvesTab->repaint();
}

void Panel::changeName()
{
	if(curveCombo->count() == 0) {
		return;
	}
	int index = curveCombo->currentIndex();
	QString name = lineEdit->text();
	curveCombo->setItemText(index, name);
	emit nameChange(index, name);
}

void Panel::changePlotName()
{
	if(curveCombo->count() == 0) {
		return;
	}
	QString name = plotName->text();
	emit plotNameChange(name);
}

void Panel::changeLabels()
{
	if(curveCombo->count() == 0) {
		return;
	}
	QString nameX = labelX->text();
	QString nameY = labelY->text();
	emit labelsChange(nameX, nameY);

}

void Panel::changeGrid(int _state)
{
	emit gridChange(_state);
}

void Panel::setColor()
{
    QColor color;
	color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
    if (color.isValid()) {
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
	QString name = curveCombo->currentText();
	colorButton->setChecked(false);
	emit colorChange(name, color);
 }

void Panel::setBcgColor()
{
    QColor color;
	color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
    if (color.isValid()) {
        plotBcgColorLabel->setPalette(QPalette(color));
        plotBcgColorLabel->setAutoFillBackground(true);
    }
	plotBcgColorButton->setChecked(false);
	emit changeBackgroundColor(color);
 }

void Panel::deleteCurve()
{
	if(curveCombo->count() == 0) {
		return;
	}

	int index = curveCombo->currentIndex();
	curveCombo->removeItem(index);
	emit curveDelete(index);

	if(curveCombo->count() == 0) {
		lineEdit->clear();
		colorLabel->clear();
		aucLabel->clear();
		return;
	}
	
	curveCombo->setCurrentIndex(0);		//after delete display first

	QString which = curveCombo->currentText();
	lineEdit->setText(which);
	emit getColorAuc(which);
}

void Panel::hideAll()
{
	int index = curveCombo->currentIndex();
	emit hideAllExceptOfThis(index);
}
