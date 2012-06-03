/**
 * @file
 * @author  Szymon Piątek, Mateusz Matuszewski
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
 * Class for creating and control of panels. allows to change curves and
 * plotting parameters
 */



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
	void clearPlot();
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
	void clearAll();
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
	QPushButton* clearButton;
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

