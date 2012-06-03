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
 * Initialize the program and window
 */


#include <qapplication.h>
#include <qlibraryinfo.h>
#include "../headers/PlotWindow.h"

int main(int argc, char *argv[]){	
	QApplication app(argc, argv);
<<<<<<< HEAD
	app.setApplicationName("Por�wnywanie krzywych");
=======
	app.setApplicationName("Porównywanie krzywych");
    
	QString translatorFileName = QLatin1String("qt_");
    translatorFileName += QLocale::system().name();
    QTranslator *translator = new QTranslator(&app);
    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    	app.installTranslator(translator);
>>>>>>> f6a94097b79b49d7a236856a5465e87029f68ffb

	PlotWindow window;
    window.resize(800,400);
	window.show();

    return app.exec(); 
}

