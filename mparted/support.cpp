// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "support.h"

string find_program(const string& name) {
	vector<string> paths;
	paths.push_back("/bin");
	paths.push_back("/usr/bin");
	paths.push_back("/usr/local/bin");

	paths.push_back("/sbin");
	paths.push_back("/usr/sbin");
	paths.push_back("/usr/local/sbin");

	for (size_t i=0; i<paths.size(); ++i) {
		if (FileExists(paths[i]+"/"+name)) return paths[i]+"/"+name;
	}
	return "";

}
