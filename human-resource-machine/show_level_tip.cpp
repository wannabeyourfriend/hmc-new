#pragma once
#include <QWidget>
#include "humanresourcemachine.h"
#include <QMessageBox>
#include <cstring>
#include <sstream>
#include <QTextEdit>
/*
�ӹؿ���.dat�ļ��ж�ȡ�ؿ���Ϣ���������ʾ��Ϣ
*/
/*
��1�أ���ӡ¥��
### ����һ���У��㽫����inbox outbox��Ϥ����������������ԭ�ⲻ���������������С�
2
1 2
2
1 2
0
2
inbox outbox
��2�أ����������
### ����һ���У��㽫Ҫʵ�������������������������a��b����Ҫ������ǵĲ�a-b��b-a���㽫��2���յ������Ĵ��м�����
8
3 8 5 1 -2 -2 9 -9
8
-5 5 4 -4 0 0 18 -18
3
8
inbox outbox copyfrom copyto add sub jump jumpifzero
��2.b�أ�
8
3 9 5 1 -2 -2 9 -9
8
-6 6 4 -4 0 0 18 -18
3
8
inbox outbox copyfrom copyto add sub jump jumpifzero
@��3�أ���ȹ�����
### ����һ���У��㽫Ҫʵ����ȹ�����������һ�����֣��㽫������������ظ������ε����֣��㽫��3���յ������Ĵ��м�����
8
6 2 7 7 -9 3 -3 -3
2
7 -3
3
8
inbox outbox copyfrom copyto add sub jump jumpifzero
��4�أ�
### ����һ���У��㽫ʵ��һ��ʵ�ֳ˷������㽫����������ֵĳ˻�������4���յ����洢�м���
9
1 3 5 9 8 7 3 4 4
4
15 72 21 16
4
8
inbox outbox copyfrom copyto add sub jump jumpifzero
*/
//void on_show_aimout(LEVEL* level, int aim_out_number) {
//    std::stringstream aim_out_info;
//    for (int i = 0; i < aim_out_number; i++) {
//        aim_out_info << level->get_aim_outs(i) << " ";
//    }
//
//    // ������Ϣ����ʾĿ�����
//    QMessageBox::information(nullptr, "Aim Out Information", QString::fromStdString(aim_out_info.str()));
//}


void on_close(QWidget* window) {
    window->close();
}

void humanresourcemachine::show_level_tip(int level_num) {
    string level_path = "../../levels/" + to_string(level_num) + ".dat";
    // ���� LEVEL ����ʹ��·�����������عؿ�����
    LEVEL* level = new LEVEL(level_path);
    // ��ȡ�ؿ���Ϣ
    int box_number = level->get_box_number();
    int spare_number = level->get_spare_number();
    int aim_out_number = level->get_aim_out_number();
    int available_instruction_number = level->get_available_instruction_number();

    // ��ȡ�ؿ��Ļ�ľ��Ŀ������Ϳ���ָ��
    std::stringstream box_info;
    for (int i = box_number - 1; i >= 0; i--) {
        box_info << level->get_boxes(i) << " ";
    }

    /*std::stringstream aim_out_info;
    for (int i = 0; i < aim_out_number; i++) {
        aim_out_info << level.get_aim_outs(i) << " ";
    }*/

    std::stringstream instruction_info;
    for (int i = 0; i < available_instruction_number; i++) {
        instruction_info << level->get_available_instructions(i) << " ";
    }

    // �ؿ�������Ϣ
    std::vector<std::string> instructions = {
        "In this level, you will use inbox and outbox to familiarize yourself with basic operations, where the input will be output unchanged.",
        "In this level, you will implement a subtractor: input two numbers, a and b, and output their differences a-b and b-a. You will have 2 empty spaces to store intermediate results.",
        "In this level, you will implement an equality filter. Input a series of numbers, and you will output the numbers that appear consecutively twice. You will have 3 empty spaces to store intermediate results.",
        "In this level, you will implement a multiplier. You will output the product of two numbers, and you will have 4 empty spaces to store intermediate results.\nNOTICE: You will be given a \"1\" first, and we will restrict the first element of every pair is positive."
    };

    // ������ʾ��Ϣ
    std::stringstream tip_message;
    tip_message << "Level " << level_num << " Information:\n";
    tip_message << "Instructions: " << instructions[level_num - 1] << "\n";
    tip_message << "Boxes: " << box_info.str() << "\n";
    tip_message << "Available Instructions: " << instruction_info.str() << "\n";
    tip_message << "Spare Spaces: " << spare_number << "\n";

    // ��������
    QWidget* window = new QWidget;
    window->setWindowTitle("Level Info");

    // �������ֹ�����
    QVBoxLayout* layout = new QVBoxLayout(window);

    // �����ı�������ʾ��ʾ��Ϣ
    QTextEdit* tipTextBox = new QTextEdit(window);
    tipTextBox->setText(QString::fromStdString(tip_message.str())); // ����ʾ��Ϣ�����ı���
    tipTextBox->setReadOnly(true); // ����Ϊֻ��ģʽ
    tipTextBox->setFont(QFont("Comic Sans MS", 12)); // ��������Ϊ΢���źڣ���СΪ12
    tipTextBox->setStyleSheet("background-color: #f0f0f0; border: 1px solid #cccccc; padding: 10px;");

    // �����رհ�ť
    QPushButton* closeButton = new QPushButton("OK", window);

    // ��ӿؼ�������
    layout->addWidget(tipTextBox);
    layout->addWidget(closeButton);

    // ���ӹرհ�ť���¼�������
    QObject::connect(closeButton, &QPushButton::clicked, [=]() { on_close(window); });

    // ���ò��ֲ���ʾ����
    window->setLayout(layout);
    window->show();
}