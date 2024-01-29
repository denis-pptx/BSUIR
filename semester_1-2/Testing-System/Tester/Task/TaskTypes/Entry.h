#ifndef ENTRY_H
#define ENTRY_H

#include "Task.h"

// ВВОД
class Entry : public Task {
private:
    QString rightAnswer; // Правильный ответ
    QString* userAnswer;  // Ответ пользователя

protected:
    QPair<bool, int> execute() override;
    void plus() override {}
    void minus() override {}
    void switchAnswers(Answers answers) override;

public:
    Entry(QWidget* parent = nullptr);

    void read(QFile* file) override;
    void setWatchMistakesEnabled(bool) override;
};

#endif // ENTRY_H
