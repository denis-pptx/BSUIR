#include "Ngon.h"

Ngon::Ngon()
{
    InputDialogNgon* dialog = new InputDialogNgon;
    dialog->show();
    dialog->activateWindow();

    if (dialog->exec() == QDialog::Accepted) {
        N = dialog->getN();
        edge = dialog->getE();

        p = new QPoint[N];

        calculateInfo();
    }
}

void Ngon::calculateInfo() {

    QPoint O = QPoint(rand() % 600 + 200, rand() % 400 + 200);

    name = QString::number(N) + "-угольник";

    min_x = 2000; max_x = 0; min_y = 2000; max_y = 0;
    R = edge * sqrt(3) / 2;
    for (int i = 0; i < N; i++) {
        p[i].setX(O.x() + R * cos(2 * PI * i / N));
        p[i].setY(O.y() + R * sin(2 * PI * i / N));

        min_x = min(min_x, p[i].x());
        max_x = max(max_x, p[i].x());

        min_y = min(min_y, p[i].y());
        max_y = max(max_y, p[i].y());
    }

    P = N * edge;
    S = pow(edge, 2) * sqrt(3) * 0.25 * N;
    C = QPoint((max_x - min_x) / 2, (max_y - min_y) / 2);
}


void Ngon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPolygon* plgn = new QPolygon;

    for (int i = 0; i < N; i++)
        *plgn << p[i];

    painter->setBrush(QBrush(QColor(R, G, B)));
    painter->drawPolygon(*plgn);

    setFlags(QGraphicsItem::ItemIsMovable);
    Q_UNUSED(option); Q_UNUSED(widget);
}

QRectF Ngon::boundingRect() const {
    return QRectF(min_x, min_y, max_x - min_x, max_y - min_y);
}


InputDialogNgon::InputDialogNgon(QWidget* parent)
    : QDialog(parent, Qt::Window | Qt::Tool) {

    setWindowTitle("N-угольник");
    setModal(true);


    QGridLayout* param = new QGridLayout;

    spbN = new QSpinBox;
    spbN->setRange(4, 50);
    spbN->setValue(4);
    param->addWidget(new QLabel("Вершин: "), 0, 0);
    param->addWidget(spbN, 0, 1);

    spbE = new QSpinBox;
    spbE->setRange(10, 300);
    spbE->setValue(100);
    param->addWidget(new QLabel("Сторона: "), 1, 0);
    param->addWidget(spbE, 1, 1);


    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отменить");
    param->addWidget(Ok, 2, 0);
    param->addWidget(Cancel, 2, 1);

    setLayout(param);

    connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

int InputDialogNgon::getE() {
    return spbE->value();
}

int InputDialogNgon::getN() {
    return spbN->value();
}
