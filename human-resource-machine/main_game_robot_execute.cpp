#pragma once
#include "humanresourcemachine.h"
#include "progress.h"

void QMainGame::robot_execute() {
    string* instr_input = new string[kMAX_NUMBER_OF_INSTRUCTIONS];
    int instr_input_now = 0;
    int instr_input_num = lst_code->count();
    vector<pair< QListWidgetItem*, QListWidgetItem*> > lst_friends = lst_code->get_friends();
    for (int i = 0; i < instr_input_num; i++) {
        QListWidgetItem* item = lst_code->item(i);
        //qDebug() << item->text().toStdString();
        if (item && item->text().toStdString() != "") {
            instr_input[instr_input_now] = (item->text().toStdString());
            if (instr_input[instr_input_now] == "jump" || instr_input[instr_input_now] == "jumpifzero") {//�����ת����
                vector<pair<QListWidgetItem*, QListWidgetItem*> >::iterator it;
                for (it = lst_friends.begin(); it != lst_friends.end(); it++) {
                    if (it->first == item)
                        break;
                }
                if (it != lst_friends.end()) {
                    int smaller_count = lst_code->row(it->second);//����С�Ŀհ���
                    vector<pair<QListWidgetItem*, QListWidgetItem*> >::iterator it2;
                    for (it2 = lst_friends.begin(); it2 != lst_friends.end(); it2++) {
                        if (lst_code->row(it->second) > lst_code->row(it2->second))
                            smaller_count--;
                    }
                    instr_input[instr_input_now] += " " + to_string(smaller_count + 1);
                }
            }
            instr_input_now++;
        }
    }

	//����
	LEVEL* level = new LEVEL("../../levels/" + to_string(level_info.level_num) + ".dat");
	ROBOTSYSTEM* robot_system = new ROBOTSYSTEM(level);
    robot_system->instructions_input(instr_input_now, instr_input);
    int p = robot_system->execution();

    //�������ܼ�������
    //���ض���
    if (p > -1)//�������ش���
        robot_execute_animate(instr_input_now, instr_input, p);
    else {
        QMessageBox::information(this, tr("Error"), tr(("Illegal input on instruction " + to_string(-p) + "! Tryna burn the system?").c_str()));
    }

    //����������
    delete robot_system; // ��ʱlevelҲ�ᱻdelete������ΪҰָ�룬������
    delete[] instr_input;
    lt_inbox_init(level_info);
    lt_robot_n_spare_init(level_info);
    lt_outbox_init(level_info);
    sleep_time = kDEFAULT_SLEEP_TIME;
}

void QMainGame::robot_execute_animate(int instr_num, string* instrs, int stop_num) {
	int execute_count = 0;
    int execute_num = 0;
	for (; execute_num < instr_num; execute_num++) {
		if (instrs[execute_num] == "inbox") {
			if (lb_inboxes.empty()) // ���û�л�ľ��
                break;
			on_inbox_exe(-1);
		}
		else if (instrs[execute_num] == "outbox") {
			on_outbox_exe(-1);
		}
		else if (instrs[execute_num].substr(0, 4) == "add ") {
			on_add_exe(atoi(instrs[execute_num].substr(4, instrs[execute_num].length()).c_str()));
		}
		else if (instrs[execute_num].substr(0, 4) == "sub ") {
			on_sub_exe(atoi(instrs[execute_num].substr(4, instrs[execute_num].length()).c_str()));
		}
		else if (instrs[execute_num].substr(0, 9) == "copyfrom ") {
			on_copyfrom_exe(atoi(instrs[execute_num].substr(9, instrs[execute_num].length()).c_str()));
		}
		else if (instrs[execute_num].substr(0, 7) == "copyto ") {
			on_copyto_exe(atoi(instrs[execute_num].substr(7, instrs[execute_num].length()).c_str()));
		}
		else if (instrs[execute_num].substr(0, 5) == "jump ") {
			execute_num = atoi(instrs[execute_num].substr(5).c_str()) - 2; // �¸�ѭ����Ҫ++������Ҫ��-1
		}
		else if (instrs[execute_num].substr(0, 11) == "jumpifzero ") {
			if (lb_robox->text().toStdString() != "" && atoi(lb_robox->text().toStdString().c_str()) == 0) {
                execute_num = atoi(instrs[execute_num].substr(11).c_str()) - 2;
			}
		}
        execute_count++;
        if (stop_num != 0 && execute_count > stop_num - 2)
            break;
	}
    if (stop_num == 0) { // ������ʤ������������������ʤ��
        LEVEL* level = new LEVEL("../../levels/" + to_string(level_info.level_num) + "_2.dat");
        ROBOTSYSTEM* robot_system = new ROBOTSYSTEM(level);
        robot_system->instructions_input(instr_num, instrs);
        int p = robot_system->execution();
        if (p != 0) {
            QMessageBox::information(this, tr("Fail"), tr("Though you have done well in this sample, your code can't cover every aspect, and ends up wrong."));
            return;
        }
        delete robot_system;
        level = new LEVEL("../../levels/" + to_string(level_info.level_num) + "_3.dat");
        robot_system = new ROBOTSYSTEM(level);
        robot_system->instructions_input(instr_num, instrs);
        p = robot_system->execution();
        if (p != 0) {
            QMessageBox::information(this, tr("Fail"), tr("Though you have done well in this sample, your code can't cover every aspect, and ends up wrong."));
            return;
        }
        delete robot_system;
        QMessageBox::information(this, tr("Congrats"), tr("You've won!"));
        //ȷ��ͨ�أ������ź�p
        emit game_result(p, level_info.level_num);
    }
    else if (stop_num > 100000) {
        QMessageBox::information(this, tr("Loop"), tr("The program's stuck into a loop! Who creates the mess?"));
    }
    else {
        on_fail_exe();
        QMessageBox::information(this, tr("Fail"), tr("Unexpected output or operation, please retry."));
    }
}