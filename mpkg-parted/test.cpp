// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "mpkg-parted.h"
#include <iostream>
int main() {
/*	vector<pEntry> plist = getPartitionList();
	for (size_t i=0; i<plist.size(); ++i) {
		cout << plist[i].devname << endl;
	}*/
	
	ped_device_probe_all_workaround();
	PedDevice *tmpDevice=NULL;
	PedDisk *tmpDisk=NULL;
	PedPartition *tmpPartition=NULL;

	tmpDevice = ped_device_get_next(tmpDevice);
	ped_disk_probe(tmpDevice);
	tmpDisk = ped_disk_new(tmpDevice);
	return 0;
}
