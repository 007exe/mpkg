// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <mpkg/libmpkg.h>

int print_usage(int ret = 0) {
	fprintf(stderr, "mpkg-getopt: get specific option from mpkg config file\n");
	fprintf(stderr, "Usage:\nmpkg-getopt OPTION_NAME\n");
	return ret;
}

int main(int argc, char **argv) {
	if (argc!=2) return print_usage(1);
	cout << mConfig.getValue(argv[1]) << endl;
	return 0;
}
