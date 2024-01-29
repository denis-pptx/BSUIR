#include "triangle.h"

Triangle::Triangle()
{

    InputDialogTriangle* dialog = new InputDialogTriangle;
    dialog->show();
    dialog->activateWindow();

    QPoint correct(115, 80);
    if (dialog->exec() == QDialog::Accepted) {


        P1 = dialog->getP1() + correct;
        P2 = dialog->getP2() + correct;
        P3 = dialog->getP3() + correct;

        calculateInfo();
    }
}

void Triangle::calculateInfo() {

    name = "Треугольник";

    P1P2 = sqrt( pow(P2.x() - P1.x(), 2) + pow(P2.y() - P1.y(), 2) );
    P2P3 = sqrt( pow(P3.x() - P2.x(), 2) + pow(P3.y() - P2.y(), 2) );
    P1P3 = sqrt( pow(P3.x() - P1.x(), 2) + pow(P3.y() - P1.y(), 2) );

    P = P1P2 + P2P3 + P1P3;
    double p = P / 2;
    S = sqrt(p * (p - P1P2) * (p - P2P3) * (p - P1P3));
    C = QPoint((P1.x() + P2.x() + P3.x()) / 3, (P1.y() + P2.y() + P3.y()) / 3);

}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPolygon* plgn = new QPolygon;

    *plgn << P1 << P2 << P3;

    painter->setBrush(QBrush(QColor(R, G, B)));
    painter->drawPolygon(*plgn);

    setFlags(QGraphicsItem::ItemIsMovable);
    Q_UNUSED(option); Q_UNUSED(widget);
}

QRectF Triangle::boundingRect() const {

    return QRectF(min(P1.x(), min(P2.x(), P3.x())),
                  min(P1.y(), min(P2.y(), P3.y())),
                  max(P1.x(), max(P2.x(), P3.x())) - min(P1.x(), min(P2.x(), P3.x())),
                  max(P1.y(), max(P2.y(), P3.y())) - min(P1.y(), min(P2.y(), P3.y()))
                  );
}



InputDialogTriangle::InputDialogTriangle(QWidget* parent)
    : QDialog(parent, Qt::Window | Qt::Tool) {

    setWindowTitle("Треугольник");
    setModal(true);

    spbP = new QSpinBox*[3];
    for (int i = 0; i < 3; i++)
        spbP[i] = new QSpinBox[2];

    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отменить");

    QGridLayout* lay = new QGridLayout;

    int defaultCoords[3][2] = { {300, 300}, {300, 400}, {400, 300} };
    // int defaultCoords[3][2] = { {0, 0}, {0, 100}, {100, 000} };
    for (int i = 0; i < 3; i++) {

        spbP[i][0].setRange(0, 800);
        spbP[i][0].setValue(defaultCoords[i][0]);
        lay->addWidget(new QLabel("X" + QString::number(i+1) + " :"), i, 0);
        lay->addWidget(&spbP[i][0], i, 1);


        spbP[i][1].setRange(0, 800);
        spbP[i][1].setValue(defaultCoords[i][1]);
        lay->addWidget(new QLabel("Y" + QString::number(i+1) + " :"), i, 2);
        lay->addWidget(&spbP[i][1], i, 3);

    }

    QHBoxLayout* horizontalLay = new QHBoxLayout;
    horizontalLay->addWidget(Ok);
    horizontalLay->addWidget(Cancel);

    QVBoxLayout* verticalLay = new QVBoxLayout;
    verticalLay->addLayout(lay);
    verticalLay->addLayout(horizontalLay);


    setLayout(verticalLay);

    connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));

}

QPoint InputDialogTriangle::getP1() {
    return { spbP[0][0].value(), spbP[0][1].value() };
}

QPoint InputDialogTriangle::getP2() {
    return { spbP[1][0].value(), spbP[1][1].value() };
}

QPoint InputDialogTriangle::getP3() {
    return { spbP[2][0].value(), spbP[2][1].value() };
}


