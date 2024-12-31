#pragma once
#include "humanresourcemachine.h"

void QMainGame::ui_dlg_pause_init() {
	ui_dlg_pause = new QDialog();
	lt_pause = new QHBoxLayout();
	ui_dlg_pause->setLayout(lt_pause);
	ui_dlg_pause->setWindowTitle("Pause");
	ui_dlg_pause->setModal(true);
	ui_dlg_pause->resize(300, 100);
	ui_dlg_pause->setWindowFlags(Qt::WindowStaysOnTopHint);
	ui_dlg_pause->setAttribute(Qt::WA_DeleteOnClose);
	ui_dlg_pause->setWindowIcon(QIcon("../../img/pause.png")); // ȷ������һ����Ϊ"pause.png"��ͼ���ļ�
	ui_dlg_pause->setWindowIconText("Pause"); // ���ô���ͼ��ͱ���
	ui_dlg_pause->setFixedSize(300, 100);
	ui_dlg_pause->setWindowOpacity(0.5);
	ui_dlg_pause->setContentsMargins(10, 10, 10, 10);

	btn_back = new QPushButton("Back");
	btn_restart = new QPushButton("Clear");
	btn_accl = new QPushButton("Accl");
	btn_exit_in_pause = new QPushButton("Exit");
	lt_pause->addWidget(btn_back);
	lt_pause->addWidget(btn_restart);
	lt_pause->addWidget(btn_accl);
	lt_pause->addWidget(btn_exit_in_pause);

	connect(btn_back, &QPushButton::clicked, this, &QMainGame::on_btn_back_clicked);
	connect(btn_restart, &QPushButton::clicked, lst_code, &QDragListWidget::on_btn_restart_clicked);
	connect(btn_restart, &QPushButton::clicked, this, &QMainGame::on_btn_restart_clicked);
	connect(btn_accl, &QPushButton::clicked, this, &QMainGame::on_btn_accl_clicked);
	connect(btn_exit_in_pause, &QPushButton::clicked, this, &QMainGame::on_btn_exit_clicked);
}

void QMainGame::stop_threads()
{

}

void QMainGame::on_btn_pause_clicked() {
	ui_dlg_pause_init();
	ui_dlg_pause->show();
}