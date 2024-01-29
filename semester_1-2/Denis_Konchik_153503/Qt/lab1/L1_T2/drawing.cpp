#include "drawing.h"

Drawing::Drawing(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);
    isLeftPressed = false;
    isMouseCanDraw = false;

    pen.setWidth(3);
    pen.setColor(QColor(rand() % 256, rand() % 256, rand() % 256));
}


void Drawing::paintEvent(QPaintEvent *) {

    QPainter painter(this);

    painter.setPen(pen);
    QVector<QLineF> lines;

    for (int i = 0; i < pointList.size() - 1; i++) {
        QLineF line(pointList[i], pointList[i+1]);
        lines.push_back(line);
    }

    if (isMouseCanDraw && pointList.size() > 0) {
        QLineF line(pointList.back(), endPoint);
        lines.push_back(line);
    }

    painter.drawLines(lines);
}


void Drawing::mousePressEvent(QMouseEvent *) {

    if (!isLeftPressed) {
        pointList.clear();
        isLeftPressed = true;
        update();
    }
}


void Drawing::mouseMoveEvent(QMouseEvent *event) {

    if (isLeftPressed) {
        endPoint = event->pos();
        isMouseCanDraw = true;
        update();
    }
}


void Drawing::mouseReleaseEvent(QMouseEvent *event) {

    if (isLeftPressed) {
        pointList.push_back(event->pos());
        isMouseCanDraw = false;
        update();
    }
}


void Drawing::mouseDoubleClickEvent(QMouseEvent *) {

    isLeftPressed = false;
    pointList.push_back(pointList[0]);
    update();
}
