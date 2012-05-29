#pragma once

#include <qtabwidget.h>
#include <list>
#include <qlistwidget.h>
#include <qlist.h>

class QGridLayout;
class QComboBox;
class QPushButton;
class QLabel;
class QLineEdit;
class QCheckBox;

class Panel: public QTabWidget
{
    Q_OBJECT

public:
    Panel(QWidget * = NULL, int _type = 0);

signals:
    void settingsChanged(QString);
	void nameChange(int, QString);
	void colorChange(QString, QColor);
	void getColorAuc(QString);
	void curveDelete(int);
	void hideAllExceptOfThis(int);
	void changeBackgroundColor(QColor);
	void plotNameChange(QString);
	void labelsChange(QString, QString);
	void gridChange(int);

private slots:
	void addCurve(QString, QColor, double);
	void edited(const QString&);
	void setColor();
	void changeName();
	void deleteCurve();
	void hideAll();
	void readColorAuc(QColor, double);
	void setBcgColor();
	void changePlotName();
	void changeLabels();
	void changeGrid(int);
	//void switchPlot(int);

private:
	QWidget *createCurveTab(QWidget *);
	QWidget *createPlotTab(QWidget *);

	QWidget* curvesTab;
	QWidget* plotTab;

	QComboBox* curvesCombo;

	QLineEdit* lineEdit;
	QLabel* colorLabel;
	QLabel* aucLabel;
	QPushButton* colorButton;
	QPushButton* nameButton;
	QPushButton* deleteButton;
	QPushButton* hideAllButton;
	QGridLayout* curvesLayout;

	QLineEdit* plotName;
	QLineEdit* labelX;
	QLineEdit* labelY;
	QLabel* plotBcgColorLabel;
	QPushButton* plotNameButton;
	QPushButton* labelButton;
	QPushButton* plotBcgColorButton;
	QGridLayout* plotLayout;
	QCheckBox* gridCheckBox;

	int type;
};