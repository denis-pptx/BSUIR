#include "TaskView.h"
#include "ui_TaskView.h"

TaskView::TaskView(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TaskView)
    , optionsLayout(new QGridLayout)
    , optionsWidget(new QWidget)
{
    ui->setupUi(this);


    // Соединение с сигналом "задание изменено"
    connect(ui->priceSpinBox, &QSpinBox::valueChanged, this, &TaskView::taskEdited);
    connect(ui->minusButton, &QPushButton::clicked, this, &TaskView::taskEdited);
    connect(ui->plusButton, &QPushButton::clicked, this, &TaskView::taskEdited);
    connect(this, &TaskView::nameEdited, this, &TaskView::taskEdited);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &TaskView::taskEdited);

}

TaskView::~TaskView()
{
    delete ui;
}






