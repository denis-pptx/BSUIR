#ifndef TASKSERVICE_H
#define TASKSERVICE_H

#include <QString>

#include "TaskTypes\SingleChoice.h"
#include "TaskTypes\MultipleChoice.h"
#include "TaskTypes\OrderIndication.h"
#include "TaskTypes\Comparison.h"
#include "TaskTypes\Entry.h"

class Task;

// Служебный класс для заданий
class TaskService {
public:

    // Получить название типа задания по enum
    static QString strByType(TaskType type) {

        if (type == TaskType::SINGLE_CHOICE)
            return "Одиночный выбор";
        else if (type == TaskType::MULTIPLE_CHOICE)
            return "Множественный выбор";
        else if (type == TaskType::ORDER_INDICATION)
            return "Указание порядка";
        else if (type == TaskType::COMPARISON)
            return "Сопоставление";
        else if (type == TaskType::ENTRY)
            return "Ввод";
        else
            throw std::exception();
    }

    // Получить задание по enum
    static Task* objByType(TaskType type) {


        if (type == TaskType::SINGLE_CHOICE)
            return new SingleChoice;
        else if (type == TaskType::MULTIPLE_CHOICE)
            return new MultipleChoice;
        else if (type == TaskType::ORDER_INDICATION)
            return new OrderIndication;
        else if (type == TaskType::COMPARISON)
            return new Comparison;
        else if (type == TaskType::ENTRY)
            return new Entry;
        else
            throw std::exception();

    }
};
#endif // TASKSERVICE_H
