// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <mpkg/libmpkg.h>
int print_usage() {
	fprintf(stderr, "%s",_("MPKG Package System: save repository profile\n"));
	fprintf(stderr, "%s",_("Usage: mpkg-saveprofile PROFILE_NAME\n"));
	return 1;
}

int main(int argc, char **argv) {
	if (argc<2) return print_usage();
	string profile_name = string(argv[1]);
	if (profile_name.find_first_of("/\n")!=std::string::npos) {
		fprintf(stderr, "%s",_("Profile name is invalid\n"));
		return 2;
	}
	mpkg *core = new mpkg;
	vector<string> repList = core->get_repositorylist();
	system("mkdir -p /etc/mpkg/profiles");
	WriteFileStrings("/etc/mpkg/profiles/" + profile_name, repList);
	delete core;
	return 0;
}
