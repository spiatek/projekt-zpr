#include "..\headers\Panel.h"
#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qwt_plot_curve.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcolor.h>
#include <qcolordialog.h>
#include <qtextcodec.h>

class SpinBox: public QSpinBox
{
public:
    SpinBox(int min, int max, int step, QWidget *parent):
        QSpinBox(parent)
    {
        setRange(min, max);
        setSingleStep(step);
    }
};

class CheckBox: public QCheckBox
{
public:
    CheckBox(const QString &title, QWidget *parent):
        QCheckBox(title, parent)
    {
    }

    void setChecked(bool checked)
    {
        setCheckState(checked ? Qt::Checked : Qt::Unchecked);
    }

    bool isChecked() const
    {
        return checkState() == Qt::Checked;
    }
};

Panel::Panel(QWidget *parent):
    QTabWidget(parent)
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("Windows-1250"));	
    setTabPosition(QTabWidget::North);
		
	//addTab(createPlotTab(this), "Plot");
    //addTab(createCanvasTab(this), "Canvas");
    //addTab(createCurveTab(this), "Curve");

	addTab(createNewTab(this), "Curve Properties");

   // setSettings(Settings());

	connect(curveCombo, SIGNAL(currentIndexChanged(const QString&)), SLOT(edited(const QString&)));

	/*
    connect(d_numPoints, SIGNAL(valueChanged(int)), SLOT(edited()) );
    connect(d_updateInterval, SIGNAL(valueChanged(int)), SLOT(edited()) );
    connect(d_curveWidth, SIGNAL(valueChanged(int)), SLOT(edited()) );
    connect(d_paintCache, SIGNAL(stateChanged(int)), SLOT(edited()) );
    connect(d_paintOnScreen, SIGNAL(stateChanged(int)), SLOT(edited()) );
    connect(d_immediatePaint, SIGNAL(stateChanged(int)), SLOT(edited()) );
    connect(d_curveAntialiasing, SIGNAL(stateChanged(int)), SLOT(edited()) );
    connect(d_curveClipping, SIGNAL(stateChanged(int)), SLOT(edited()) );
    connect(d_lineSplitting, SIGNAL(stateChanged(int)), SLOT(edited()) );
    connect(d_curveFilled, SIGNAL(stateChanged(int)), SLOT(edited()) );

    connect(d_updateType, SIGNAL(currentIndexChanged(int)), SLOT(edited()) );
    connect(d_gridStyle, SIGNAL(currentIndexChanged(int)), SLOT(edited()) );
    connect(d_curveType, SIGNAL(currentIndexChanged(int)), SLOT(edited()) );
    connect(d_curvePen, SIGNAL(currentIndexChanged(int)), SLOT(edited()) );*/
}

/*QWidget *Panel::createPlotTab(QWidget *parent)
{
    QWidget *page = new QWidget(parent);

    d_updateInterval = new SpinBox(0, 1000, 10, page);
    d_numPoints = new SpinBox(10, 1000000, 1000, page);

    d_updateType = new QComboBox(page);
    d_updateType->addItem("Repaint");
    d_updateType->addItem("Replot");

    int row = 0;

    QGridLayout *layout = new QGridLayout(page);

    layout->addWidget(new QLabel("Updates", page), row, 0 );
    layout->addWidget(d_updateInterval, row, 1);
    layout->addWidget(new QLabel("ms", page), row++, 2 );

    layout->addWidget(new QLabel("Points", page), row, 0 );
    layout->addWidget(d_numPoints, row++, 1);

    layout->addWidget(new QLabel("Update", page), row, 0 );
    layout->addWidget(d_updateType, row++, 1);

    layout->addLayout(new QHBoxLayout(), row++, 0);

    layout->setColumnStretch(1, 10);
    layout->setRowStretch(row, 10);

    return page;
}*/

/*QWidget *Panel::createCanvasTab(QWidget *parent)
{
    QWidget *page = new QWidget(parent);

    d_gridStyle = new QComboBox(page);
    d_gridStyle->addItem("None");
    d_gridStyle->addItem("Solid");
    d_gridStyle->addItem("Dashes");

    d_paintCache = new CheckBox("Paint Cache", page);
    d_paintOnScreen = new CheckBox("Paint On Screen", page);
    d_immediatePaint = new CheckBox("Immediate Paint", page);

    int row = 0;

    QGridLayout *layout = new QGridLayout(page);
    layout->addWidget(new QLabel("Grid", page), row, 0);
    layout->addWidget(d_gridStyle, row++, 1);

    layout->addWidget(d_paintCache, row++, 0, 1, -1);
    layout->addWidget(d_paintOnScreen, row++, 0, 1, -1);
    layout->addWidget(d_immediatePaint, row++, 0, 1, -1);

    layout->addLayout(new QHBoxLayout(), row++, 0);

    layout->setColumnStretch(1, 10);
    layout->setRowStretch(row, 10);

    return page;
}*/
	/*
QWidget *Panel::createCurveTab(QWidget *parent)
{
    QWidget *page = new QWidget(parent);

    d_curveType = new QComboBox(page);
    d_curveType->addItem("Wave");
    d_curveType->addItem("Noise");

    d_curveAntialiasing = new CheckBox("Antialiasing", page);
    d_curveClipping = new CheckBox("Clipping", page);
    d_lineSplitting = new CheckBox("Split Lines", page);

    d_curveWidth = new SpinBox(0, 10, 1, page);

    d_curvePen = new QComboBox(page);
    d_curvePen->addItem("Solid");
    d_curvePen->addItem("Dotted");

    d_curveFilled = new CheckBox("Filled", page);

    int row = 0;

    QGridLayout *layout = new QGridLayout(page);
    layout->addWidget(new QLabel("Type", page), row, 0 );
    layout->addWidget(d_curveType, row++, 1);

    layout->addWidget(d_curveAntialiasing, row++, 0, 1, -1);
    layout->addWidget(d_curveClipping, row++, 0, 1, -1);
    layout->addWidget(d_lineSplitting, row++, 0, 1, -1);

    layout->addWidget(new QLabel("Width", page), row, 0 );
    layout->addWidget(d_curveWidth, row++, 1);

    layout->addWidget(new QLabel("Style", page), row, 0 );
    layout->addWidget(d_curvePen, row++, 1);

    layout->addWidget(d_curveFilled, row++, 0, 1, -1);

    layout->addLayout(new QHBoxLayout(), row++, 0);

    layout->setColumnStretch(1, 10);
    layout->setRowStretch(row, 10);

    return page;
}*/

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
	
	connect(nameButton, SIGNAL(clicked()), this, SLOT(changeName()));
	connect(colorButton, SIGNAL(clicked()), this, SLOT(setColor()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteCurve()));
	connect(hideAllButton, SIGNAL(clicked()), this, SLOT(hideAll()));

	curvesTab->repaint();
}

void Panel::changeName()
{
	//emit, ¿eby zmieniæ nazwê
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
 }

void Panel::deleteCurve()
{
	//emit, ¿eby usun¹æ krzyw¹
}

void Panel::hideAll()
{
	//emit, ¿eby usun¹æ krzyw¹
}

/*
Settings Panel::settings() const
{
    Settings s;

    s.grid.pen = QPen(Qt::black);

    switch(d_gridStyle->currentIndex())
    {
        case 0:
            s.grid.pen.setStyle(Qt::NoPen);
            break;
        case 2:
            s.grid.pen.setStyle(Qt::DashLine);
            break;
    }
    
    s.curve.pen.setStyle(d_curvePen->currentIndex() == 0 ?
        Qt::SolidLine : Qt::DotLine);
    s.curve.pen.setWidth(d_curveWidth->value());
    s.curve.brush.setStyle((d_curveFilled->isChecked()) ?
        Qt::SolidPattern : Qt::NoBrush);
    s.curve.numPoints = d_numPoints->value();
    s.curve.functionType = (Settings::FunctionType)d_curveType->currentIndex();
    if ( d_curveClipping->isChecked() )
        s.curve.paintAttributes |= QwtPlotCurve::ClipPolygons;
    else
        s.curve.paintAttributes &= ~QwtPlotCurve::ClipPolygons;

    if ( d_curveAntialiasing->isChecked() )
        s.curve.renderHint |= QwtPlotCurve::RenderAntialiased;
    else
        s.curve.renderHint &= ~QwtPlotCurve::RenderAntialiased;

    s.curve.lineSplitting = (d_lineSplitting->isChecked() );

    s.canvas.useBackingStore = (d_paintCache->isChecked() );
    s.canvas.paintOnScreen = (d_paintOnScreen->isChecked() );
    s.canvas.immediatePaint = (d_immediatePaint->isChecked() );

    s.updateInterval = d_updateInterval->value();
    s.updateType = (Settings::UpdateType)d_updateType->currentIndex();

    return s;
}

void Panel::setSettings(const Settings &s)
{
    d_numPoints->setValue(s.curve.numPoints);
    d_updateInterval->setValue(s.updateInterval);
    d_updateType->setCurrentIndex(s.updateType);

    switch(s.grid.pen.style())
    {
        case Qt::NoPen:
            d_gridStyle->setCurrentIndex(0);
            break;
        case Qt::DashLine:
            d_gridStyle->setCurrentIndex(2);
            break;
        default:
            d_gridStyle->setCurrentIndex(1); // Solid
    }

    d_paintCache->setChecked(s.canvas.useBackingStore );
    d_paintOnScreen->setChecked(s.canvas.paintOnScreen);
    d_immediatePaint->setChecked(s.canvas.immediatePaint);

    d_curveType->setCurrentIndex(s.curve.functionType);
    d_curveAntialiasing->setChecked(
        s.curve.renderHint & QwtPlotCurve::RenderAntialiased );

    d_curveClipping->setChecked(
        s.curve.paintAttributes & QwtPlotCurve::ClipPolygons);

    d_lineSplitting->setChecked(s.curve.lineSplitting );

    d_curveWidth->setValue(s.curve.pen.width());
    d_curvePen->setCurrentIndex(
        s.curve.pen.style() == Qt::SolidLine ? 0 : 1);
    d_curveFilled->setChecked(s.curve.brush.style() != Qt::NoBrush);
}
*/