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

    // Линии ввода вариантов ответов
    QVector<QLineEdit*> optionsLinesEdit;

    // Добавить и удалить вариант ответов
    virtual void plus() = 0;
    virtual void minus() = 0;

    void checkOptionsLimit(); // Проверка количества вариантов ответов
    void resetTaskName();     // Сбросить имя задания

    // Копировать основные свойства заданий в это задание из другого
    void copy_general(const Task* copyFrom);

public:
    Task(TaskType type, QWidget* parent);

    QString getQuestion(); // Вопрос задания
    QString getName();     // Имя задания
    TaskType getType();    // Тип задания
    int getPrice();        // Получить стоимость

    // Конвертировать в строку
    virtual QString toString(bool solved) = 0;

    // Записать и считать задание
    virtual void write(QFile* file) = 0;
    virtual void read(QFile* file) = 0;

    // Получить копию
    virtual Task* getCopy() = 0;

    // Записать и считать общие свойства для всех типов заданий
    void write_general(QFile* file);
    void read_general(QFile* file);
};

#endif // TASK_H
