/*
ʵ����Ϸ�������棬������Ϸ���ܡ���Ϸ����˵������Ϸ��ʼ��ť�ȡ�

 QVBoxLayout* ui_start_menu;
 QPushButton* btn_start;
 QPushButton* btn_exit_in_start;

*/
#include "humanresourcemachine.h"
void humanresourcemachine::ui_start_menu_init() {

    ui_start_menu = new QVBoxLayout();
    //���ر������
    QString background_image_path = "../../img/start_menu_background.png";
    QPixmap background_image = QPixmap(background_image_path);
    QLabel* background_label = new QLabel;
    background_label->setPixmap(background_image);
    background_label->setScaledContents(true); // ͼƬ����Ӧ��С
    background_label->setAlignment(Qt::AlignCenter); // ʹͼƬ����
    ui_start_menu->addWidget(background_label);


    //���������Ͱ�ť�ĸ�����
    QWidget* containerWidget = new QWidget;
    containerWidget->setLayout(ui_level_select);


    // ˮƽ�������ڷ��ø�������ť�ͷ��ذ�ť
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->setAlignment(Qt::AlignCenter);

    const QString buttonStyles[] = {
        "background-color: #E67E5D; color: white;", // Start in Green
        "background-color: #7DBE6C; color: white;", // Exit in Red
        "background-color: #F39C12; color: white;" // continue in Yellow
    };
    // ����ʽ������ť
    //start
    btn_start = new QPushButton(tr("Start"));
    btn_start->setStyleSheet(buttonStyles[0]);
    buttonLayout->addWidget(btn_start);
    //exit
    btn_exit_in_start = new QPushButton(tr("Exit"));
    btn_exit_in_start->setStyleSheet(buttonStyles[1]);
    buttonLayout->addWidget(btn_exit_in_start);
    //conntinue
    btn_continue = new QPushButton(tr("Continue"));
    btn_continue->setStyleSheet(buttonStyles[2]);
    buttonLayout->addWidget(btn_continue);
    // ���ð�ť���
    buttonLayout->setSpacing(20);

    QWidget* buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background: transparent;"); // ���ñ���͸��
    buttonWidget->setGeometry(0, this->height() - 100, this->width(), 100); // ���ð�ť������λ��

    ui_start_menu->addWidget(buttonWidget);


    //connect signal and slot
    connect(btn_start, SIGNAL(clicked()), this, SLOT(start_game()));
    connect(btn_exit_in_start, SIGNAL(clicked()), this, SLOT(exit_game()));
    connect(btn_continue, SIGNAL(clicked()), this, SLOT(start_game_from_continue()));

    return;
}

void humanresourcemachine::start_game() {
    // �л����ؿ�ѡ�����
    if (stackedWidget != nullptr) {
        stackedWidget->setCurrentIndex(1);
    }
    else {
        // Handle the error appropriately
        std::cout << "stackedWidget is not initialized." << std::endl;
    }

}
void humanresourcemachine::start_game_from_continue() {
    if (player_progress->isCompleted) {
        QMessageBox::information(this, "Game Complete", "Congratulations! You have completed all levels.");
        // �л����ؿ�ѡ�����
        if (stackedWidget != nullptr) {
            stackedWidget->setCurrentIndex(1);
        }
        else {
            // Handle the error appropriately
            std::cout << "stackedWidget is not initialized." << std::endl;
        }
    }
    else {
        int current_level = player_progress->currentLevel;
        // �л�����ǰ�ؿ�
        enter_level(current_level);
    }
}

void humanresourcemachine::exit_game() {
    // �����˳�ȷ�϶Ի���
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // ������ҽ���
        on_game_exit(player_progress->currentLevel, player_progress->isCompleted);

        // �˳�Ӧ�ó���
        qApp->quit();
    }
}
