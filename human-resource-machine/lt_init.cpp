#include "humanresourcemachine.h"

void QMainGame::lt_inbox_init(LevelInfo level_info) {
    if (lt_inbox == NULL)
        lt_inbox = new QVBoxLayout(this);
    for (int i = 0; i < lb_inboxes.size(); i++)
        delete lb_inboxes[i];
    lb_inboxes.clear();
    for (int i = 0; i < level_info.box_number; i++) {
        QLabel* tmp = new QLabel(to_string(level_info.boxes[level_info.box_number - i - 1]).c_str());//level�Ƿ���洢�������ٷ���õ�����
        lb_inboxes.push_back(tmp);
        lt_inbox->addWidget(tmp);
    }
}

void QMainGame::lt_robot_n_spare_init(LevelInfo level_info) {
    lt_robot_init();
    lt_space_init(level_info);
    if (lt_robot_n_spare == NULL)
        lt_robot_n_spare = new QVBoxLayout();
    lt_robot_n_spare->addLayout(lt_robot);
    lt_robot_n_spare->addLayout(lt_spare);
}

void QMainGame::lt_outbox_init(LevelInfo level_info) {
    if (lt_outbox == NULL)
        lt_outbox = new QVBoxLayout();
    for (int i = 0; i < lb_outboxes.size(); i++)
        delete lb_outboxes[i];
    lb_outboxes.clear();
}

void QMainGame::lt_code_choice_init(LevelInfo level_info) {
    lt_code_choice = new QVBoxLayout();
    for (int i = 0; i < level_info.available_instruction_number; i++) {
        lb_code_choices[i] = new QDragLabel();
        lb_code_choices[i]->setText(level_info.available_instructions[i].c_str());
        lt_code_choice->addWidget(lb_code_choices[i]);
    }
}

void QMainGame::lt_code_init(LevelInfo level_info) {
    lt_code = new QVBoxLayout();
    lt_pause_init();
    lt_code->addLayout(lt_pause);
    lst_code = new QDragListWidget(level_info.spare_number);
    lt_code->addWidget(lst_code);
    btn_run = new QPushButton("RUN");
    lt_code->addWidget(btn_run);
    connect(btn_run, SIGNAL(clicked()), this, SLOT(robot_execute()));
    for (int i = 0; i < level_info.available_instruction_number; i++) {
        connect(lb_code_choices[i], &QDragLabel::labelDragged, lst_code, &QDragListWidget::onLabelDragged);
    }
    connect(btn_pause_in_game, SIGNAL(clicked()), this, SLOT(on_btn_pause_clicked()));
}

void QMainGame::lt_robot_init() {
    if (lb_robox != NULL)
        delete lb_robox;
    lb_robox = new QLabel();
    if (wdg_robot_pic != NULL)
        delete wdg_robot_pic;
    wdg_robot_pic = new BackgroundWidget("../../img/robot.png");
    if (lt_robot != NULL)
        delete lt_robot;
    lt_robot = new QVBoxLayout();
    lt_robot->addWidget(lb_robox);
    lt_robot->addWidget(wdg_robot_pic);
}

void QMainGame::lt_space_init(LevelInfo level_info) {
    if (lt_spare != NULL)
        delete lt_spare;
    lt_spare = new QHBoxLayout();
    for (int i = 0; i < level_info.spare_number; i++) {
        if (lb_spare_boxes[i] != NULL)
            delete lb_spare_boxes[i];
        lb_spare_boxes[i] = new QLabel();
        lt_spare->addWidget(lb_spare_boxes[i]);
    }
}

void QMainGame::lt_pause_init() {
    lt_pause = new QHBoxLayout();
    btn_pause_in_game = new QPushButton();
    btn_pause_in_game->setIcon(QIcon("../../img/pause.png")); // ȷ������һ����Ϊ"pause.png"��ͼ���ļ�
    btn_pause_in_game->setToolTip("��ͣ"); // ���������ͣʱ����ʾ��Ϣ
    lt_pause->addStretch(1);
    lt_pause->addWidget(btn_pause_in_game);
}