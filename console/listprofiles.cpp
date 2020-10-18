// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <mpkg/libmpkg.h>

int main(int , char **) {
	vector<string> pList = getDirectoryList("/etc/mpkg/profiles");
	for (unsigned int i=0; i<pList.size(); ++i) {
		printf("%s\n", pList[i].c_str());
	}
	return 0;
}
