#include "Task.h"
#include "Task/TaskService.h"

Task::Task(TaskType type, QWidget* parent)
    : TaskView(parent), taskType(type), ans_amount(0)
{

    // Соединение кнопок добавления и удаления вариантов ответа
    connect(ui->plusButton, &QPushButton::clicked, this, &Task::plus);
    connect(ui->plusButton, &QPushButton::clicked, this, &Task::checkOptionsLimit);
    connect(ui->minusButton, &QPushButton::clicked, this, &Task::minus);
    connect(ui->minusButton, &QPushButton::clicked, this, &Task::checkOptionsLimit);


    connect(ui->resetNameButton, &QPushButton::clicked, this, &Task::resetTaskName);

    connect(ui->nameLineEdit, &QLineEdit::textEdited, this, [=](){
        emit nameEdited();
    });

    ui->nameLineEdit->setMaxLength(MAX_TASK_NAME_LEN);
    ui->nameLineEdit->setText(TaskService::strByType(taskType));
}


void Task::copy_general(const Task* copyFrom) {
    ui->textEdit->setText(copyFrom->ui->textEdit->toPlainText());
    ui->nameLineEdit->setText(copyFrom->ui->nameLineEdit->text());
    ui->priceSpinBox->setValue(copyFrom->ui->priceSpinBox->value());

    while (ans_amount < copyFrom->ans_amount)
        plus();

    while (ans_amount > copyFrom->ans_amount)
        minus();

    checkOptionsLimit();
}
void Task::resetTaskName() {
    ui->nameLineEdit->setText(TaskService::strByType(taskType));
    emit nameEdited();
}

void Task::checkOptionsLimit() {

    if (ans_amount == MAX_OPT_NUM) {
        ui->plusButton->setEnabled(false);
        ui->minusButton->setEnabled(true);
    } else if (ans_amount == MIN_OPT_NUM) {
        ui->plusButton->setEnabled(true);
        ui->minusButton->setEnabled(false);
    } else if (ans_amount == 1) { // в случае типа задания "Ввод"
        ui->plusButton->setEnabled(false);
        ui->minusButton->setEnabled(false);
    } else {
        ui->plusButton->setEnabled(true);
        ui->minusButton->setEnabled(true);
    }
}


// Вопрос задания
QString Task::getQuestion() {
    return ui->textEdit->toPlainText();
}

QString Task::getName() {
    return ui->nameLineEdit->text();
}

TaskType Task::getType() {
    return taskType;
}

void Task::write_general(QFile* file) {

    // Тип задания
    file->write((char*)&taskType, sizeof(TaskType));

    // Число пунктов в задании
    file->write((char*)&ans_amount, sizeof(int32_t));

    // Цена
    uint32_t price = ui->priceSpinBox->value();
    file->write((char*)&price, sizeof(uint32_t));

    // Размер названия
    uint32_t size = ui->nameLineEdit->text().toStdString().size();
    file->write((char*)&size, sizeof(uint32_t));

    // Название
    file->write(ui->nameLineEdit->text().toStdString().c_str(), (size + 1) * sizeof(char));

    // Размер вопроса
    size = ui->textEdit->toPlainText().toStdString().size();
    file->write((char*)&size, sizeof(uint32_t));

    // Вопрос
    file->write(ui->textEdit->toPlainText().toStdString().c_str(), (size + 1) * sizeof(char));

    // Текст в вариантах ответа
    for (const auto& line : optionsLinesEdit) {

        // Длина строки
        uint32_t size = line->text().toStdString().size();
        file->write((char*)&size, sizeof(uint32_t));

        // Строка
        file->write(line->text().toStdString().c_str(), (size + 1) * sizeof(char));
    }


}

void Task::read_general(QFile* file) {

    int32_t need_ans_amount;

    // Число вариантов ответов в задании
    file->read((char*)&need_ans_amount, sizeof(int32_t));


    while (ans_amount < need_ans_amount)
        plus();

    while (ans_amount > need_ans_amount)
        minus();

    // Цена
    int32_t price;
    file->read((char*)&price, sizeof(int32_t));
    ui->priceSpinBox->setValue(price);

    // Размер названия
    uint32_t size = ui->nameLineEdit->text().toStdString().size();
    file->read((char*)&size, sizeof(uint32_t));

    // Название
    char* str = new char[size + 1];
    file->read(str, (size + 1) * sizeof(char));

    ui->nameLineEdit->setText(QString(str));

    delete[] str;

    // Размер вопроса
    size = 0;
    file->read((char*)&size, sizeof(int32_t));

    // Вопрос
    str = new char[size + 1];
    file->read(str, (size + 1) * sizeof(char));

    ui->textEdit->setText(QString(str));

    delete[] str;

    // Текст в пунктах заданий
    for (const auto& line : optionsLinesEdit) {


        // Длина строки
        int32_t size = 0;
        file->read((char*)&size, sizeof(int32_t));


        // Строка
        char* str = new char[size + 1];
        file->read(str, (size + 1) * sizeof(char));

        line->setText(QString(str));

        delete[] str;
    }

    checkOptionsLimit();

}

int Task::getPrice() {
    return ui->priceSpinBox->value();
}
