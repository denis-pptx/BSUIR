#include "Entry.h"






Entry::Entry(QWidget *parent) :
    Task(TaskType::ENTRY, parent),
    userAnswer(nullptr)

{
    userAnswer = nullptr;

    optionsLinesEdit.push_back(new QLineEdit);
    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);


    optionsLayout->addWidget(optionsLinesEdit.back(), 0, 0);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    ans_amount = 1;
}


QPair<bool, int> Entry::execute() {
    // Получение ответа пользователя
    if (userAnswer == nullptr) {
        userAnswer = new QString;
        *userAnswer = optionsLinesEdit.back()->text();
    }

    // Результат задания
    bool flag = rightAnswer.toLower() == userAnswer->toLower();
    return QPair<bool, int>(flag, price);
}



void Entry::read(QFile* file) {

    // Считать общие для всех заданий свойства
    read_general(file);

    rightAnswer = optionsLinesEdit.back()->text();
    optionsLinesEdit.back()->setText("");
}

void Entry::setWatchMistakesEnabled(bool flag)
{
    setWatchMistakesEnabled_general(flag);

    if (flag == false) {
        delete userAnswer;
        userAnswer = nullptr;
    }

    optionsLinesEdit.back()->setReadOnly(flag);
}

void Entry::switchAnswers(Answers answers) {

    currentAnswers = answers;

    if (answers == Answers::RIGHT)
        optionsLinesEdit.back()->setText(rightAnswer);
    else
        optionsLinesEdit.back()->setText(*userAnswer);

}
