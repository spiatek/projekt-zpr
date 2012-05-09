#include <qapplication.h>
#include "PlotWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
    PlotWindow window;
    window.resize(600,400);
	window.show();

    return app.exec(); 
}