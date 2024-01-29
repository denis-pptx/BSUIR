#ifndef TEST_H
#define TEST_H

#include "Task\TaskTypes\Task.h"
#include "Task\TaskService.h"
#include "TestResult.h"

#include <QWidget>
#include <QFile>
#include <QUrl>
#include <QPair>
#include <QList>

// ТЕСТ
class Test : public QObject
{
    Q_OBJECT
private:
    QVector<Task*> taskList;           // Задания
    QPair<bool, int32_t> passingTime;  // Время прохождения
    QUrl url;                          // Путь к тесту

public:
    Test(QUrl);

    // Добавить и удалить задание
    void addTask(Task*);
    void removeTask(int);


    // Открыть тест
    void open();

    // Активировать компоненты просмотра ошибок во всех заданиях
    void setWatchMistakesEnabled(bool);

    TestExecute execute();      // Результат прохождения теста
    int size();                // Количество заданий
    Task* back();              // Последнее задание в тесте
    Task* operator[](int i);   // Задание теста по индексу
    QUrl getUrl();             // Получить Url теста

    // Время прохождения теста
    void setPassingTime(bool, int);
    void setPassingTime(QPair<bool, int32_t>);
    QPair<bool, int32_t> getPassingTime();
};



#endif // TEST_H
