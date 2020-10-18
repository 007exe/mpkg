// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "raidtool.h"

int main(int argc, char **argv) {
	dialogMode = true;
	cdromList = getCdromList();
	runRaidTool();
}
