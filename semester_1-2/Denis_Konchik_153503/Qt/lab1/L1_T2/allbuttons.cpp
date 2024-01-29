#include "allbuttons.h"


allButtons::allButtons(QWidget* parent) : QWidget(parent)
{

    rectangleButton = new QPushButton("Прямоугольник");
    squareButton = new QPushButton("Квадрат");
    circleButton = new QPushButton("Круг");
    triangleButton = new QPushButton("Треугольник");
    rhombButton = new QPushButton("Ромб");
    hexagonButton = new QPushButton("N-угольник");
    parallelogramButton = new QPushButton("Параллелограмм");
    starButton = new QPushButton("Звезда");
    drawButton = new QPushButton("Рисовать");
    infoButton = new QPushButton("Info");
}
