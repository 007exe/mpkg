// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
/*
 *  loading.cpp
 *  manager
 *
 *  Created by aix 27249 on 2/16/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "db.h"

DatabaseBox::DatabaseBox()
{
	mDb = new mpkg;
	ui.setupUi(this);
}

mpkg *DatabaseBox::recreateDb()
{
	delete mDb;
	mDb = new mpkg;
	return mDb;
}

void DatabaseBox::commit()
{
	mDb->commit();
}
