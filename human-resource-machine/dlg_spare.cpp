#pragma once
#include "humanresourcemachine.h"

QDialogSpare::QDialogSpare(int spares_number)
{
	setWindowTitle("Select a Spare");
	setModal(true);
	setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
	spare_no = 1;
	this->spares_number = spares_number;
	lt_dlg_spare = new QVBoxLayout();
	btn_spares = new QPushButton * [spares_number];
	for (int i = 0; i < spares_number; i++) {
		btn_spares[i] = new QPushButton(("Spare " + to_string(i)).c_str());
		lt_dlg_spare->addWidget(btn_spares[i]);
		connect(btn_spares[i], &QPushButton::clicked, this, &QDialogSpare::onButtonClicked);
	}
	setLayout(lt_dlg_spare);
}

int QDialogSpare::get_spare_no()
{
	return spare_no;
}

void QDialogSpare::onButtonClicked() {
	for (int i = 0; i < spares_number; i++) {
		if (sender() == btn_spares[i]) {
			spare_no = i;
			accept();
			return;
		}
	}
	spare_no = 1;
	accept();
}
