#pragma once

#ifndef GRAPHICSPAINTER_H
#define GRAPHICSPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class Drawing : public QWidget
{
    Q_OBJECT

public:
    Drawing(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    bool isLeftPressed;
    bool isMouseCanDraw;
    bool isAfterDelete;

    QVector<QPointF> pointList;
    QPointF endPoint;
    QPen pen;
    int R, G, B;
};

#endif // GRAPHICSPAINTER_H
