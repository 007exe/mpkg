// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "globals.h"


bool _cdromMounted = false;
string CDROM_DEVICE;// = "/dev/hda";
string CDROM_MOUNTPOINT;// = "/mnt/cdrom";

bool setupMode = false;
bool msayState = false;
