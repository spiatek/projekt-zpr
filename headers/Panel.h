#ifndef _PANEL_H_
#define _PANEL_H_ 1

//#include "settings.h"
#include <qtabwidget.h>
#include <list>
#include <qlistwidget.h>
#include <qlist.h>

class QGridLayout;
class QComboBox;
class SpinBox;
class CheckBox;

class Panel: public QTabWidget
{
    Q_OBJECT

public:
    Panel(QWidget * = NULL);

    //Settings settings() const;
    //void setSettings(const Settings &);

signals:
    void settingsChanged(QString);

private slots:
	void addCurve(QString, QColor, double);
	void edited(int);

private:
    /*QWidget *createPlotTab(QWidget *);
    QWidget *createCanvasTab(QWidget *);
    QWidget *createCurveTab(QWidget *);
	*/
	/*
    SpinBox *d_numPoints;
    SpinBox *d_updateInterval;
    QComboBox *d_updateType;

    QComboBox *d_gridStyle;
    CheckBox *d_paintCache;
    CheckBox *d_paintOnScreen;
    CheckBox *d_immediatePaint;
*/
	QWidget* curvesTab;
	QGridLayout* curvesLayout;
	//QCheckListIcon* checkList;

	int counter;

  /*  SpinBox  *d_curveWidth;
    QComboBox *d_curvePen;
    CheckBox *d_curveFilled;*/
};

#endif
