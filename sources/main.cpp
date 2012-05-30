#include <qapplication.h>
#include <qtranslator.h>
#include <qlibraryinfo.h>
#include "../headers/PlotWindow.h"

int main(int argc, char *argv[])
{	
	QApplication app(argc, argv);
	app.setApplicationName("Porównywanie krzywych");
     
	QString translatorFileName = QLatin1String("qt_");
     translatorFileName += QLocale::system().name();
     QTranslator *translator = new QTranslator(&app);
     if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
         app.installTranslator(translator);

	PlotWindow window;
    window.resize(800,400);
	window.show();

    return app.exec(); 
}
