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
    standardize_blocks(*it);
    lb_robox->setText((*it)->text());
    //若手中谁是不空的，就标准化
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
    //机器人右转放到输出
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
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_spare_boxes[op]);
    QThread::msleep(sleep_time);
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
    standardize_blocks(lb_robox);
    QThread::msleep(sleep_time);
}

void QMainGame::standardize_blocks(QLabel* tmp)
{
    tmp->setAlignment(Qt::AlignCenter);
    QString backgroundColor = "lightblue";
    QString style = "QLabel {"
        "background-color: " + backgroundColor + ";"  // 统一背景颜色
        "border: 2px solid black;"                      // 黑色边框
        "border-radius: 5px;"                           // 圆角
        "padding: 5px; }";                             // 内边距
    tmp->setStyleSheet(style);  // 应用样式表
    int labelSize = 25;
    tmp->setFixedSize(labelSize, labelSize);
    return;
}

void QMainGame::standardize_code_blocks(QDragLabel* lb_code_block)
{
    int width = 150;  // 设定固定宽度
    int height = 40;  // 设定固定高度
    lb_code_block->setFixedSize(width, height);
    lb_code_block->setAlignment(Qt::AlignCenter);
    // 设置每个QLabel的样式
    QString labelStyle = "QLabel {"
        "background-color: #f0f0f0;"      // 背景色
        "border: 2px solid #0078d7;"      // 边框颜色和宽度
        "border-radius: 5px;"             // 圆角边框
        "padding: 10px;"                  // 内边距
        "font-size: 14px;"                // 字体大小
        "font-weight: bold;"              // 字体加粗
        "color: #333333;"                 // 字体颜色
        "}";
    // 应用样式到标签
    lb_code_block->setStyleSheet(labelStyle);
    lb_code_block->setAlignment(Qt::AlignCenter);
    return;
}
