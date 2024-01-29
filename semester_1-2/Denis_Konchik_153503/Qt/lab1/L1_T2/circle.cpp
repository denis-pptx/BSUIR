#include "circle.h"

Circle::Circle()
{
    InputDialogCircle* dialog = new InputDialogCircle;
    dialog->show();
    dialog->activateWindow();

    if (dialog->exec() == QDialog::Accepted) {
        R = dialog->getR();
        calculateInfo();
    }

    delete dialog;
}

void Circle::calculateInfo() {

    Begining = QPoint(rand() % 600 + 200, rand() % 400 + 200);

    name = "Круг";

    P = 2 * PI * R;
    S = PI * R * R;
    C = QPoint(R / 2, R / 2);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setBrush(QBrush(QColor(R, G, B)));
    painter->drawEllipse(Begining.x(), Begining.y(), R, R);

    setFlags(QGraphicsItem::ItemIsMovable);

    Q_UNUSED(option); Q_UNUSED(widget);
}

QRectF Circle::boundingRect() const {
    return QRectF(Begining.x(), Begining.y(), R, R);
}

InputDialogCircle::InputDialogCircle(QWidget* parent)
    : QDialog(parent, Qt::Window | Qt::Tool) {

    setWindowTitle("Круг");
    setModal(true);

    spb = new QSpinBox;
    spb->setRange(10, 300);
    spb->setValue(100);

    QLabel* radius = new QLabel("Радиус: ");
    QPushButton* Ok = new QPushButton("&Ок");
    QPushButton* Cancel = new QPushButton("&Отменить");

    QGridLayout* lay = new QGridLayout;
    lay->addWidget(radius, 0, 0);
    lay->addWidget(spb, 0, 1);
    lay->addWidget(Ok, 1, 0);
    lay->addWidget(Cancel, 1, 1);

    setLayout(lay);

    connect(Ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(Cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

int InputDialogCircle::getR() {
    return spb->value();
}

