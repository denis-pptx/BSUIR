#ifndef ENTRY_H
#define ENTRY_H

#include "Task.h"

// ВВОД
class Entry : public Task {
protected:
    void plus() override {}
    void minus() override {}

public:
    explicit Entry(QWidget* parent = nullptr);

    void write(QFile* file) override;
    void read(QFile* file) override;
    QString toString(bool) override;

    Task* getCopy() override;
};

#endif // ENTRY_H
