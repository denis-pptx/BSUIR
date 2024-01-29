#ifndef ORDERINDICATION_H
#define ORDERINDICATION_H

#include "Task.h"

// УКАЗАНИЕ ПОРЯДКА
class OrderIndication : public Task {
private:
    QVector<int32_t> rightAnswers; // Правильные ответы
    QVector<int32_t>* userAnswers;  // Ответы пользователя

    // Комбобоксы вариантов ответов
    QVector<QComboBox*> optionsComboBoxes;

protected:
    QPair<bool, int> execute() override;
    void plus() override;
    void minus() override;
    void switchAnswers(Answers answers) override;

public:
    OrderIndication(QWidget* parent = nullptr);

    void read(QFile* file) override;
    void setWatchMistakesEnabled(bool) override;
};

#endif // ORDERINDICATION_H
