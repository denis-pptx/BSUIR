#include "SingleChoice.h"



SingleChoice::SingleChoice(QWidget *parent) :
    Task(TaskType::SINGLE_CHOICE, parent),
    userAnswer(nullptr)
{

    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

    optionsRadioButtons[0]->setChecked(true);

}

void SingleChoice::plus() {

    optionsRadioButtons.push_back(new QRadioButton);
    optionsLinesEdit.push_back(new QLineEdit);


    optionsLayout->addWidget(optionsRadioButtons.back(), ans_amount, 0);
    optionsLayout->addWidget(optionsLinesEdit.back(), ans_amount, 1);

    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);
    optionsLinesEdit.back()->setReadOnly(true);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    ++ans_amount;
}

void SingleChoice::minus() {

    optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, 0)->widget());
    optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, 1)->widget());

    if (optionsRadioButtons.back()->isChecked())
        optionsRadioButtons[0]->setChecked(true);

    delete optionsRadioButtons.back();
    delete optionsLinesEdit.back();

    optionsRadioButtons.pop_back();
    optionsLinesEdit.pop_back();

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    --ans_amount;
}

QPair<bool, int> SingleChoice::execute() {

    // Получение ответа пользователя
    if (userAnswer == nullptr) {

        userAnswer = new int32_t(0);

        for (int i = 0; i < ans_amount; i++)
            if (optionsRadioButtons[i]->isChecked()) {
                *userAnswer = i;
                break;
            }
    }

    // Результат задания
    bool flag = rightAnswer == *userAnswer;
    return QPair<bool, int>(flag, price);
}



void SingleChoice::read(QFile* file) {

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильный ответ
    file->read((char*)&rightAnswer, sizeof(int32_t));

    optionsRadioButtons[0]->setChecked(true);
}

void SingleChoice::setWatchMistakesEnabled(bool flag)
{
    setWatchMistakesEnabled_general(flag);

    // Чтобы после выключения показа ошибок и изменения ответов
    // в execute отработало получение нового ответа пользователя
    if (flag == false) {
        delete userAnswer;
        userAnswer = nullptr;
    }

    // Отключить взаимодействие мышки выбором ответов
    for (int i = 0; i < ans_amount; i++)
        optionsRadioButtons[i]->setAttribute(Qt::WA_TransparentForMouseEvents, flag);



}

void SingleChoice::switchAnswers(Answers answers) {

    currentAnswers = answers;

    for (int i = 0; i < ans_amount; i++)
        optionsRadioButtons[i]->setChecked(false);

    if (answers == Answers::RIGHT)
        optionsRadioButtons[rightAnswer]->setChecked(true);
    else
        optionsRadioButtons[*userAnswer]->setChecked(true);

}





