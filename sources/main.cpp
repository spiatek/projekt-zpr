#include <qapplication.h>
#include <qlibraryinfo.h>
#include "../headers/PlotWindow.h"

int main(int argc, char *argv[])
{	
	QApplication app(argc, argv);
	app.setApplicationName("Porównywanie krzywych");

	PlotWindow window;
    window.resize(800,400);
	window.show();

    return app.exec(); 
}
