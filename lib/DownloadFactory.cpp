// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "DownloadFactory.h"

void DownloadFactory::addMethodHandler(DownloadMethods method, IDownload* handler)
{
	library[ method ] = handler;
}

IDownload* DownloadFactory::getMethodHandler(DownloadMethods method)
{
	return library[ method ];
}
