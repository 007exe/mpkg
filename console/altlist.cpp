// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <mpkg/libmpkg.h>

int main(int, char **) {
	mpkg core;
	SQLRecord sqlSearch;
	PACKAGE_LIST pkgList;
	core.get_packagelist(sqlSearch, &pkgList);
	vector<string> alt = pkgList.getAlternativeList(true);
	for (size_t i=0; i<alt.size(); ++i) {
		cout << alt[i] << endl;
	}
	return 0;
}
