#ifndef COMPARISON_H
#define COMPARISON_H

#include "Task.h"

// СОПОСТАВЛЕНИЕ
class Comparison : public Task {
private:
    // Комбобоксы и надписи с номерами вариантов ответов
    QVector<QComboBox*> comboBox;
    QVector<QLabel*> label;

protected:
    void plus() override;
    void minus() override;

public:
    explicit Comparison(QWidget *parent = nullptr);

    void write(QFile* file) override;
    void read(QFile* file) override;
    QString toString(bool) override;

    Task* getCopy() override;
};

#endif // COMPARISON_H
