// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "help.h"
#include "ui_help.h"

HelpForm::HelpForm(QWidget *parent) : QWidget(parent), ui(new Ui::HelpFormClass)  {
	ui->setupUi(this);
	connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

HelpForm::~HelpForm() {
}

void HelpForm::loadText(const QString& text) {
	ui->textBrowser->setText(text);
}
