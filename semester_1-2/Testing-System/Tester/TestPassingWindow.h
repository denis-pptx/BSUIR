#ifndef TESTPASSINGWINDOW_H
#define TESTPASSINGWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QMessageBox>

#include "Task\TaskTypes\Task.h"
#include "Test.h"
#include "TestResultWindow.h"


namespace Ui {
class PassingTestWindow;
}

// ОКНО ПРОХОЖДЕНИЕ ТЕСТА
class PassingTestWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PassingTestWindow(Test*, QPair<QString, QString>, QWidget *parent = nullptr);
    ~PassingTestWindow();

signals:
    void goToMainWindow();

private slots:
    void on_goToMainWindowButton_clicked();
    void on_nextButton_clicked();
    void on_prevButton_clicked();
    void on_finishButton_clicked();

    void on_showMistakes();

    void updateTime();               // Обновить тикающее время
    QString secondsToFormatStr(int); // Секунды в формат

private:
    Ui::PassingTestWindow *ui;

    // Окно с результатом теста
    TestResultWindow* testResultWindow;

    Test* test;                   // Тест
    QTimer* timer;                // Таймер
    int currentTaskIndex;         // Текущий индекс задания
    int passedTime;               // Прошедшее время (в секундах)
    QPair<QString, QString> name; // Имя тестируемого
};

#endif // TESTPASSINGWINDOW_H
