#include <mpkg/libmpkg.h>


int searchPackageID(string package_name, string &package_md5) {
	mpkg core;
	SQLTable pkgSearchResults;

	SQLRecord pkgSearch, pkgFields;
	pkgSearch.addField("package_name", package_name);
	pkgSearch.addField("package_installed", ST_INSTALLED);
	pkgSearch.setSearchMode(SEARCH_AND);

	pkgFields.addField("package_id");
	pkgFields.addField("package_md5");

	core.db->get_sql_vtable(pkgSearchResults, pkgFields, "packages", pkgSearch);

	if (pkgSearchResults.empty()) {
		return 0;
	}
	
	int package_id = atoi(pkgSearchResults.getValue(0, 0).c_str());
	package_md5 = pkgSearchResults.getValue(0, 1);
	return package_id;
}

int findConflicts(int package_id, string package_name, string package_md5 ) { 
	mpkg core;
	// First search: what we overwrote
	SQLTable conflictResults;
	SQLRecord conflictSearch, conflictFields;
	conflictSearch.addField("conflicted_package_id", package_id);
	core.db->get_sql_vtable(conflictResults, conflictFields, "conflicts", conflictSearch);

	//int fConflict_id = conflictResults.getFieldIndex("conflict_id");
	int fConflict_file_name = conflictResults.getFieldIndex("conflict_file_name");
	int fConflict_backup_file = conflictResults.getFieldIndex("backup_file");
	int fConflict_package_id = conflictResults.getFieldIndex("conflicted_package_id");
	string over_name;
	if (conflictResults.size()>0) fprintf(stderr, _("Package %s overwrites these files:\n"), package_name.c_str());
	else fprintf(stderr, _("Package didn't overwrite any other's files.\n"));
	for (size_t i=0; i<conflictResults.size(); ++i) {
		over_name = conflictResults.getValue(i, fConflict_backup_file);
		over_name = over_name.substr(0, over_name.find_first_of("/"));
		over_name = over_name.substr(0, over_name.size()-33);
		printf("%s:\t%s\n", conflictResults.getValue(i, fConflict_file_name).c_str(), over_name.c_str());
	}


	// Search reverse conflicts
	SQLRecord revConflictSearch;
	revConflictSearch.setEqMode(EQ_LIKE);
	revConflictSearch.addField("backup_file", package_name + "_" + package_md5 + "%");
	SQLTable revConflictResults;
	core.db->get_sql_vtable(revConflictResults, conflictFields, "conflicts", revConflictSearch);

	if (revConflictResults.getRecordCount()>0) {
		fprintf(stderr, _("\nOverwritten by others: \n"));
	}
	else return 0;

	int fRevConflict_package_id = revConflictResults.getFieldIndex("conflicted_package_id");
	int fRevConflict_file_name = revConflictResults.getFieldIndex("conflict_file_name");
	SQLRecord revPkgSearch;
	for (size_t i=0; i<revConflictResults.size(); ++i) {
		revPkgSearch.addField("package_id", revConflictResults.getValue(i, fRevConflict_package_id));
	}
	revPkgSearch.setSearchMode(SEARCH_IN);
	PACKAGE_LIST revList;
	core.get_packagelist(revPkgSearch, &revList);
	PACKAGE *p;

	for (size_t i=0; i<revConflictResults.size(); ++i) {
		p = revList.getPackageByIDPtr(atoi(revConflictResults.getValue(i, fRevConflict_package_id).c_str()));
		if (!p) over_name = "(unknown)";
		else over_name = p->get_name();
		printf("%s:\t%s\n", revConflictResults.getValue(i, fRevConflict_file_name).c_str(), over_name.c_str());
	}
	return 0;
}

int main(int argc, char **argv) {
	setlocale(LC_ALL, "");
	bindtextdomain( "mpkg", "/usr/share/locale");
	textdomain("mpkg");
	if (argc<2) {
		fprintf(stderr, _("Package name not specified"));
		return 1;
	}
	string package_name = argv[1];
	string package_md5;
	int package_id = searchPackageID(package_name, package_md5);
	if (package_id<=0) {
		fprintf(stderr, _("Package %s not found or not installed\n"), package_name.c_str());
		return 1;
	}
	findConflicts(package_id, package_name, package_md5);
	return 0;
}

