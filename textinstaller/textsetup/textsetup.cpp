#include "textsetup.h"
#include "mediachecker.h"
#include "mechanics.h"

TextSetup::TextSetup(string _distro_version) {
	distro_version = _distro_version;
}

TextSetup::~TextSetup() {
	saveSettings();
}

int TextSetup::run() {
	int ret;
	for (int i=0; i<9; ++i) {
		switch(i) {
			case 0: ret = setPackageSource(); break;
			case 1: ret = setInstallType(); break;
			case 2: ret = setPartitionEditor(); break;
			case 3: ret = setMountPoints(); break;
			case 4: ret = setBootLoader(); break;
			case 5: ret = setRootPassword(); break;
			case 6: ret = setCreateUser(); break;
			case 7: ret = setNetworkSettings(); break;
			case 8: ret = setTimezone(); break;
			default: return -1;
		}
		if (ret!=0) i=i-2;
		if (i<0) return -1;
	}
	return 0;
}

string TextSetup::getISORepoPath() {
	string st, ret;
	st = ncInterface.subtitle;
	ncInterface.setSubtitle(_("Select ISO file:"));
	ret = ncInterface.ncGetOpenFile();
	ncInterface.setSubtitle(st);
	return ret;

}

string TextSetup::getHDDRepoPath() {
	string st, ret;
	st = ncInterface.subtitle;
	ncInterface.setSubtitle(_("Select directory which contains repository:"));
	ret = ncInterface.ncGetOpenDir();
	ncInterface.setSubtitle(st);
	return ret;
}


string TextSetup::getCustomRepoPath() {
	return ncInterface.showInputBox(_("Enter custom URL to repository:"));
}

int TextSetup::setPackageSource() {
	vector<MenuItem> m;
	m.push_back(MenuItem("Disc", _("Install from installation DVD or USB flash")));
	m.push_back(MenuItem("Network", _("Install from official network repository")));
	m.push_back(MenuItem("ISO", _("Install from ISO image")));
	m.push_back(MenuItem("HDD", _("Install from directory on local hard drive")));
	m.push_back(MenuItem("Custom", _("Specify custom repository set")));
	
	settings["pkgsource"] = ncInterface.showMenu2(_("Please, choose package source from a list below:"), m, settings["pkgsource"]);
	
	string repo, ret_repo, volname, rep_location;
	if (settings["pkgsource"].empty()) return 1;
	if (settings["pkgsource"]=="Disc") repo="dvd";
	if (settings["pkgsource"]=="Network") repo="http://core.agilialinux.ru/" + distro_version + "/";
	if (settings["pkgsource"]=="ISO") repo=getISORepoPath();
	if (settings["pkgsource"]=="HDD") repo=getHDDRepoPath();
	if (settings["pkgsource"]=="Custom") repo=getCustomRepoPath();
	



	customPkgSetList = mech.getCustomPkgSetList(repo, &ret_repo, &volname, &rep_location);
	settings["pkgsource"] = ret_repo;
	settings["volname"] = volname;
	settings["rep_location"] = rep_location;
	
	if (customPkgSetList.empty()) {
		if (ncInterface.showYesNo(_("Failed to retrieve required data from specified repository. Select another one?"))) return setPackageSource();
		else return 2;
	}

	return 0;
}

int TextSetup::setInstallType() {
	vector<MenuItem> m;

	for (size_t i=0; i<customPkgSetList.size(); ++i) {
		m.push_back(MenuItem(customPkgSetList[i].name, customPkgSetList[i].desc));
	}

	settings["pkgset"] = ncInterface.showMenu2(_("Select installation type:"), m, settings["pkgset"]);

	if (settings["pkgset"].empty()) return 1;

	setNvidiaDriver();
	return 0;
}

int TextSetup::setNvidiaDriver() {
	if (!mech.checkNvidiaLoad()) return 0;
	vector<MenuItem> m;
	m.push_back(MenuItem("latest", _("Latest NVIDIA driver for GeForce 6 and newer cards")));
	m.push_back(MenuItem("173", _("Legacy NVIDIA driver (173.xx) for GeForce 5 FX cards")));
	m.push_back(MenuItem("96", _("Legacy NVIDIA driver (96.xx) for GeForce 4 and older cards")));
	m.push_back(MenuItem("nv", _("NV: Non-accelerated opensource driver")));
	m.push_back(MenuItem("nouveau", _("Nouveau: accelerated, but unstable, opensource driver")));
	settings["nvidia-driver"]=ncInterface.showMenu2(_("You have NVIDIA video card. Please select appropriate driver to use:"), m, settings["nvidia-driver"]);
	if (settings["nvidia-driver"].empty()) return 1;
	return 0;
}

int TextSetup::setPartitionEditor() {
	vector<MenuItem> m;
	m.push_back(MenuItem("cfdisk", _("NCurses-based partition editor. MBR only.")));
	m.push_back(MenuItem("fdisk", _("Command-line partition editor. MBR only.")));
	m.push_back(MenuItem("parted", _("Another command-line partition editor. Be careful: for advanced users only.")));
	m.push_back(MenuItem("skip", _("Skip partition editing")));

	string p_editor = ncInterface.showMenu2(_("Please select partitioning tool. You can skip this step if you have already partitioned your hard drives"), m);

	if (p_editor.empty()) return 1;
	if (p_editor=="skip") return 0;

	vector<MenuItem> d;
	for (size_t i=0; i<mech.drives.size(); ++i) {
		d.push_back(MenuItem(mech.drives[i].tag, mech.drives[i].value));
		d.push_back(MenuItem("CONTINUE", _("Continue to next step")));
	}
	string drive;
	do {
		drive = ncInterface.showMenu2(_("Select drive to edit:"), d, drive);
		if (drive.empty() || drive=="CONTINUE") break;
		system(p_editor + " " + drive);
	} while (drive!="CONTINUE" && !drive.empty());

	if (drive.empty()) return setPartitionEditor();

	return 0;
}



int TextSetup::setMountPoints() {
	vector<MenuItem> m, fs;
	string fslabel;
	for (size_t i=0; i<mech.partitions.size(); ++i) {
		if (mech.partitions[i].fslabel.empty()) fslabel = _(", no label");
		else fslabel=_(", label: ") + mech.partitions[i].fslabel;
		m.push_back(MenuItem(mech.partitions[i].devname, humanizeSize((int64_t) atol(mech.partitions[i].size.c_str())*(int64_t) 1048576) + ", " + mech.partitions[i].fstype + fslabel));
	}
	m.push_back(MenuItem("CONTINUE", _("Continue to next step")));



	// Let's do some rock :)
	string part, mount_point, fs_options, mount_options;
	do {
		part = ncInterface.showMenu2(_("Please select partition to specify it's mount point and formatting options"), m, part);
		if (part.empty() || part=="CONTINUE") break;

		mapSettings[part]["mountpoint"] = cutSpaces(ncInterface.showInputBox(_("Enter mount point for partition ") + \
					part + _(", for example: '/boot' (without quotes). For swap partition, enter 'swap'. For root partition, enter '/'. If you wish to leave partition unused, leave this field empty."), \
					mapSettings[part]["mountpoint"]));

		if (mapSettings[part]["mountpoint"]!="swap") {
			mapSettings[part]["fs"] = ncInterface.showMenu2(_("Select filesystem for partition ") + \
					part + " (" + mapSettings[part]["mountpoint"] + _("). Select 'NONE' if you wish to keep data. NOTE: IF YOU CREATE NEW FILESYSTEM HERE, ALL DATA ON PARTITION WILL BE DESTROYED!"), \
					fs, mapSettings[part]["fs"]);

			mapSettings[part]["mount_options"] = ncInterface.showInputBox(_("Enter mount options for partition ") + \
					part + "(" + mapSettings[part]["mountpoint"] + ", " + mapSettings[part]["fs"] + _("). If you don't know what this stuff means, it is STRONGLY RECOMMENDED to leave it empty (to use default values)."), \
					mapSettings[part]["mount_options"]);
		}
		else {
			mapSettings[part]["fs"] = "swap";
			mapSettings[part]["mount_options"] = "";
		}


	} while (part!="CONTINUE" && !part.empty());

	return 0;
}

int TextSetup::setBootLoader() {
	string fstype;
	vector<MenuItem> m;
	m.push_back(MenuItem("MBR", _("Install in Master Boot Record (recommended")));
	m.push_back(MenuItem("Partition", _("Install on partition (for advanced users only)")));
	m.push_back(MenuItem("None", _("Do not install bootloader (think twice!)")));

	string b_type = ncInterface.showMenu2(_("Select where to install bootloader. If in doubt, select 'MBR'. All other options requires some additional preparations, which you should do manually."), m, "MBR");
	if (b_type=="None") {
		settings["bootloader"]="none";
		return 0;
	}
		m.clear();
	if (b_type=="MBR") {
		for (size_t i=0; i<mech.drives.size(); ++i) {
			m.push_back(MenuItem(mech.drives[i].tag, mech.drives[i].value));
		}

		settings["bootloader"] = ncInterface.showMenu2(_("Select disk for bootloader. Note for GPT users: you need a hybrid partition table to use GRUB on it."), m);
	}
	else if (b_type=="Partition") {
		for (size_t i=0; i<mech.partitions.size(); ++i) {
			// Blacklist some unbootable stuff
			fstype = mapSettings[mech.partitions[i].devname]["fs"]=="NONE";
			if (fstype=="NONE") fstype = mech.partitions[i].fstype;
			if (mapSettings[mech.partitions[i].devname]["mountpoint"].empty()) continue;
			if (mapSettings[mech.partitions[i].devname]["mountpoint"]=="swap") continue;
			if (fstype=="xfs" || fstype=="swap" || fstype=="unformatted") continue;
			m.push_back(MenuItem(mech.partitions[i].devname, humanizeSize((int64_t) atol(mech.partitions[i].size.c_str())*(int64_t) 1048576) + ", " + fstype + " " + mapSettings[mech.partitions[i].devname]["mountpoint"]));
		}
		settings["bootloader"] = ncInterface.showMenu2(_("Select partition for bootloader. Note: not all partitions listed here are suitable for keeping bootloader on it."), m);
	}
	
	return 0;
}

int TextSetup::setRootPassword() {
	string rootpwd1, rootpwd2;
	// Loop until user enters good password pair. Break is inside.
	while(true) {
		rootpwd1 = ncInterface.showInputBox(_("Enter root password. It should not be empty!"));
		if (rootpwd1.empty()) {
			ncInterface.showMsgBox(_("Empty root password is not allowed."));
			continue;
		}
		rootpwd2 = ncInterface.showInputBox(_("Confirm root password by entering it again."));
		if (rootpwd1 == rootpwd2) {
			settings["rootpassword"]=rootpwd1;
			break;
		}
		else {
			ncInterface.showMsgBox(_("Error: passwords does not match."));
		}
	}

	return 0;
}

int TextSetup::setCreateUser() {
	string username;
       	while (username.empty()) {
		username = ncInterface.showInputBox(_("Enter user name. It may contain only lowercase latin characters, digits and _ character. Username should not start with digit."));
	}
	settings["username"]=username;
	
	string pwd1, pwd2;
	// Loop until user enters good password pair. Break is inside.
	while(true) {
		pwd1 = ncInterface.showInputBox(_("Enter password for user ") + settings["username"] + _(". It should not be empty!"));
		if (pwd1.empty()) {
			ncInterface.showMsgBox(_("Empty password is not allowed."));
			continue;
		}
		pwd2 = ncInterface.showInputBox(_("Confirm password by entering it again."));
		if (pwd1 == pwd2) {
			settings["userpassword"]=pwd1;
			break;
		}
		else {
			ncInterface.showMsgBox(_("Error: passwords does not match."));
		}
	}
	return 0;
}

int TextSetup::setNetworkSettings() {
	// Three things: hostname, network name, network manager.
	// TODO: error handling (empty input, insane values, and so on).
	settings["hostname"] = ncInterface.showInputBox(_("Enter hostname:"), "agilia-box");
	settings["netname"] = ncInterface.showInputBox(_("Enter network name. Leave 'example.net' for intranet:"), "example.net");
	
	int hasNetworkManager = system("[ \"`cat /tmp/setup_variants/" + settings["pkgset"] + ".list | grep '^NetworkManager$'`\" = \"\" ]");
	int hasWicd = system("[ \"`cat /tmp/setup_variants/" + settings["pkgset"] + ".list | grep '^wicd$'`\" = \"\" ]");

	vector<MenuItem> m;
	if (hasNetworkManager) m.push_back(MenuItem("networkmanager", "Network Manager"));
	if (hasWicd) m.push_back(MenuItem("wicd", "Wicd"));
	m.push_back(MenuItem("manual", "Manual configuration via /etc/conf.d/network"));
	if (m.size()==1) settings["networkmanager"]="manual";
	else settings["networkmanager"] = ncInterface.showMenu2(_("Select the way you wish to manage your network:"), m);

	return 0;
}

int TextSetup::setTimezone() {
	// TODO: implement some easy way to find your timezone from this fuckin' large list
	string tmpfile = get_tmp_file();
	system("( cd /usr/share/zoneinfo && find . -type f | sed -e 's/\\.\\///g') > " + tmpfile);
	vector<string> tz = ReadFileStrings(tmpfile);
	unlink(tmpfile.c_str());
	vector<MenuItem> m;
	for (size_t i=0; i<tz.size(); ++i) {
		m.push_back(MenuItem(tz[i], ""));
	}
	settings["timezone"] = ncInterface.showMenu2(_("Select your timezone:"), m, "Europe/Moscow");

	if (ncInterface.showYesNo(_("Does your hardware clock stores time in UTC instead of localtime?"))) settings["hwclock"]="UTC";
	else settings["hwclock"]="local";

	return 0;
}


int TextSetup::saveSettings() {
	// Settings will be saved to ~/.config/textinstaller.conf
	vector<string> conf;

	map<string, string>::iterator it, mit;
	map<string, map<string, string> >::iterator mapit;

	for (it=settings.begin(); it!=settings.end(); it++) {
		conf.push_back(it->first + "=" + it->second);
	}

	for (mapit=mapSettings.begin(); mapit!=mapSettings.end(); mapit++) {
		for (mit=mapSettings[mapit->first].begin(); mit!=mapSettings[mapit->first].end(); mit++) {
			conf.push_back("[" + mapit->first + "]");
			conf.push_back(mit->first + "=" + mit->second);
		}
	}

	string home = getenv("HOME");
	if (!FileExists(home + "/.config")) system("mkdir -p " + home + "/.config");
	WriteFileStrings(home + "/.config/textinstaller.conf", conf);
	return 0;
}
