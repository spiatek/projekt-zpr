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
		
	addTab(createNewTab(this), "Curve Properties");

	connect(curveCombo, SIGNAL(currentIndexChanged(const QString&)), SLOT(edited(const QString&)));
}

QWidget *Panel::createNewTab(QWidget *parent)
{
	curvesTab = new QWidget(parent);

	curveCombo = new QComboBox(parent);
	//curvesTab = new QWidget(parent);
	curvesLayout = new QGridLayout(curvesTab);
    //addTab(curvesTab, "Krzywe");
	//counter = 0;

    //curvesLayout = new QGridLayout(parent);
    curvesLayout->addWidget(new QLabel("Choose curve:", parent), 0, 0 );
    curvesLayout->addWidget(curveCombo, 1, 0);

	lineEdit = new QLineEdit("", curvesTab);
	QLabel *label1 = new QLabel("Title:", curvesTab);
	curvesLayout->addWidget(label1, 4, 0);
	curvesLayout->addWidget(lineEdit, 5, 0);
	nameButton = new QPushButton(tr("Change title"));
	curvesLayout->addWidget(nameButton, 6, 0);

	QLabel *label2 = new QLabel("Color:", curvesTab);
	curvesLayout->addWidget(label2, 7, 0);
	colorLabel = new QLabel();
	curvesLayout->addWidget(colorLabel, 8, 0);
	colorButton = new QPushButton(tr("Change color"));
	curvesLayout->addWidget(colorButton, 9, 0);

	QLabel *label3 = new QLabel("AUC:", curvesTab);
	curvesLayout->addWidget(label3, 10, 0);
	aucLabel = new QLabel();
	curvesLayout->addWidget(aucLabel, 11, 0);

	deleteButton = new QPushButton(tr("Delete curve"));
	curvesLayout->addWidget(deleteButton, 12, 0);

	hideAllButton = new QPushButton(tr("Hide all except of this"));
	curvesLayout->addWidget(hideAllButton, 13, 0);

	curvesLayout->setColumnStretch(1, 10);
    curvesLayout->setRowStretch(14, 20);

	connect(nameButton, SIGNAL(clicked()), this, SLOT(changeName()));
	connect(colorButton, SIGNAL(clicked()), this, SLOT(setColor()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteCurve()));
	connect(hideAllButton, SIGNAL(clicked()), this, SLOT(hideAll()));

	curvesTab->repaint();

	return curvesTab;
}

void Panel::addCurve(QString _name, QColor _color, double _auc)
{
	//checkList = new QCheckListIcon();
	curveCombo->addItem(_name);
	curveCombo->setCurrentIndex(curveCombo->count() - 1);
	lineEdit->setText(_name);
	
	colorLabel->setPalette(QPalette(_color));
	colorLabel->setAutoFillBackground(true);

	QString auc = QString("%1").arg(_auc);
	aucLabel->clear();
	aucLabel->setText(auc);

	//CheckBox *curve = new CheckBox(_name, curvesTab);
	//curve->setChecked(true);
	//curvesLayout->addWidget(curve, counter++, 0, 1, -1);
    //curvesLayout->addLayout(new QHBoxLayout(), counter++, 0);
    //curvesLayout->setColumnStretch(1, 10);
    //curvesLayout->setRowStretch(counter, 10);
	curvesTab->repaint();
	//checkboxes->push_back(curve);
	//int size = checkboxes->size();
	//int index = size - 1;

}

void Panel::edited(const QString& which)
{
	lineEdit->setText(which);
	emit getColorAuc(which);
	//curvesTab->repaint();
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
	int index = curveCombo->currentIndex();
	QString name = lineEdit->text();
	curveCombo->setItemText(index, name);
	emit nameChange(index, name);
}

void Panel::setColor()
{
    QColor color;
	color = QColorDialog::getColor(Qt::green, this, "Select Color", QColorDialog::DontUseNativeDialog);
    if (color.isValid()) {
        //colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
	QString name = curveCombo->currentText();
	colorButton->setChecked(false);
	emit colorChange(name, color);
 }

void Panel::deleteCurve()
{
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
