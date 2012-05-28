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

class Panel: public QTabWidget
{
    Q_OBJECT

public:
    Panel(QWidget * = NULL);

signals:
    void settingsChanged(QString);
	void nameChange(int, QString);
	void colorChange(QString, QColor);
	void getColorAuc(QString);
	void curveDelete(int);
	void hideAllExceptOfThis(int);

private slots:
	void addCurve(QString, QColor, double);
	void edited(const QString&);
	void setColor();
	void changeName();
	void deleteCurve();
	void hideAll();
	void readColorAuc(QColor, double);

private:
	QWidget *createNewTab(QWidget *);
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
};