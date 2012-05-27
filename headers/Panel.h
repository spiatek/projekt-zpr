#ifndef _PANEL_H_
#define _PANEL_H_ 1

//#include "settings.h"
#include <qtabwidget.h>
#include <list>
#include <qlistwidget.h>
#include <qlist.h>

class QGridLayout;
class QComboBox;
class QPushButton;
class QLabel;
class SpinBox;
class CheckBox;
class QLineEdit;

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
	void edited(const QString&);
	void setColor();
	void changeName();
	void deleteCurve();
	void hideAll();

private:
    /*QWidget *createPlotTab(QWidget *);
    QWidget *createCanvasTab(QWidget *);
    QWidget *createCurveTab(QWidget *);
	*/
	QWidget *createNewTab(QWidget *);
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
	QComboBox* curveCombo;
	QLabel* colorLabel;
	QLabel* aucLabel;
	QPushButton* colorButton;
	QPushButton* nameButton;
	QPushButton* deleteButton;
	QPushButton* hideAllButton;
	QGridLayout* curvesLayout;
	QLineEdit* lineEdit;
	//QCheckListIcon* checkList;

	int counter;

  /*  SpinBox  *d_curveWidth;
    QComboBox *d_curvePen;
    CheckBox *d_curveFilled;*/
};

#endif
