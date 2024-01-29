#include "Comparison.h"

Comparison::Comparison(QWidget *parent) :
    Task(TaskType::COMPARISON, parent),
    userAnswers(nullptr)
{

    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

}

void Comparison::plus() {

    for (const auto& i : comboBox)
        i->addItem(QString::number(ans_amount + 1));

    comboBox.push_back(new QComboBox);

    for (int i = 0; i < ans_amount + 1; i++)
        comboBox.back()->addItem(QString::number(i + 1));

    comboBox.back()->setCurrentIndex(ans_amount);
    optionsLayout->addWidget(comboBox.back(), ans_amount, 0);

    for (int i = 0; i < 2; i++) {
        optionsLinesEdit.push_back(new QLineEdit);
        optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);
        optionsLinesEdit.back()->setReadOnly(true);

        optionsLayout->addWidget(optionsLinesEdit[ans_amount * 2 + i], ans_amount, i == 0 ? 1 : 3);
    }

    label.push_back(new QLabel(QString::number(ans_amount + 1) + "."));
    optionsLayout->addWidget(label.back(), ans_amount, 2);


    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    ++ans_amount;
}

void Comparison::minus() {


    for (int i = 0; i < 4; i++)
        optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, i)->widget());


    delete comboBox.back();
    delete label.back();

    for (int i = 0; i < 2; i++) {
        delete optionsLinesEdit[ans_amount * 2 - 1 - i];
        optionsLinesEdit.pop_back();
    }

    comboBox.pop_back();
    label.pop_back();


    for (const auto& i : comboBox)
        i->removeItem(ans_amount - 1);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    --ans_amount;
}

QPair<bool, int> Comparison::execute() {

    // Получение ответа пользователя
    if (userAnswers == nullptr) {
        userAnswers = new QVector<int32_t>;

        for (int i = 0; i < ans_amount; i++)
            userAnswers->push_back(comboBox[i]->currentIndex());
    }

    // Результат задания
    bool flag = true;
    for (int i = 0; i < ans_amount; i++) {
        if (rightAnswers[i] != (*userAnswers)[i]) {
            flag = false;
            break;
        }
    }

    return QPair<bool, int>(flag, price);
}


void Comparison::read(QFile* file) {

    rightAnswers.clear();

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильные ответы
    for (int32_t i = 0; i < ans_amount; i++) {

        int32_t ans = 0;
        file->read((char*)&ans, sizeof(uint32_t));
        rightAnswers.push_back(ans);
    }


}

void Comparison::setWatchMistakesEnabled(bool flag)
{
    setWatchMistakesEnabled_general(flag);

    if (flag == false) {
        delete userAnswers;
        userAnswers = nullptr;
    }

    for (int i = 0; i < ans_amount; i++)
        comboBox[i]->setAttribute(Qt::WA_TransparentForMouseEvents, flag);
}

void Comparison::switchAnswers(Answers answers) {

    currentAnswers = answers;

    if (answers == Answers::RIGHT)
        for (int i = 0; i < ans_amount; i++)
            comboBox[i]->setCurrentIndex(rightAnswers[i]);
    else
        for (int i = 0; i < ans_amount; i++)
            comboBox[i]->setCurrentIndex((*userAnswers)[i]);

}




