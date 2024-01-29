#ifndef SINGLECHOICE_H
#define SINGLECHOICE_H

#include "Task.h"

// ОДИНОЧНЫЙ ВЫБОР
class SingleChoice : public Task {
private:
    int32_t rightAnswer; // Правильный ответ
    int32_t* userAnswer;  // Ответ пользователя

    // Радиобаттоны вариантов ответов
    QVector<QRadioButton*> optionsRadioButtons;

protected:
    QPair<bool, int> execute() override;
    void plus() override;
    void minus() override;
    void switchAnswers(Answers answers) override;

public:
    SingleChoice(QWidget *parent = nullptr);

    void read(QFile* file) override;
    void setWatchMistakesEnabled(bool) override;
};

#endif // SINGLECHOICE_H
