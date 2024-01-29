#include "MultipleChoice.h"

MultipleChoice::MultipleChoice(QWidget *parent) :
    Task(TaskType::MULTIPLE_CHOICE, parent),
    userAnswers(nullptr)
{

    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

}



void MultipleChoice::plus() {

    optionsCheckBoxes.push_back(new QCheckBox);
    optionsLinesEdit.push_back(new QLineEdit);
    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);
    optionsLinesEdit.back()->setReadOnly(true);

    optionsLayout->addWidget(optionsCheckBoxes.back(), ans_amount, 0);
    optionsLayout->addWidget(optionsLinesEdit.back(), ans_amount, 1);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    ++ans_amount;
}

void MultipleChoice::minus() {

    optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, 0)->widget());
    optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, 1)->widget());

    delete optionsCheckBoxes.back();
    delete optionsLinesEdit.back();

    optionsCheckBoxes.pop_back();
    optionsLinesEdit.pop_back();

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    --ans_amount;


}

QPair<bool, int> MultipleChoice::execute() {

    // Получение ответа пользователя
    if (userAnswers == nullptr) {
        userAnswers = new QVector<bool>;

        for (int i = 0; i < ans_amount; i++)
            userAnswers->push_back(optionsCheckBoxes[i]->isChecked());
    }

    // Результат задания
    bool flag = true;
    for (int i = 0; i < ans_amount; i++)
        if (rightAnswers[i] != (*userAnswers)[i]) {
            flag = false;
            break;
        }

    return QPair<bool, int>(flag, price);
}


void MultipleChoice::read(QFile* file) {

    rightAnswers.clear();

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильные ответы
    for (int32_t i = 0; i < ans_amount; i++) {

        bool ans = 0;
        file->read((char*)&ans, sizeof(bool));

        rightAnswers.push_back(ans);
    }
}

void MultipleChoice::setWatchMistakesEnabled(bool flag)
{


    setWatchMistakesEnabled_general(flag);

    if (flag == false) {
        delete userAnswers;
        userAnswers = nullptr;
    }

    for (int i = 0; i < ans_amount; i++)
        optionsCheckBoxes[i]->setAttribute(Qt::WA_TransparentForMouseEvents, flag);

}

void MultipleChoice::switchAnswers(Answers answers) {

    currentAnswers = answers;

    if (answers == Answers::RIGHT)
        for (int i = 0; i < ans_amount; i++)
            optionsCheckBoxes[i]->setChecked(rightAnswers[i]);
    else
        for (int i = 0; i < ans_amount; i++)
            optionsCheckBoxes[i]->setChecked((*userAnswers)[i]);

}
