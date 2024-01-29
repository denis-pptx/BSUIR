#ifndef TASKCHOOSE_H
#define TASKCHOOSE_H

#include <QDialog>
#include <QRadioButton>
#include <QLayout>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QWidget>
#include "TaskTypes\Task.h"

// RadioButton с сигналом двойного клика мыши
class RadioButton : public QRadioButton {
    Q_OBJECT
signals:
    void doubleClicked();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent*) override {
        emit doubleClicked();
    }

public:
    RadioButton(QString text, QWidget* parent = nullptr)
        : QRadioButton(text, parent)
    {

    }

};

// Выбор типа задания
class TaskChoose : public QDialog
{
    Q_OBJECT   
private:
    // Ok | Cancel
    QPushButton* Ok;
    QPushButton* Cancel;

    QVBoxLayout* componentsLayout;     // layout со всеми компонентами окна
    QVector<RadioButton*> radioButton; // Вектор RadioButton'ов
    TaskType type;                     // Тип выбранного задания

public slots:
    // Ok | Cancel: clicked
    void on_Ok_clicked();
    void on_Cancel_clicked();

public:
    TaskChoose();

    TaskType getType(); // Получить тип выбранного задания
    Task* getTask();    // Получить выбранное задание
    void reset();       // Сбросить (radiobutton в исх положение)

};



#endif // TASKCHOOSE_H
