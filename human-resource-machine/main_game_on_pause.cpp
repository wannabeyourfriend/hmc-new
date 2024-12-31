#pragma once
#include "humanresourcemachine.h"

void QMainGame::on_btn_back_clicked()
{
	ui_dlg_pause->accept();
}

void QMainGame::on_btn_restart_clicked()
{//���ﻹ��Ҫ�����еĽ����жϣ������³�ʼ����������Ҫʵ��stop_threads������������ÿ�����ڽ��еĽ��̽��б���
	stop_threads();
	lt_inbox_init(level_info);
	lt_robot_n_spare_init(level_info);
	lt_outbox_init(level_info);
	ui_dlg_pause->accept();
}

void QMainGame::on_btn_accl_clicked()
{
	if (sleep_time > 1)
		sleep_time = sleep_time / 2;
}

void QMainGame::on_btn_exit_clicked()
{

	//humanresourcemachine::ui_level_select_init();
	on_btn_restart_clicked();//�˳�ʱ�Զ����ùؿ��������ƺ�Ҳ����Ҫ��
	emit exit_signal();
	ui_dlg_pause->accept();
}