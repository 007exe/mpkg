// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <mpkg/libmpkg.h>

int main(int argc, char **argv) {
	if (argc<2) return 1;
	string pkgname = argv[1];
	
	mpkg core;
	SQLRecord sqlSearch;
	PACKAGE_LIST pkgList;
	core.get_packagelist(sqlSearch, &pkgList);
	vector<PACKAGE *> alts = pkgList.getAllAlternatives(pkgname);
	for (size_t i=0; i<alts.size(); ++i) {
		cout << alts[i]->get_name() << " " << alts[i]->get_fullversion() << endl;
	}
	return 0;
}
