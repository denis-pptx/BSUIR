#ifndef COMPARISON_H
#define COMPARISON_H

#include "Task.h"

// СОПОСТАВЛЕНИЕ
class Comparison : public Task {
private:
    QVector<int32_t> rightAnswers;  // Правильные ответы
    QVector<int32_t>* userAnswers;   // Ответы пользователя

    // Комбобоксы и надписи с номерами вариантов ответов
    QVector<QComboBox*> comboBox;
    QVector<QLabel*> label;

protected:
    QPair<bool, int> execute() override;
    void plus() override;
    void minus() override;
    void switchAnswers(Answers answers) override;

public:
    Comparison(QWidget *parent = nullptr);

    void read(QFile* file) override;
    void setWatchMistakesEnabled(bool) override;
};

#endif // COMPARISON_H
