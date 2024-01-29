#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QFile>
#include <QVector>
#include <QRadioButton>
#include <QLineEdit>
#include <QPair>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>

#include "TaskView.h"
#include "ui_TaskView.h"

// Начальное, минимальное и максимальное
// количество вариантов ответов
#define START_OPT_NUM 5
#define MAX_OPT_NUM 10
#define MIN_OPT_NUM 2

// Максимальная длина варианта ответа
#define MAX_POINT_LEN 33

// ТИПЫ ЗАДАНИЙ
enum TaskType {
    SINGLE_CHOICE,      // Одиночный выбор
    MULTIPLE_CHOICE,    // Множественный выбор
    ORDER_INDICATION,   // Указание порядка
    COMPARISON,         // Сопоставление
    ENTRY,              // Ввод

    AMOUNT              // Число типов заданий
};



// БАЗОВЫЙ КЛАСС ДЛЯ ВСЕХ ЗАДАНИЙ
class Task : public TaskView {
protected:
    TaskType taskType;  // Тип задания
    int32_t ans_amount; // Число ответов
    int32_t price;      // Стоимость задания

    // Линии ввода вариантов ответов
    QVector<QLineEdit*> optionsLinesEdit;

    // Добавить и удалить вариант ответов
    virtual void plus() = 0;
    virtual void minus() = 0;

    // общие действие для всех типов заданий
    void read_general(QFile* file);
    void setWatchMistakesEnabled_general(bool);

    // Показать ответы
    virtual void switchAnswers(Answers answers) = 0;

protected slots:
    void on_switchAnswersButton_clicked();

public:
    Task(TaskType type, QWidget* parent);

    QString getQuestion(); // Вопрос задания
    QString getName();     // Имя задания
    TaskType getType();    // Тип задания

    // Установить "Задание: a / b"
    void setTaskNum(int number, int total);

    // Как выполнено задание. <правильно?, цена>
    virtual QPair<bool, int> execute() = 0;

    // Активировать компоненты просмотра ошибок
    virtual void setWatchMistakesEnabled(bool) = 0;

    // Cчитать задание
    virtual void read(QFile* file) = 0;




};

#endif // TASK_H
