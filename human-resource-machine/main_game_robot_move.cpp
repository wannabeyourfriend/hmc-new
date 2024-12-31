#pragma once
#include "humanresourcemachine.h"

void QMainGame::on_fail_exe()
{
    //����������fail��������fail֮�󣬴�robot_system�л��赲ʣ�¶�����emit��robot_system����Ҳ�᲻�����У����Բ�����emit
}
void QMainGame::on_inbox_exe(int op)
{
    qDebug() << "INBOX";
    qDebug() << "inbox:";
    for (int i = 0; i < lb_inboxes.size(); i++)
        qDebug() << lb_inboxes[i]->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    //��������תȡ���ŵ��Լ�ͷ�ϣ��ߵ��м�
    vector<QLabel*>::iterator it = lb_inboxes.begin();
    lb_robox->setText((*it)->text());
    lt_inbox->removeWidget(*it);
    delete (*it);
    lb_inboxes.erase(it);
    lt_inbox->update();
    lb_robox->update();
    //QThread::msleep(sleep_time);
}
void QMainGame::on_outbox_exe(int op)
{
    qDebug() << "OUTBOX";
    //��������ת�ŵ����
    QLabel* tmp = new QLabel(lb_robox->text());
    lb_outboxes.insert(lb_outboxes.begin(), tmp);
    lb_robox->setText("");
    lt_outbox->insertWidget(0, tmp);
    //QThread::msleep(sleep_time);
}
void QMainGame::on_add_exe(int op)
{
    qDebug() << "ADD";
    //�������ߵ��ո񲢼�
    qDebug() << "robox:";
	qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    int robox_num = stoi(lb_robox->text().toStdString());
    int spare_num = stoi(lb_spare_boxes[op]->text().toStdString());
    robox_num += spare_num;
    lb_robox->setText(to_string(robox_num).c_str());
    //QThread::msleep(sleep_time);
}
void QMainGame::on_sub_exe(int op)
{
    qDebug() << "SUB";
    //�������ߵ��ո񲢼�
    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    int robox_num = stoi(lb_robox->text().toStdString());
    int spare_num = stoi(lb_spare_boxes[op]->text().toStdString());
    robox_num -= spare_num;
    lb_robox->setText(to_string(robox_num).c_str());
    //QThread::msleep(sleep_time);
}
void QMainGame::on_copyto_exe(int op)
{
    qDebug() << "COPYTO";
    //�������ߵ��ո񲢸��Ƶ��ո�
    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    lb_spare_boxes[op]->setText(lb_robox->text());
    //QThread::msleep(sleep_time);
}
void QMainGame::on_copyfrom_exe(int op)
{
    qDebug() << "COPYFROM";
    //�������ߵ��ո�ȡ��
    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    lb_robox->setText(lb_spare_boxes[op]->text());
    //QThread::msleep(sleep_time);
}