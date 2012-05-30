#include "..\headers\fileProxy.h"
#include <QFile>

//constructor
RealFile::RealFile(QString _path){
	path=_path;
}

//destructor
RealFile::~RealFile(){
	//delete data_points;
}

QVector<QPointF>* RealFile::getData(){
qDebug()<<" RealFile::getData";
	//read from file
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QTextStream in(&file);
	QString line;
	qDebug()<<" RealFile::getData2";
	
	while (!in.atEnd()) {
		line= in.readLine();
		QStringList field = line.split("\t", QString::SkipEmptyParts);
		if (field.size()!=2){
			qDebug()<<"fileproxy error:"<<line;
			continue;
		}
		qDebug()<<field.at(0).toFloat()<<","<<field.at(1).toFloat()<<"  size:"<<field.size();
		data_points.append( QPointF( field.at(0).toFloat(), field.at(1).toFloat() ) );	
	}
	qDebug()<<" RealFile::getData return";
	return &data_points;
}

ProxyFile::ProxyFile(){
}
		
ProxyFile::ProxyFile(QString _path){
	real_file_path=_path;
	p_real_file=0;
}

ProxyFile::~ProxyFile(){
	delete p_real_file;
}

ProxyFile* ProxyFile::init_path(QString _path){
	if (!p_real_file){
		delete p_real_file;
	}
	real_file_path=_path;
	return this;
}
		
QVector<QPointF>* ProxyFile::getData(){
	if (!p_real_file){
		p_real_file= new RealFile(real_file_path);
	}
	return p_real_file->getData();
}


 /*
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }

     QTextStream in(&file);
 #ifndef QT_NO_CURSOR
     QApplication::setOverrideCursor(Qt::WaitCursor);
 #endif
     //textEdit->setPlainText(in.readAll());
 #ifndef QT_NO_CURSOR
     QApplication::restoreOverrideCursor();
 #endif

     setCurrentFile(fileName);
     statusBar()->showMessage(tr("File loaded"), 2000);
 */
