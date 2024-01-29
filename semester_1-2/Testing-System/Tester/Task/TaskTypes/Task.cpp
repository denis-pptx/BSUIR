#include "Task.h"
#include "Task/TaskService.h"

Task::Task(TaskType type, QWidget* parent)
    : TaskView(parent), taskType(type), ans_amount(0), price(0)
{

    connect(ui->switchAnswersButton, &QPushButton::clicked, this, &Task::on_switchAnswersButton_clicked);

}





// Вопрос задания
QString Task::getQuestion() {
    return ui->textEdit->toPlainText();
}


TaskType Task::getType() {
    return taskType;
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
    file->read((char*)&price, sizeof(int32_t));
    ui->priceLabel->setText("Стоимость: " + QString::number(price));

    // Размер названия
    uint32_t size;
    file->read((char*)&size, sizeof(uint32_t));

    // Название
    char* str = new char[size + 1];
    file->read(str, (size + 1) * sizeof(char));

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

}

void Task::setTaskNum(int number, int total) {
    ui->taskNumlabel->setText("Задание: " + QString::number(number) + QString(" / ") + QString::number(total));
}

void Task::setWatchMistakesEnabled_general(bool flag) {

    if (execute().first) {
        ui->taskResultLabel->setText("Верно");
        ui->taskResultLabel->setStyleSheet("font: 700 18pt \"Segoe UI\"; color: green");
    }
    else {
        ui->taskResultLabel->setText("Неверно");
        ui->taskResultLabel->setStyleSheet("font: 700 18pt \"Segoe UI\"; color: red");
    }

    ui->switchAnswersButton->setHidden(!flag);
    ui->taskResultLabel->setHidden(!flag);
    ui->whoseAnswersLabel->setHidden(!flag);
}

void Task::on_switchAnswersButton_clicked()
{
    if (currentAnswers == Answers::USER) {
        switchAnswers(Answers::RIGHT);
        ui->switchAnswersButton->setText("Показать мой ответ");
        ui->whoseAnswersLabel->setText("Ответ: правильный");

    }
    else {
        switchAnswers(Answers::USER);
        ui->switchAnswersButton->setText("Показать правильный ответ");
        ui->whoseAnswersLabel->setText("Ответ: мой");
    }
}
