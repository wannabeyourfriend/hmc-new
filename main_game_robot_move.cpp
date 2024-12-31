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
    standardize_blocks(*it);
    lb_robox->setText((*it)->text());
    //������˭�ǲ��յģ��ͱ�׼��
    if (lb_robox->text() != "")
        standardize_blocks(lb_robox);
    lt_inbox->removeWidget(*it);
    delete (*it);
    lb_inboxes.erase(it);
    lt_inbox->update();
    lb_robox->update();
    lt_game->update();
    QThread::msleep(sleep_time);
}
void QMainGame::on_outbox_exe(int op)
{
    qDebug() << "OUTBOX";
    //��������ת�ŵ����
    QLabel* tmp = new QLabel(lb_robox->text());
    standardize_blocks(tmp);
    lb_outboxes.insert(lb_outboxes.begin(), tmp);
    lb_robox->setText("");
    lb_robox->setStyleSheet("");
    lt_outbox->insertWidget(0, tmp);

    lt_inbox->update();
    lb_robox->update();
    lt_game->update();
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_spare_boxes[op]);
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
}

void QMainGame::standardize_blocks(QLabel* tmp)
{
    tmp->setAlignment(Qt::AlignCenter);
    QString backgroundColor = "lightblue";
    QString style = "QLabel {"
        "background-color: " + backgroundColor + ";"  // ͳһ������ɫ
        "border: 2px solid black;"                      // ��ɫ�߿�
        "border-radius: 5px;"                           // Բ��
        "padding: 5px; }";                             // �ڱ߾�
    tmp->setStyleSheet(style);  // Ӧ����ʽ��
    int labelSize = 25;
    tmp->setFixedSize(labelSize, labelSize);
    return;
}

void QMainGame::standardize_code_blocks(QDragLabel* lb_code_block)
{
    int width = 150;  // �趨�̶����
    int height = 40;  // �趨�̶��߶�
    lb_code_block->setFixedSize(width, height);
    lb_code_block->setAlignment(Qt::AlignCenter);
    // ����ÿ��QLabel����ʽ
    QString labelStyle = "QLabel {"
        "background-color: #f0f0f0;"      // ����ɫ
        "border: 2px solid #0078d7;"      // �߿���ɫ�Ϳ��
        "border-radius: 5px;"             // Բ�Ǳ߿�
        "padding: 10px;"                  // �ڱ߾�
        "font-size: 14px;"                // �����С
        "font-weight: bold;"              // ����Ӵ�
        "color: #333333;"                 // ������ɫ
        "}";
    // Ӧ����ʽ����ǩ
    lb_code_block->setStyleSheet(labelStyle);
    lb_code_block->setAlignment(Qt::AlignCenter);
    return;
}
