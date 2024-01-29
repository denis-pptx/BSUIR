#ifndef TEST_H
#define TEST_H

#include <QList>
#include "Task\TaskTypes\Task.h"
#include "Task\TaskService.h"
#include "ModifiedClasses/StatusBar.h"

#include <list>
#include <QWidget>
#include <QFile>
#include <QUrl>
#include <QPrinter>

// Состояние теста
enum TestStatus {
    CREATED,       // Создан
    OPENED,        // Открыт из файла
    EDITED,        // Изменен
    SAVED,         // Сохранен
    REMOVED        // Удален
};

// ТЕСТ
class Test : public QObject
{
    Q_OBJECT
private:
    QVector<Task*> taskList;           // Задания
    QPair<bool, int32_t> passingTime;  // Время прохождения
    TestStatus status;                 // Состояние
    QUrl url;                          // Путь к тесту

    void setStatus(TestStatus); // Установить статус
    QString toString(bool solved); // Конвертировать тест в строку
    int sumOfPrices();             // Стоимость всех заданий

signals:
    // Сигналы теста
    void testCreated();
    void testOpened();
    void testEdited();
    void testSaved();
    void testRemoved();

public:
    Test(QUrl);

    static StatusBar* statusBar; // Статусбар из MainWindow

    // Добавить, удалить, вставить задание
    void addTask(Task*);
    void removeTask(int);
    void pasteTask(int numberOfPasted, int placeToPaste);

    // Открыть, Создать, Сохранить, Удалить тест
    void open();
    void create();
    void save();
    void saveAs(QUrl);
    void savePDF(QUrl);
    void remove();


    void moveTask(int, int);       // Изменить номер заданию
    bool hasUnsavedChanges();      // Есть ли несохраненные изменения
    int size();                    // Количество заданий
    Task* back();                  // Последнее задание в тесте
    Task* operator[](int);         // Задание теста по индексу
    QUrl getUrl();                 // Получить Url теста
    QString getFileName();         // Получить имя файла

    // Время прохождения теста
    void setPassingTime(bool, int);
    void setPassingTime(QPair<bool, int32_t>);
    QPair<bool, int32_t> getPassingTime();

};



#endif // TEST_H
