#include "TaskChoose.h"
#include "TaskService.h"

TaskChoose::TaskChoose()
    : Ok(new QPushButton("Ok")), Cancel(new QPushButton("Cancel")), componentsLayout(new QVBoxLayout), type((TaskType)0)
{

    setWindowTitle("Тип задания");
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    setModal(true);

    // Добавление RadioButton'ов в окно выбора типа задания
    for (int i = 0; i < TaskType::AMOUNT; i++) {
        radioButton.push_back(new RadioButton(TaskService::strByType((TaskType)i)));
        componentsLayout->addWidget(radioButton.back());
        connect(radioButton.back(), &RadioButton::doubleClicked, this, &TaskChoose::on_Ok_clicked);
    }

    radioButton[0]->setChecked(true);

    // Панель "Ok | Cancel"
    QHBoxLayout* acceptPanel = new QHBoxLayout;
    acceptPanel->addWidget(Ok);
    acceptPanel->addWidget(Cancel);

    componentsLayout->addItem(acceptPanel);

    setLayout(componentsLayout);

    connect(Ok, &QPushButton::clicked, this, &TaskChoose::on_Ok_clicked);
    connect(Cancel, &QPushButton::clicked, this, &TaskChoose::on_Cancel_clicked);
}

TaskType TaskChoose::getType() {
    return type;
}

Task* TaskChoose::getTask() {
    return TaskService::objByType(type);
}

void TaskChoose::reset() {
    radioButton[0]->setChecked(true);
}

void TaskChoose::on_Ok_clicked() {

    for (int i = 0; i < radioButton.size(); i++)
        if (radioButton[i]->isChecked()) {
            type = (TaskType)i;
            break;
        }

    accept();
}


void TaskChoose::on_Cancel_clicked()
{
    reject();
}
