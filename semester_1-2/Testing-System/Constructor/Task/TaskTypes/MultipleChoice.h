#ifndef MULTIPLECHOICE_H
#define MULTIPLECHOICE_H

#include "Task.h"

// МНОЖЕСТВЕННЫЙ ВЫБОР
class MultipleChoice : public Task {
private:
    // Чекбоксы вариантов ответов
    QVector<QCheckBox*> optionsCheckBoxes;

protected:
    void plus() override;
    void minus() override;

public:
    explicit MultipleChoice(QWidget *parent = nullptr);

    void write(QFile* file) override;
    void read(QFile* file) override;
    QString toString(bool) override;

    Task* getCopy() override;
};

#endif // MULTIPLECHOICE_H
