// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
///#include <QApplication>
#include <QGuiApplication>
#include "mainwindow.h"
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[]) {
	
	setlocale(LC_ALL, "");
	
	QApplication a(argc, argv);
	QLocale lc;
	QTranslator translator;
	translator.load("guisetup_lang_" + lc.name(), "/usr/share/setup/l10n");
	a.installTranslator(&translator);

	MainWindow w;
	w.show();
	return a.exec();
}

