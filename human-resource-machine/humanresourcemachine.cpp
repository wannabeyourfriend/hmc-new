#include "humanresourcemachine.h"
#include "progress.h"
humanresourcemachine::humanresourcemachine(QWidget* parent)
	: QMainWindow(parent)
{
	// ���������ڵı����Ĭ�ϴ�С
	setWindowTitle("Human Resource Machine");
	setFixedSize(800, 600);  // ���贰�ڴ�СΪ 800x600 

	// ���� QStackedWidget ������Ϊ���Ĳ���
	stackedWidget = new QStackedWidget(this);
	setCentralWidget(stackedWidget);

	// ��ʼ�����ȹ���
	player_progress = new PlayerProgress();
	player_progress->loadProgress("../../log/player_progress.json");
	//��QMessage���һ��player_progress������ʲô��Ϣ
	//QMessageBox::information(this, "Player Information", "Name: " + player_progress->name + "\nAge: " + QString::number(player_progress->age) + "\nGender: " + player_progress->gender + "\nLevel: " + QString::number(player_progress->currentLevel) + "\nCompleted: " + QString::number(player_progress->isCompleted));

	QWidget* startMenuPage = new QWidget();
	QWidget* levelSelectPage = new QWidget();


	// ��ʼ������ҳ��� UI ����
	ui_start_menu_init();
	ui_level_select_init();

	for (int i = 0; i < kMAX_NUMBER_OF_LEVEL; i++) {
		ui_main_games[i] = new QMainGame(i + 1, this);
		connect(ui_main_games[i], &QMainGame::exit_signal, this, &humanresourcemachine::start_game);
		//pֵ���ӵ����̹�������
		connect(ui_main_games[i], &QMainGame::game_result, this, &humanresourcemachine::update_progress);
		//��levelselectҳ��ˢ�º������ӵ�����ֵ�İ����ź�
		connect(ui_main_games[i], &QMainGame::exit_signal, this, &humanresourcemachine::ui_level_select_re_init);
	}

	// ������ҳ��� UI ��������Ϊ���ֲ����õ�����ҳ����
	startMenuPage->setLayout(ui_start_menu);
	levelSelectPage->setLayout(ui_level_select);

	// ������ҳ����ӵ� QStackedWidget ��
	stackedWidget->addWidget(startMenuPage);
	stackedWidget->addWidget(levelSelectPage);
	for (int i = 0; i < kMAX_NUMBER_OF_LEVEL; i++)
		stackedWidget->addWidget(ui_main_games[i]);

	stackedWidget->setCurrentIndex(0);  // ��ʾ��ʼҳ��
}

humanresourcemachine::~humanresourcemachine()
{
	delete player_progress;
}

void humanresourcemachine::on_game_exit(int level, bool completed) {
	// ������ҵĽ���
	player_progress->currentLevel = level + 1;  // ����ؿ���1��ʼ��level��0������
	player_progress->isCompleted = completed;

	// �������
	player_progress->saveProgress("../../log/player_progress.json");

}

void humanresourcemachine::ui_level_select_re_init()
{
	// ��ʼ��һ��ָ��ָ��stackedWidget�еĵڶ���ҳ�棬���ؿ�ѡ��ҳ��
	QWidget* oldWidget = stackedWidget->widget(1);
	// �Ƴ��ɿؼ�
	stackedWidget->removeWidget(oldWidget);
	// ��ʼ���¿ؼ�
	ui_level_select_init();
	QWidget* newWidget = new QWidget(stackedWidget); // �����¿ؼ�
	newWidget->setLayout(ui_level_select); // �����¿ؼ��Ĳ���

	stackedWidget->insertWidget(1, newWidget);
	// �л����¿ؼ�
	stackedWidget->setCurrentIndex(1);

	//debug:����һ����Ϣ��
	//QMessageBox::information(this, "Congratulations", "Congratulations! You have completed the game.");

}

void humanresourcemachine::update_progress(int p, int level_num) {
	if (p == 0) {
		//�����һ�����֮ǰû����ɣ���ͨ������+1
		if (player_progress->currentLevel == level_num) {
			player_progress->currentLevel += 1;
			if (player_progress->currentLevel > 4) {
				player_progress->isCompleted = true;
				player_progress->currentLevel = 4;
				ui_level_select_re_init(); // �Զ��ص�ѡ�ؽ���
			}
			else {
				player_progress->isCompleted = false;
				enter_level(player_progress->currentLevel); // �Զ�������һ��
			}
		}
	}
	player_progress->saveProgress("../../log/player_progress.json");
}