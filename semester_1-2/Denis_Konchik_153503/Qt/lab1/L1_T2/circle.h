#ifndef CIRCLE_H
#define CIRCLE_H

#include "abstritem.h"

class Circle : public AbstrItem
{

private:
    int R;
    QPoint Begining;
    void calculateInfo() override;

public:
    Circle();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


class InputDialogCircle : public QDialog {
    Q_OBJECT
private:
    QSpinBox* spb;

public:
    InputDialogCircle(QWidget* parent = nullptr);
    int getR();
};

#endif // CIRCLE_H

