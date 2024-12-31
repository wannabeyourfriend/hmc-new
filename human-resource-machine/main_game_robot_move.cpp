#pragma once
#include "humanresourcemachine.h"

void QMainGame::on_fail_exe()
{
    //机器人做出fail动作；在fail之后，从robot_system中会阻挡剩下动作的emit；robot_system本身也会不再运行，所以不会有emit
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
    //机器人左转取件放到自己头上，走到中间
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
    //机器人右转放到输出
    QLabel* tmp = new QLabel(lb_robox->text());
    lb_outboxes.insert(lb_outboxes.begin(), tmp);
    lb_robox->setText("");
    lt_outbox->insertWidget(0, tmp);
    //QThread::msleep(sleep_time);
}
void QMainGame::on_add_exe(int op)
{
    qDebug() << "ADD";
    //机器人走到空格并加
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
    //机器人走到空格并减
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
    //机器人走到空格并复制到空格
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
    //机器人走到空格并取件
    qDebug() << "robox:";
    qDebug() << lb_robox->text();
    qDebug() << "spare:";
    for (int i = 0; i < level_info.spare_number; i++)
        qDebug() << lb_spare_boxes[i]->text();
    lb_robox->setText(lb_spare_boxes[op]->text());
    //QThread::msleep(sleep_time);
}