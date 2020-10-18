// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "progresswidget.h"
#include "ui_progresswidget.h"
#include <mpkg/libmpkg.h>
#include <QMessageBox>
ProgressWidget *progressWidgetPtr;
void updateProgressData(ItemState a) {
	progressWidgetPtr->updateData(a);
}

ProgressWidget::ProgressWidget(QWidget *parent): QWidget(parent), ui(new Ui::ProgressWidgetClass) {
	ui->setupUi(this);
	ui->totalProgressBar->setMaximum(100);
	qRegisterMetaType<ItemState>("ItemState");
	connect(this, SIGNAL(callUpdateData(const ItemState &)), this, SLOT(updateDataProcessing(const ItemState &)));
	connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelActions()));
}

ProgressWidget::~ProgressWidget() {
}

void ProgressWidget::updateData(const ItemState& a) {
	emit callUpdateData(a);
}

void ProgressWidget::updateDataProcessing(const ItemState &a) {
	ui->label->setText(QString::fromStdString(a.name + ": " + a.currentAction));
	if (a.totalProgress>=0 && a.totalProgress<=100) ui->totalProgressBar->setValue(a.totalProgress);
	else if (a.totalProgress<0) ui->totalProgressBar->setValue(0);
}

void ProgressWidget::cancelActions() {
	if (QMessageBox::warning(this, tr("Please confirm abort"), tr("Are you sure you want to abort current operations?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No)==QMessageBox::Yes) {
		_abortActions = true;
	}
}
