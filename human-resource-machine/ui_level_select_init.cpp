/*
�����ui_level_select_init�������ú������ڳ�ʼ��ѡ�ؽ��档

�ú���������3����ť���ֱ��Ӧ3�����𣬲������˲�ͬ����ɫ���ı���
*/
#include "humanresourcemachine.h"

void humanresourcemachine::ui_level_select_init()
{
    // �Ű棺ͼƬ��ҳ����Ϸ�����ť��ҳ���·��Ų�
    ui_level_select = new QVBoxLayout;

    //���屳��ͼƬ��ַ
    QString background_image_path = "../../img/level_select_background.png";
    // ���������ñ���ͼƬ
    QPixmap background_image = QPixmap(background_image_path);
    QLabel* background_label = new QLabel;
    background_label->setPixmap(background_image);
    background_label->setScaledContents(true); // ͼƬ����Ӧ��С
    background_label->setAlignment(Qt::AlignCenter); // ʹͼƬ����
    // ������ͼƬ��ӵ�ui_level_select������
    ui_level_select->addWidget(background_label, 0, Qt::AlignCenter);

    //���������Ͱ�ť�ĸ�����
    QWidget* containerWidget = new QWidget;
    containerWidget->setLayout(ui_level_select);



    // ˮƽ�������ڷ��ø�������ť�ͷ��ذ�ť
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    // ���尴ť����ɫ���ı�
    string levelText[kMAX_NUMBER_OF_LEVEL];
    for (int i = 0; i < kMAX_NUMBER_OF_LEVEL; i++) {
        levelText[i] = "Level " + to_string(i + 1);
    }
    const QString buttonStyles[] = {
        //����������ɫ���ɣ���ɫ��ʾ�ѽ����Ѿ�ͨ�أ���ɫ��ʾ���ڵĹؿ�����ɫ��ʾδ��������ɫΪ���˵İ�ť
        "background-color: #4CAF50; color: white;",//��ɫ
        "background-color: #2196F3; color: white;",//��ɫ
        "background-color: #9E9E9E; color: white;",//��ɫ
        "background-color: #F44336; color: white;" //��ɫ
    };

    // ��ȡ��󼶱���Ŀ��Ӳ����Ϊ3��
    const int levelCount = sizeof(levelText) / sizeof(levelText[0]);

    // �˳���ť
    QPushButton* btn_exit_in_game = new QPushButton("Back");
    btn_exit_in_game->setFixedSize(150, 50);
    btn_exit_in_game->setStyleSheet(buttonStyles[3]);

    // �����˳���ť���źŲ�
    connect(btn_exit_in_game, &QPushButton::clicked, this, &humanresourcemachine::exit_level);

    // ���˳���ť��ӵ�ˮƽ����
    buttonLayout->addWidget(btn_exit_in_game);


    // ���������ùؿ�ѡ��ť
    for (int i = 0; i < levelCount; ++i) {
        btn_levels[i] = new QPushButton(QString::fromStdString(levelText[i]));
        btn_levels[i]->setFixedSize(150, 50);
        //����progress��δ�����ؿ����б�Ǻͽ���
        if (i + 1 == player_progress->currentLevel && player_progress->isCompleted == false) { // ��ǰ��δͨ���Ĺؿ���Ϊ��ɫ
            //����Ϊ��ɫ
            btn_levels[i]->setStyleSheet(buttonStyles[1]);
        }
        else if (i + 1 > player_progress->currentLevel) {
            btn_levels[i]->setEnabled(false);  // �ؿ�δ���������ð�ť
            //����Ϊ��ɫ
            btn_levels[i]->setStyleSheet(buttonStyles[2]);
        }
        else {
            // ���ð�ť����ɫΪ��ɫ
            btn_levels[i]->setStyleSheet(buttonStyles[0]);
        }
        // �����źŲۣ�ʹ��ͨ�õķ�ʽ�򻯴���
        connect(btn_levels[i], &QPushButton::clicked, this, [this, i]() {
            enter_level(i + 1); // i��0��ʼ�����ݶ�Ӧ�ļ���
            });
        // ����ť��ӵ�������
        buttonLayout->addWidget(btn_levels[i]);
    }

    QWidget* buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setStyleSheet("background: transparent;"); // ���ñ���͸��
    buttonWidget->setGeometry(0, this->height() - 100, this->width(), 100); // ���ð�ť������λ��

    ui_level_select->addWidget(buttonWidget);

    setLayout(ui_level_select);
}

void humanresourcemachine::enter_level(int level_index)
{

    //���ﵯ���ؿ���ʾ������ʾ���ؿ�Ҫ�ﵽ�����Ŀ��
    show_level_tip(level_index);
    // ����level_index��1��ʼ�����Լ�1������ջλ��
    stackedWidget->setCurrentIndex(1 + level_index);
}

void humanresourcemachine::exit_level() {
    // �˳�ʱ���ص���ҳ��indexΪ0��
    stackedWidget->setCurrentIndex(0);
}
