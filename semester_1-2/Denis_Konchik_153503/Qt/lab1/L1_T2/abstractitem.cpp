#include "abstractitem.h"

AbstractItem::AbstractItem(QObject *parent) : QObject(parent)
{

}

void AbstractItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    if (event->button() & Qt::LeftButton) {
        delete this;
    } else if (event->button() & Qt::RightButton) {
        showFigureInfo();
    }
};

void AbstractItem::showFigureInfo() {
    QWidget* window = new QWidget;
    window->setWindowTitle(name);
    window->setWindowFlags(Qt::Window | Qt::Tool);

    QVBoxLayout* layText = new QVBoxLayout;
    layText->addWidget(new QLabel("Периметр:"));
    layText->addWidget(new QLabel("Площадь:"));
    layText->addWidget(new QLabel("Центр масс:"));

    QVBoxLayout* layValue = new QVBoxLayout;
    layValue->addWidget(new QLabel(QString::number(P)));
    layValue->addWidget(new QLabel(QString::number(S)));
    layValue->addWidget(new QLabel("(" + QString::number(C.x()) + ", " + QString::number(C.y()) + ")"));

    QHBoxLayout* mainLay = new QHBoxLayout;
    mainLay->addItem(layText);
    mainLay->addItem(layValue);

    window->setLayout(mainLay);
    window->show();
}
