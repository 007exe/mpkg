// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "thread.h"

Thread::Thread(mpkg *_db) {
	db = _db;
	printf("ideal thread count: %d\n", QThread::idealThreadCount());
}

Thread::~Thread() {}

void Thread::run() {
	int ret = db->commit();
	if (ret==0) emit workFinished(true);
	else emit workFinished(false);
}

