#ifndef SINGLECHOICE_H
#define SINGLECHOICE_H

#include "Task.h"

// ОДИНОЧНЫЙ ВЫБОР
class SingleChoice : public Task {
private:
    // Радиобаттоны вариантов ответов
    QVector<QRadioButton*> optionsRadioButtons;

protected:
    void plus() override;
    void minus() override;

public:
    explicit SingleChoice(QWidget *parent = nullptr);

    void write(QFile* file) override;
    void read(QFile* file) override;
    QString toString(bool) override;

    Task* getCopy() override;
};

#endif // SINGLECHOICE_H
