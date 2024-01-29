#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QStatusBar>
#include <QPalette>
#include <QString>
#include <Task\TaskService.h>
#include <QUrl>

// Продолжительность сообщения в статусбаре
#define STATUS_BAR_DURATION 3000

class StatusBar : public QStatusBar {
public:
    StatusBar(QWidget* parent = nullptr) : QStatusBar(parent) {

        setPalette(QPalette(Qt::gray, Qt::gray, Qt::gray, Qt::gray, Qt::gray, Qt::gray, Qt::gray));
    }

    void taskCopied(QString taskName) {
        showMessage("Задание скопировано: " + taskName, STATUS_BAR_DURATION);
    }

    void taskPasted(QString taskName) {
        showMessage("Задание вставлено: " + taskName, STATUS_BAR_DURATION);
    }

    void taskAdded(TaskType type) {
        showMessage("Задание добавлено: " + TaskService::strByType(type), STATUS_BAR_DURATION);
    }

    void taskRemoved(QString taskName) {
        showMessage("Задание удалено: " + taskName, STATUS_BAR_DURATION);
    }

    void testOpened(QUrl url) {
        showMessage("Тест открыт: " + url.toString(), STATUS_BAR_DURATION);
    }

    void testSaved(QUrl url) {
        showMessage("Тест сохранен: " + url.toString(), STATUS_BAR_DURATION);
    }

    void testSavedAs(QUrl url) {
        showMessage("Тест сохранен как: " + url.toString(), STATUS_BAR_DURATION);
    }

    void testSavedPDF(QUrl url) {
        showMessage("Тест экспортирован в PDF: " + url.toString(), STATUS_BAR_DURATION);
    }

    void testCreated(QUrl url) {
        showMessage("Тест создан: " + url.toString(), STATUS_BAR_DURATION);
    }

    void testRemoved(QUrl url) {
        showMessage("Тест удалён: " + url.toString(), STATUS_BAR_DURATION);
    }

};

#endif // STATUSBAR_H
