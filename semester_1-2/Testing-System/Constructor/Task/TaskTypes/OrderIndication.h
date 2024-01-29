#ifndef ORDERINDICATION_H
#define ORDERINDICATION_H

#include "Task.h"

// УКАЗАНИЕ ПОРЯДКА
class OrderIndication : public Task {
private:
    // Комбобоксы вариантов ответов
    QVector<QComboBox*> optionsComboBoxes;

protected:
    void plus() override;
    void minus() override;

public:
    explicit OrderIndication(QWidget* parent = nullptr);

    void write(QFile* file) override;
    void read(QFile* file) override;
    QString toString(bool) override;

    Task* getCopy() override;
};

#endif // ORDERINDICATION_H
