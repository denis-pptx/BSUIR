#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "abstritem.h"

class Triangle : public AbstrItem
{

private:
    QPoint P1;
    QPoint P2;
    QPoint P3;

    double P1P2;
    double P2P3;
    double P1P3;

    void calculateInfo() override;

public:
    Triangle();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

class InputDialogTriangle : public QDialog {
    Q_OBJECT
private:
    QSpinBox** spbP;

public:
    InputDialogTriangle(QWidget* parent = nullptr);
    QPoint getP1();
    QPoint getP2();
    QPoint getP3();
};
#endif // TRIANGLE_H
