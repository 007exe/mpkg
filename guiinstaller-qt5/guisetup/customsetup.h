#ifndef CUSTOMSETUP_H_
#define CUSTOMSETUP_H_
#include <QtWidgets>

namespace Ui {
	class CustomSetupDialog;
};

class CustomSetupWidget: public QDialog {
	Q_OBJECT
	public:
		CustomSetupWidget(QWidget *parent = 0);
		~CustomSetupWidget();
	private:
		Ui::CustomSetupDialog *ui;
		
	public slots:
		void chooseFile();
		QString customURL();
		bool isMerge();
		void setMerge(bool);

};

#endif
