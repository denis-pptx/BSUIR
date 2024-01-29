#ifndef MULTIPLECHOICE_H
#define MULTIPLECHOICE_H

#include "Task.h"

// МНОЖЕСТВЕННЫЙ ВЫБОР
class MultipleChoice : public Task {
private:
    QVector<bool> rightAnswers; // Правильные ответы
    QVector<bool>* userAnswers;  // Ответы пользователя

    // Чекбоксы вариантов ответов
    QVector<QCheckBox*> optionsCheckBoxes;

protected:
    QPair<bool, int> execute() override;
    void plus() override;
    void minus() override;
    void switchAnswers(Answers answers) override;

public:
    MultipleChoice(QWidget *parent = nullptr);

    void read(QFile* file) override;
    void setWatchMistakesEnabled(bool) override;
};

#endif // MULTIPLECHOICE_H
