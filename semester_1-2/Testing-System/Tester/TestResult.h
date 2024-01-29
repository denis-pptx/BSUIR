#ifndef TESTRESULT_H
#define TESTRESULT_H

#include <QPair>
#include <QString>

struct TestExecute
{
    // Баллы <заработанные, возможные>
    QPair<int,int> score = QPair<int,int>(0,0);

    // Задания <верно решенные, всего>
    QPair<int,int> tasks = QPair<int,int>(0,0);
};

struct TestResult
{
    QPair<QString, QString> name; // Имя
    TestExecute testExecute;      // Подсчет теста
    QString time;                 // Время прохождения
};

#endif // TESTRESULT_H
