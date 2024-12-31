#pragma once
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <iostream>

class PlayerProgress {
public:
    int currentLevel;  // ��ǰ�ؿ�
    bool isCompleted;  // �Ƿ���ɵ�ǰ�ؿ�


    PlayerProgress() : currentLevel(1), isCompleted(false) {}

    // ������ȵ��ļ�
    void saveProgress(const QString& filename) {
        QJsonObject progressData;
        progressData["currentLevel"] = currentLevel;
        progressData["isCompleted"] = isCompleted;

        QJsonDocument doc(progressData);
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson());
            file.close();
        }
    }

    // ���ļ����ؽ���
    void loadProgress(const QString& filename) {
        //����ļ������ڣ��򴴽��ļ���д��Ĭ�Ͻ���
        if (!QFile(filename).exists()) {
            saveProgress(filename);
            std::cout << "Progress file not found, creating a new one." << std::endl;
            return;
        }
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray data = file.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QJsonObject progressData = doc.object();

            currentLevel = progressData.value("currentLevel").toInt();
            isCompleted = progressData.value("isCompleted").toBool();
            file.close();
        }
    }
};
