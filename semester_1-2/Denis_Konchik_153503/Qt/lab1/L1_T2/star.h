#ifndef STAR_H
#define STAR_H

#include "abstritem.h"

class Star : public AbstrItem
{

private:
    QPoint* point;

    int R;

    int min_x, max_x, min_y, max_y;
    int peaksAmount;

    void calculateInfo() override;

public:
    Star();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

class InputDialogStar : public QDialog {
    Q_OBJECT
private:

    QSpinBox* spbP;
    QSpinBox* spbR;

public:
    InputDialogStar(QWidget* parent = nullptr);
    int getPeaks();
    int getR();

};
#endif // STAR_H
