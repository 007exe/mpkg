// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "console-help.h"
void showBanner() {
	say("MPKG package system v.%s\n", mpkgVersion);
}

int showCmdHelp(const string cmd, bool is_error)
{
	FILE *stream = stdout;
	if (is_error) stream = stderr;

	showBanner();

	fprintf(stream, _("\nUsage: %s [options] ACTION [package] [package] ...\n"), cmd.c_str());
	fprintf(stream, "%s", _("Common options:\n"));
	fprintf(stream, "%s", _("\t-h\t--help\t\t\t\tshow this help\n"));
	fprintf(stream, "%s", _("\t-v\t--verbose\t\t\tbe verbose\n"));
	fprintf(stream, "%s", _("\t-g\t--dialog\t\t\tuse dialog mode UI\n"));
	fprintf(stream, "%s", _("\t-d\t--force-dep\t\t\tinterpret dependency errors as warnings\n"));
	fprintf(stream, "%s", _("\t-z\t--no-dep\t\t\ttotally ignore dependencies existance\n"));
	fprintf(stream, "%s", _("\t-f\t--force-conflicts\t\tdo not perform file conflict checking\n"));
	fprintf(stream, "%s", _("\t-m\t--no-md5\t\t\tdo not check package integrity on install\n"));
	fprintf(stream, "%s", _("\t-k\t--force-essential\t\tallow removing essential packages\n"));
	fprintf(stream, "%s", _("\t-D\t--download-only\t\t\tjust download packages, do not install\n"));
	fprintf(stream, "%s", _("\t-r\t--repair\t\t\trepair damaged packages (use with \"check\" keyword)\n"));
	fprintf(stream, "%s", _("\t-i\t--installed\t\t\tshow only installed packages (use with \"list\" keyword)\n"));
	fprintf(stream, "%s", _("\t-a\t--available\t\t\tshow only available packages (use with \"list\" keyword)\n"));
	fprintf(stream, "%s", _("\t-l\t--filelist\t\t\tshow file list for package (with \"show\" keyword)\n"));
	fprintf(stream, "%s", _("\t-y\t--noconfirm\t\t\tdon't ask confirmation\n"));
	fprintf(stream, "%s", _("\t-q\t--noreset\t\t\tdon't reset queue at start\n"));
	fprintf(stream, "%s", _("\t-N\t--nodepgen\t\t\tdon't generate dependencies on package building\n"));
	fprintf(stream, "%s", _("\t-w\t--no_buildcache\t\t\tdon't use source cache when building packages\n"));
	fprintf(stream, "%s", _("\t-c\t--no_resume\t\t\tdisable download resuming\n"));
	fprintf(stream, "%s", _("\t-b\t--cleartags\t\t\tclear all other tags before tagging\n"));
	fprintf(stream, "%s", _("\t-F\t--fork\t\t\t\tdetach from terminal and run in background\n"));
	fprintf(stream, "%s", _("\t-Q\t--enqueue\t\t\tonly enqueue actions, do not perform\n"));
	fprintf(stream, "%s", _("\t-V\t--enableversions\t\tenable versioning in install lists\n"));
	fprintf(stream, "%s", _("\t-R\t--index-filelist\t\tcreate file list while indexing\n"));
	fprintf(stream, "%s", _("\t-M\t--md5index\t\t\tadd md5 sums for each file in filelist\n"));
	fprintf(stream, "%s", _("\t-S\t--sysroot=<DIR>\t\t\tset temporary system root\n"));
	fprintf(stream, "%s", _("\t-L\t--linksonly\t\t\ton install/upgradeall, show only download links and exit\n"));
	fprintf(stream, "%s", _("\t-P\t--noaaa\t\t\t\ttry to avoid aaa_elflibs in dependency generation (for gendeps2)\n"));
	fprintf(stream, "%s", _("\t-G\t--keep-deps\t\t\tdo not replace deps in package, add to them instead (for gendeps2)\n"));
	fprintf(stream, "%s", _("\t-C\t--enable-cache\t\t\tenable cached indexing\n"));
	fprintf(stream, "%s", _("\t-K\t--skip-deprecated\t\twhile sync, skip deprecated packages\n"));
	fprintf(stream, "%s", _("\t-s\t--keep-symlinks\t\t\tkeep symlinks in archive instead of moving it to doinst.sh\n"));
	fprintf(stream, "%s", _("\t-e\t--arch=ARCH\t\t\ttemporarily override architecture. Valid options is x86_64 and x86.\n"));
	fprintf(stream, "%s", _("\t-Y\t--resync\t\t\tforces deep database update (takes longer time, but rebuilds all package metadata)\n"));
	fprintf(stream, "%s", _("\t-X\t--skip=PKG1,PKG2...\t\tskip specified packages in upgradeall or listupdates\n"));
	fprintf(stream, "%s", _("\t-t\t--conf=CONFIG_FILE\t\tset temporary config file\n"));
	fprintf(stream, "%s", _("\t-A\t--download-to=<DIR>\t\tdownload packages to specified directory\n"));
	fprintf(stream, "%s", _("\t-W\t--enable-spkg-index\t\tenable spkg indexing (otherwise, it will be skipped)\n"));
	fprintf(stream, "%s", _("\t-E\t--exclusion-list=FILENAME\texclude paths from being checked by gendeps2\n"));

	fprintf(stream, "%s", _("\nAvailable commands:\n"));
	fprintf(stream, "%s", _("\tmpkg-version\t\t\t\tshow mpkg version\n"));
	fprintf(stream, "%s", _("\tmpkg-install PACKAGE_NAME | FILENAME\tinstall package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-upgradeall\t\t\t\tupgrade all installed packages\n"));
	fprintf(stream, "%s", _("\tmpkg-reinstall PACKAGE_NAME\t\treinstall package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-remove PACKAGE_NAME\t\tremove selected package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-purge PACKAGE_NAME\t\t\tpurge selected package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-installgroup GROUP_NAME\t\tinstall all the packages from group\n"));
	fprintf(stream, "%s", _("\tmpkg-removegroup GROUP_NAME\t\tremove all the packages from group\n"));
	fprintf(stream, "%s", _("\tmpkg-listupdates\t\t\tlist available updates\n"));
	fprintf(stream, "%s", _("\tmpkg-show PACKAGE_NAME\t\t\tshow info about package\n"));
	fprintf(stream, "%s", _("\tmpkg-update\t\t\t\tupdate packages info\n"));
	fprintf(stream, "%s", _("\tmpkg-list\t\t\t\tshow the list of all packages in database\n"));
	fprintf(stream, "%s", _("\tmpkg-listgroup GROUP_NAME\t\tshow the list of packages belonged to group\n"));
	fprintf(stream, "%s", _("\tmpkg-listgroups\t\t\t\tshow the list of all existing groups\n"));
	fprintf(stream, "%s", _("\tmpkg-whodepend PACKAGE_NAME\t\tshow what packages depends on this one\n"));
	fprintf(stream, "%s", _("\tmpkg-filesearch FILE_NAME\t\tlook for owner of the file in installed packages (LIKE mode).\n"));
	fprintf(stream, "%s", _("\tmpkg-which FILE_NAME\t\t\tlook for owner of the file in installed packages (EQUAL mode).\n"));
	fprintf(stream, "%s", _("\tmpkg-list_rep\t\t\t\tlist enabled repositories\n"));
	fprintf(stream, "%s", _("\tmpkg-add_rep URL\t\t\tadd repository\n"));
	fprintf(stream, "%s", _("\tmpkg-delete_rep REPOSITORY_NUMBER\tdelete Nth repository\n"));
	fprintf(stream, "%s", _("\tmpkg-enable_rep REPOSITORY_NUMBER\tenable Nth repository\n"));
	fprintf(stream, "%s", _("\tmpkg-disable_rep REPOSITORY_NUMBER\tdisable Nth repository\n"));
	fprintf(stream, "%s", _("\tmpkg-getrepositorylist [LIST_URL]\tget the list of repositories from server (by default, from packages.agilialinux.ru)\n"));
	fprintf(stream, "%s", _("\tmpkg-installfromlist FILE_NAME\t\tinstall using file with list of items\n"));
	fprintf(stream, "%s", _("\tmpkg-exportinstalled [FILE_NAME]\texport list of installed packages to file or stdout\n"));
	fprintf(stream, "%s", _("\tmpkg-reset\t\t\t\treset queue\n"));
	fprintf(stream, "%s", _("\tmpkg-show_queue\t\t\t\tshow queue\n"));
	fprintf(stream, "%s", _("\tmpkg-commit\t\t\t\tcommit queued actions\n"));
	fprintf(stream, "%s", _("\tmpkg-search PATTERN\t\t\tsearch package by name containing PATTERN\n"));
	fprintf(stream, "%s", _("\tmpkg-searchdescription PATTERN\t\tsearch package by description containing PATTERN\n"));
	fprintf(stream, "%s", _("\tmpkg-clean\t\t\t\tremove all downloaded packages from cache\n"));
	fprintf(stream, "%s", _("\tmpkg-check [package_name]\t\tchecks installed package(s) for missing files. Use -r flag to to repair\n"));
	fprintf(stream, "%s", _("\tmpkg-checkdeps URL\t\t\tchecks specified repository if all dependencies can be resolved within same repository\n"));
	fprintf(stream, "%s", _("\tmpkg-checklibdeps [PACKAGE_NAME]\tchecks installed package(s) for broken binary dependencies.\n"));
	fprintf(stream, "%s", _("\tmpkg-altlist\t\t\t\tshows all alternatives in database\n"));
	fprintf(stream, "%s", _("\tmpkg-altshow PACKAGE_NAME\t\tshows all alternative branches of specified package\n"));
	fprintf(stream, "%s", _("\tmpkg-conflicts PACKAGE_NAME\t\tchecks package for file conflicts (files with same names and paths, but from different packages)\n"));
	fprintf(stream, "%s", _("\tmpkg-deleteprofile PROFILE_NAME\t\tdelete repository profile\n"));
	fprintf(stream, "%s", _("\tmpkg-depgraph URL OUTPUT_FILE\t\tgenerates dot file with dependency graph of specified package\n"));
	fprintf(stream, "%s", _("\tmpkg-deporder FILENAME\t\t\treads package names from specified file, and generates it's dependency order\n"));
	fprintf(stream, "%s", _("\tmpkg-fixdeps\t\t\t\tfixes broken dependencies of installed packages\n"));
	fprintf(stream, "%s", _("\tmpkg-listprofiles\t\t\tshows list of known repository profiles\n"));
	fprintf(stream, "%s", _("\tmpkg-maintainer OPTIONS [NAME] [EMAIL]\tget/set maintainer name and email (for mkpkg)\n"));
	fprintf(stream, "%s", _("\tmpkg-quicklist\t\t\t\tshows machine-readable list of all installed packages. Used primarily in bash-completion.\n"));
	fprintf(stream, "%s", _("\tmpkg-saveprofile PROFILE_NAME\t\tsaves current repository set under specified profile name.\n"));
	fprintf(stream, "%s", _("\tmpkg-setmeta PATH | FILENAME [OPTIONS]\ta tool to modify package metadata. See command help for details\n"));
	fprintf(stream, "%s", _("\tmpkg-setprofile PROFILE_NAME\t\tloads specified repository set profile.\n"));
	fprintf(stream, "%s", _("\tmpkg-spkg2abuild FILENAME\t\tconverts spkg file to ABUILD tree.\n"));
	fprintf(stream, "%s", _("\tmpkg-transactions\t\t\tshows all package transactions.\n"));
	fprintf(stream, "%s", _("\tmpkg-validate PATH | FILENAME\t\tvalidates package integrity and some guidelines.\n"));
	fprintf(stream, "%s", _("\tmpkg-rollback [TRANSACTION_ID] [PACKAGE_NAME]\ttransactions rollback. Rolls back latest transaction. See command help for details.\n"));

	fprintf(stream, "%s", _("\nInteractive options:\n"));
	fprintf(stream, "%s", _("\tmpkg-menu\t\t\t\tshows the package selection menu\n"));

	fprintf(stream, "%s", _("\nRepository maintaining functions:\n"));
	fprintf(stream, "%s", _("\tmpkg-index\t\t\t\tcreate a repository index file \"packages.xml.xz\"\n"));
	fprintf(stream, "%s", _("\tmpkg-convert_dir <outp_dir>\t\tconvert whole directory (including sub-dirs) to MPKG format\n"));
	fprintf(stream, "%s", _("\tmpkg-convert <filename>\t\t\tconvert package to MPKG format\n"));
	fprintf(stream, "%s", _("\tmpkg-nativize [dir]\t\t\tsearch directory for non-native packages and convert it to MPKG format\n"));
	fprintf(stream, "%s", _("\tmpkg-gendeps <filename(s)>\t\tgenerate dependencies and import it into package. Also can be called by mpkg-gendeps2.\n"));
	fprintf(stream, "%s", _("\tmpkg-checklist [dir]\t\t\tcheck md5 sums of a package tree (requires a valid index in this dir)\n"));
	fprintf(stream, "%s", _("\tmpkg-sync <syncmap file>\t\tsyncronize repositories by sync map\n"));
	fprintf(stream, "%s", _("\tmpkg-buildup <filename>\t\t\tincrease spkg/tgz build\n"));
	fprintf(stream, "\n");

	if (is_error) return 1;
	return 0;
}