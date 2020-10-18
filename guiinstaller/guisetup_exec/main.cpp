// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>
#include <mpkg/libmpkg.h>
#include <QLocale>
#include <QTranslator>
int main(int argc, char *argv[]) {
	// This should be run as root since it does lots of things that require root privileges.
	if (getuid()) {
		// trying to obtain root UID
		setuid(0);
		if (getuid()) {
			string args;
			for (int i=1; i<argc; ++i) {
				args += string(argv[i]) + " ";
			}
			if (system("[ \"`sudo -l | grep " + string(argv[0]) + " | grep NOPASSWD`\" = \"\" ]")) return system("sudo " + string(argv[0]) + " " + args);
			else return system("xdg-su -c \"" + string(argv[0]) + " " + args + "\"");
		}
	}

	if (argc>1 && strcmp(argv[1], "-v")==0) verbose=1;
	// Check for already running process
	if (FileExists("/var/run/guisetup.pid")) {
		string pid_locked = ReadFile("/var/run/guisetup.pid").c_str();
		if (isProcessRunning(pid_locked)) {
			fprintf(stderr, "Another setup process %s is alrealy running.\n", pid_locked.c_str());
			return 1;
		}
	}

	// Store lock file
	pid_t pid = getpid();
	if (FileExists("/var/run/guisetup_exec.pid")) {
		string pid_locked = ReadFile("/var/run/guisetup_exec.pid").c_str();
		if (isProcessRunning(pid_locked)) {
			fprintf(stderr, "Another setup process %s is alrealy running.\n", pid_locked.c_str());
			return 1;
		}
	}
	WriteFile("/var/run/guisetup_exec.pid", IntToStr(pid));
	setupMode=true;
	simulate=false;
	forceSkipLinkMD5Checks=false;
	forceInInstallMD5Check = false;
	// We don't care of database integrity in case of installation failure half-way, so we can use fast mode. It has beed tested enough, and I think it is useful.
	//  Warp drive active!
	_cmdOptions["ramwarp"]="no";
	_cmdOptions["warpmode"]="yes";
	if (FileExists("/tmp/sw1")) _cmdOptions["doinst_scrinst"]="yes";
	if (FileExists("/tmp/sw2")) _cmdOptions["bashamp"]="yes";
	noEject=true;


	setlocale(LC_ALL, "");
	bindtextdomain( "mpkg", "/usr/share/locale");
	textdomain("mpkg");
	
	if (!FileExists("/usr/share/setup/packages.db")) {
		mError("Oops, no database template in /usr/share/setup/packages.db!");
		return 1;
	}
	if (!FileExists("/usr/share/setup/mpkg-setup.xml")) {
		mError("Oops, no config template in /usr/share/setup/mpkg-setup.xml!");
		return 1;
	}

	CONFIG_FILE="/usr/share/setup/mpkg-setup.xml";
	mConfig.configName=CONFIG_FILE;
	unlink("/tmp/packages.db");
	system("cp /usr/share/setup/packages.db /tmp/packages.db");

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QApplication a(argc, argv);
	QLocale lc;
	QTranslator translator;
	translator.load("guisetup_exec_" + lc.name(), "/usr/share/setup/l10n");
	a.installTranslator(&translator);

	MainWindow w;
	w.show();
	int ret = a.exec();
	unlink("/var/run/guisetup_exec.pid");
	return ret;
}

