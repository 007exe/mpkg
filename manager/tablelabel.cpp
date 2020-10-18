// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "tablelabel.h"

TableLabel::TableLabel(QTableWidget *table)
{
	packageTable=table;
}

void TableLabel::mousePressEvent(QMouseEvent *event)
{
	packageTable->setCurrentCell(row,1);
}


ListLabel::ListLabel(QListWidget *list, int rowID)
{
	catList=list;
	row=rowID;
}

void ListLabel::mousePressEvent(QMouseEvent *event)
{
	catList->setCurrentRow(row);
}
