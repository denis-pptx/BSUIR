#include "tetragon.h"

Tetragon::Tetragon(QString name, double alpha) : AbstrItem(name)
{
    this->alpha = alpha;

    InputDialogTetragon* dialog = new InputDialogTetragon(name);
    dialog->show();
    dialog->activateWindow();

    if (dialog->exec() == QDialog::Accepted) {

        weight = dialog->getW();
        height = dialog->getH();

        if (name == "Квадрат")
            height = weight;
        else if (name == "Ромб")
            height = weight * sqrt(3) / 2;

        calculateInfo();
    }
}

void Tetragon::calculateInfo() {

    QPoint O = QPoint(rand() % 600 + 200, rand() % 400 + 200);


    p[0] = O;
    p[1] = O + QPoint(height / tan(alpha), -height);
    p[2] = O + QPoint(weight + height / tan(alpha), -height);
    p[3] = O + QPoint(weight, 0);

    P = 2 * (weight + height);
    S = weight * height;
    C = QPoint(weight / 2, height / 2);
}

void Tetragon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QPolygon* plgn = new QPolygon;

    for (int i = 0; i < 4; i++)
        *plgn << p[i];

    painter->setBrush(QBrush(QColor(R, G, B)));
    painter->drawPolygon(*plgn);

    setFlags(QGraphicsItem::ItemIsMovable);
    Q_UNUSED(option); Q_UNUSED(widget);
}

QRectF Tetragon::boundingRect() const {

    return QRectF(p[0].x(), p[1].y(), p[2].x() - p[0].x(), p[3].y() - p[1].y());
}


InputDialogTetragon::InputDialogTetragon(QString name)
    : QDialog(nullptr, Qt::Window | Qt::Tool) {

    setWindowTitle(name);
    setModal(true);


    spbW = new QSpinBox;
    spbW->setRange(10, 300);
    spbW->setValue(200);

    spbH = new QSpinBox;
    spbH->setRange(10, 300);
    spbH->setValue(100);

    QLabel* weight_lbl = new QLabel("Ширина: ");
    QLabel* height_lbl = new QLabel("Высота: ");
    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отменить");

    QGridLayout* lay = new QGridLayout;

    lay->addWidget(weight_lbl, 0, 0);
    lay->addWidget(spbW, 0, 1);

    if (name == "Квадрат" || name == "Ромб") {
        weight_lbl->setText("Сторона");
        spbW->setValue(100);
        lay->addWidget(Ok, 1, 0);
        lay->addWidget(Cancel, 1, 1);
    } else {
        lay->addWidget(height_lbl, 1, 0);
        lay->addWidget(spbH, 1, 1);

        lay->addWidget(Ok, 2, 0);
        lay->addWidget(Cancel, 2, 1);
    }
    setLayout(lay);

    connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

int InputDialogTetragon::getW() {
    return spbW->value();
}

int InputDialogTetragon::getH() {
    return spbH->value();
}

Square::Square() : Tetragon("Квадрат", PI / 2) { };
Rectangle::Rectangle() : Tetragon("Прямоугольник", PI / 2) { };
Rhomb::Rhomb() : Tetragon("Ромб", PI / 3) { };
