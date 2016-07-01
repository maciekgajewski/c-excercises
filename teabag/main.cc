#include <QApplication>

#include "debugger.hh"

#include <iostream>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	if (argc < 2)
	{
		std::cerr << "Usage: " << app.applicationName().toStdString() << " <binary-file>" << std::endl;
		return 2;
	}

	Teabag::Debugger debugger;
	debugger.start(QString::fromLocal8Bit(argv[1]));

	QObject::connect(&debugger, SIGNAL(finished()), &app, SLOT(quit()));

	QObject::connect(&debugger, &Teabag::Debugger::consoleOutput, [](const QString& o)
		{
			std::cout << "GDB: " << o.toStdString() << std::endl;
		});

	QObject::connect(&debugger, &Teabag::Debugger::targetOutput, [](const QString& o)
		{
			std::cout << "TARGET: " << o.toStdString() << std::endl;
		});

	return app.exec();
}

