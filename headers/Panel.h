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
 * Class for creating and control of panels. Allows to change curves and
 * plotting parameters.
 * Panel class derives from QTabWidget class.
 */

#pragma once

#include <qtabwidget.h>
#include <list>
#include <qlistwidget.h>
#include <qlist.h>
#include <qpointer.h>

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
    Panel(QPointer<QWidget> parent = NULL, int _type = 0);

signals:
    void settingsChanged(QString);
	void nameChange(int, QString);
	void colorChange(int, QColor);
	void getColorAuc(int);
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

private:
	QPointer<QWidget> createCurveTab(QPointer<QWidget>);
	QPointer<QWidget> createPlotTab(QPointer<QWidget>);

	QPointer<QWidget> curvesTab;
	QPointer<QWidget> plotTab;

	QPointer<QComboBox> curvesCombo;

	QPointer<QLineEdit> lineEdit;
	QPointer<QLabel> colorLabel;
	QPointer<QLabel> aucLabel;
	QPointer<QPushButton> colorButton;
	QPointer<QPushButton> nameButton;
	QPointer<QPushButton> deleteButton;
	QPointer<QPushButton> hideAllButton;
	QPointer<QPushButton> clearButton;
	QPointer<QGridLayout> curvesLayout;

	QPointer<QLineEdit> plotName;
	QPointer<QLineEdit> labelX;
	QPointer<QLineEdit> labelY;
	QPointer<QLabel> plotBcgColorLabel;
	QPointer<QPushButton> plotNameButton;
	QPointer<QPushButton> labelButton;
	QPointer<QPushButton> plotBcgColorButton;
	QPointer<QGridLayout> plotLayout;
	QPointer<QCheckBox> gridCheckBox;

	int type;
};

