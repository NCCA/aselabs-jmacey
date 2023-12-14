#include "MainWindow.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{

	QSurfaceFormat format;
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setMajorVersion(4);
	format.setMinorVersion(1);
	format.setDepthBufferSize(24);
	QSurfaceFormat::setDefaultFormat(format);

	QApplication a(argc, argv);

	QCommandLineParser parser;

	QCommandLineOption numberOption("n", "The number to convert to an integer.", "number");
	parser.addOption(numberOption);

	parser.process(a);
	int numParticles=10;
	if(parser.isSet(numberOption))
	{
		bool ok;
		numParticles=parser.value(numberOption).toInt(&ok);
	}


	MainWindow w;
	w.setNumParticles(numParticles);

	w.show();
	return a.exec();
}
