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

	fprintf(stream, "%s", _("\nUsage: %s [options] ACTION [package] [package] ...\n"), cmd.c_str());
	fprintf(stream, "%s", _("Common options:\n"));
	fprintf(stream, "%s", _("\t-h    --help              show this help\n"));
	fprintf(stream, "%s", _("\t-v    --verbose           be verbose\n"));
	fprintf(stream, "%s", _("\t-g    --dialog            use dialog mode UI\n"));
	fprintf(stream, "%s", _("\t-d    --force-dep         interpret dependency errors as warnings\n"));
	fprintf(stream, "%s", _("\t-z    --no-dep            totally ignore dependencies existance\n"));
	fprintf(stream, "%s", _("\t-f    --force-conflicts   do not perform file conflict checking\n"));
	fprintf(stream, "%s", _("\t-m    --no-md5            do not check package integrity on install\n"));
	fprintf(stream, "%s", _("\t-k    --force-essential   allow removing essential packages\n"));
	fprintf(stream, "%s", _("\t-D    --download-only     just download packages, do not install\n"));
	fprintf(stream, "%s", _("\t-r    --repair            repair damaged packages (use with \"check\" keyword)\n"));
	fprintf(stream, "%s", _("\t-i    --installed         show only installed packages (use with \"list\" keyword)\n"));
	fprintf(stream, "%s", _("\t-a    --available         show only available packages (use with \"list\" keyword)\n"));
	fprintf(stream, "%s", _("\t-l    --filelist          show file list for package (with \"show\" keyword)\n"));
	fprintf(stream, "%s", _("\t-y    --noconfirm         don't ask confirmation\n"));
	fprintf(stream, "%s", _("\t-q    --noreset           don't reset queue at start\n"));
	fprintf(stream, "%s", _("\t-N    --nodepgen          don't generate dependencies on package building\n"));
	fprintf(stream, "%s", _("\t-w    --no_buildcache     don't use source cache when building packages\n")); 
	fprintf(stream, "%s", _("\t-c    --no_resume         disable download resuming\n"));
	fprintf(stream, "%s", _("\t-b    --cleartags         clear all other tags before tagging\n"));
	fprintf(stream, "%s", _("\t-F    --fork              detach from terminal and run in background\n"));
	fprintf(stream, "%s", _("\t-Q    --enqueue           only enqueue actions, do not perform\n"));
	fprintf(stream, "%s", _("\t-V    --enableversions    enable versioning in install lists\n"));
	fprintf(stream, "%s", _("\t-R    --index-filelist    create file list while indexing\n"));
	fprintf(stream, "%s", _("\t-M    --md5index          add md5 sums for each file in filelist\n"));
	fprintf(stream, "%s", _("\t-S    --sysroot=<DIR>     set temporary system root\n"));
	fprintf(stream, "%s", _("\t-t    --conf=CONFIG_FILE  set temporary config file\n"));
	fprintf(stream, "%s", _("\t-A    --download-to=<DIR> download packages to specified directory\n"));
	fprintf(stream, "%s", _("\t-W    --enable-spkg-index enable spkg indexing (otherwise, it will be skipped)\n"));
	fprintf(stream, "%s", _("\t-L    --linksonly         on install/upgradeall, show only download links and exit\n"));
	fprintf(stream, "%s", _("\t-P    --noaaa             try to avoid aaa_elflibs in dependency generation (for gendeps2)\n"));
	fprintf(stream, "%s", _("\t-G    --keep-deps         do not replace deps in package, add to them instead (for gendeps2)\n"));
	fprintf(stream, "%s", _("\t-C    --enable-cache      enable cached indexing\n"));
	fprintf(stream, "%s", _("\t-K    --skip-deprecated   while sync, skip deprecated packages\n"));
	fprintf(stream, "%s", _("\t-s    --keep-symlinks     keep symlinks in archive instead of moving it to doinst.sh\n"));
	fprintf(stream, "%s", _("\t-E    --exclusion-list=FILENAME   Exclude paths from being checked by gendeps2\n"));
	fprintf(stream, "%s", _("\t-e    --arch=ARCH         temporarily override architecture. Valid options is x86_64 and x86.\n"));
	fprintf(stream, "%s", _("\t-Y    --resync            forces deep database update (takes longer time, but rebuilds all package metadata)\n"));
	fprintf(stream, "%s", _("\t-X    --skip=PKG1,PKG2... Skip specified packages in upgradeall or listupdates\n"));


	fprintf(stream, "%s", _("\nAvailable commands:\n"));
	fprintf(stream, "%s", _("\tmpkg-version                            show mpkg version\n"));
	fprintf(stream, "%s", _("\tmpkg-install PACKAGE_NAME | FILENAME    install package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-upgradeall                         upgrade all installed packages\n"));
	fprintf(stream, "%s", _("\tmpkg-reinstall PACKAGE_NAME             reinstall package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-remove PACKAGE_NAME                remove selected package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-purge PACKAGE_NAME                 purge selected package(s)\n"));
	fprintf(stream, "%s", _("\tmpkg-installgroup GROUP_NAME            install all the packages from group\n"));
	fprintf(stream, "%s", _("\tmpkg-removegroup GROUP_NAME             remove all the packages from group\n"));

	fprintf(stream, "%s", _("\tmpkg-listupdates                        list available updates\n"));
	fprintf(stream, "%s", _("\tmpkg-show PACKAGE_NAME                  show info about package\n"));
	fprintf(stream, "%s", _("\tmpkg-update                             update packages info\n"));
	fprintf(stream, "%s", _("\tmpkg-list                               show the list of all packages in database\n"));
	fprintf(stream, "%s", _("\tmpkg-listgroup GROUP_NAME               show the list of packages belonged to group\n"));
	fprintf(stream, "%s", _("\tmpkg-listgroups                         show the list of all existing groups\n"));
	fprintf(stream, "%s", _("\tmpkg-whodepend PACKAGE_NAME             show what packages depends on this one\n"));

	fprintf(stream, "%s", _("\tmpkg-filesearch FILE_NAME               look for owner of the file in installed packages (LIKE mode).\n"));
	fprintf(stream, "%s", _("\tmpkg-which FILE_NAME                    look for owner of the file in installed packages (EQUAL mode).\n"));
	fprintf(stream, "%s", _("\tmpkg-list_rep                           list enabled repositories\n"));
	fprintf(stream, "%s", _("\tmpkg-add_rep URL                        add repository\n"));
	fprintf(stream, "%s", _("\tmpkg-delete_rep REPOSITORY_NUMBER       delete Nth repository\n"));
	fprintf(stream, "%s", _("\tmpkg-enable_rep REPOSITORY_NUMBER       enable Nth repository\n"));
	fprintf(stream, "%s", _("\tmpkg-disable_rep REPOSITORY_NUMBER      disable Nth repository\n"));
	fprintf(stream, "%s", _("\tmpkg-getrepositorylist [LIST_URL]       get the list of repositories from server (by default, from packages.agilialinux.ru)\n"));
	fprintf(stream, "%s", _("\tmpkg-installfromlist FILE_NAME          install using file with list of items\n"));
	fprintf(stream, "%s", _("\tmpkg-exportinstalled [FILE_NAME]        export list of installed packages to file or stdout\n"));
	fprintf(stream, "%s", _("\tmpkg-reset                              reset queue\n"));
	fprintf(stream, "%s", _("\tmpkg-show_queue                         show queue\n"));
	fprintf(stream, "%s", _("\tmpkg-commit                             commit queued actions\n"));
	fprintf(stream, "%s", _("\tmpkg-search PATTERN                     search package by name containing PATTERN\n"));
	fprintf(stream, "%s", _("\tmpkg-searchdescription PATTERN          search package by description containing PATTERN\n"));
	fprintf(stream, "%s", _("\tmpkg-clean                              remove all downloaded packages from cache\n"));
	fprintf(stream, "%s", _("\tmpkg-check [package_name]               checks installed package(s) for missing files. Use -r flag to to repair\n"));
	fprintf(stream, "%s", _("\tmpkg-checkdeps URL                      checks specified repository if all dependencies can be resolved within same repository"));


	fprintf(stream, "%s", _("\tmpkg-checklibdeps [PACKAGE_NAME]        checks installed package(s) for broken binary dependencies.\n"));
	fprintf(stream, "%s", _("\tmpkg-altlist			    shows all alternatives in database\n"));
	fprintf(stream, "%s", _("\tmpkg-altshow PACKAGE_NAME		    shows all alternative branches of specified package\n")); 
	fprintf(stream, "%s", _("\tmpkg-conflicts PACKAGE_NAME		    checks package for file conflicts (files with same names and paths, but from different packages)\n")); 
	fprintf(stream, "%s", _("\tmpkg-deleteprofile PROFILE_NAME	    delete repository profile\n")); 
	fprintf(stream, "%s", _("\tmpkg-depgraph URL OUTPUT_FILE           generates dot file with dependency graph of specified package\n")); 
	fprintf(stream, "%s", _("\tmpkg-deporder FILENAME	            reads package names from specified file, and generates it's dependency order\n")); 
	fprintf(stream, "%s", _("\tmpkg-fixdeps		            fixes broken dependencies of installed packages\n")); 
	fprintf(stream, "%s", _("\tmpkg-listprofiles		            shows list of known repository profiles\n")); 
	fprintf(stream, "%s", _("\tmpkg-maintainer OPTIONS [NAME] [EMAIL]  get/set maintainer name and email (for mkpkg)\n")); 
	fprintf(stream, "%s", _("\tmpkg-quicklist		            shows machine-readable list of all installed packages. Used primarily in bash-completion.\n")); 
	fprintf(stream, "%s", _("\tmpkg-rollback [TRANSACTION_ID] [PACKAGE_NAME]  transactions rollback. Rolls back latest transaction. See command help for details.\n")); 
	fprintf(stream, "%s", _("\tmpkg-saveprofile PROFILE_NAME	    saves current repository set under specified profile name.\n")); 
	fprintf(stream, "%s", _("\tmpkg-setmeta PATH | FILENAME [OPTIONS]  a tool to modify package metadata. See command help for details\n")); 
	fprintf(stream, "%s", _("\tmpkg-setprofile PROFILE_NAME	    loads specified repository set profile.\n")); 
	fprintf(stream, "%s", _("\tmpkg-spkg2abuild FILENAME		    converts spkg file to ABUILD tree.\n")); 
	fprintf(stream, "%s", _("\tmpkg-transactions			    shows all package transactions.\n")); 
	fprintf(stream, "%s", _("\tmpkg-validate PATH | FILENAME	    validates package integrity and some guidelines.\n")); 




	fprintf(stream, "%s", _("\nInteractive options:\n"));
	fprintf(stream, "%s", _("\tmpkg-menu                      shows the package selection menu\n"));

	fprintf(stream, "%s", _("\nRepository maintaining functions:\n"));
	fprintf(stream, "%s", _("\tmpkg-index                     create a repository index file \"packages.xml.xz\"\n"));
	fprintf(stream, "%s", _("\tmpkg-convert_dir <outp_dir>    convert whole directory (including sub-dirs) to MPKG format\n"));
	fprintf(stream, "%s", _("\tmpkg-convert <filename>        convert package to MPKG format\n"));
	fprintf(stream, "%s", _("\tmpkg-nativize [dir]            search directory for non-native packages and convert it to MPKG format\n"));
	fprintf(stream, "%s", _("\tmpkg-gendeps <filename(s)>     generate dependencies and import it into package. Also can be called by mpkg-gendeps2.\n"));
	fprintf(stream, "%s", _("\tmpkg-checklist [dir]           check md5 sums of a package tree (requires a valid index in this dir)\n"));
	fprintf(stream, "%s", _("\tmpkg-sync <syncmap file>       syncronize repositories by sync map\n"));
	fprintf(stream, "%s", _("\tmpkg-buildup <filename>        increase spkg/tgz build\n"));
	fprintf(stream, "\n");


	if (is_error) return 1;
	return 0;
}