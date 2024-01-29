#include "OrderIndication.h"



OrderIndication::OrderIndication(QWidget *parent) :
    Task(TaskType::ORDER_INDICATION, parent),
    userAnswers(nullptr)
{
    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

    int c = 0;
    for (const auto& i : optionsComboBoxes)
        i->setCurrentIndex(c++);


}



void OrderIndication::plus() {

    for (const auto& i : optionsComboBoxes)
        i->addItem(QString::number(ans_amount + 1));

    optionsComboBoxes.push_back(new QComboBox);

    for (int i = 0; i < ans_amount + 1; i++)
        optionsComboBoxes.back()->addItem(QString::number(i + 1));

    optionsComboBoxes.back()->setCurrentIndex(ans_amount);

    optionsLinesEdit.push_back(new QLineEdit);
    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);
    optionsLinesEdit.back()->setReadOnly(true);

    optionsLayout->addWidget(optionsComboBoxes.back(), ans_amount, 0);
    optionsLayout->addWidget(optionsLinesEdit.back(), ans_amount, 1);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    ++ans_amount;
}

void OrderIndication::minus() {


    optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, 0)->widget());
    optionsLayout->removeWidget(optionsLayout->itemAtPosition(ans_amount - 1, 1)->widget());

    delete optionsComboBoxes.back();
    delete optionsLinesEdit.back();

    optionsComboBoxes.pop_back();
    optionsLinesEdit.pop_back();

    for (const auto& i : optionsComboBoxes)
        i->removeItem(ans_amount - 1);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    --ans_amount;


}

QPair<bool, int> OrderIndication::execute() {


    // Получение ответа пользователя
    if (userAnswers == nullptr) {

        userAnswers = new QVector<int32_t>;

        for (int i = 0; i < ans_amount; i++)
            userAnswers->push_back(optionsComboBoxes[i]->currentIndex());
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



void OrderIndication::read(QFile* file) {

    rightAnswers.clear();

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильные ответы
    for (int32_t i = 0; i < ans_amount; i++) {

        int32_t ans = 0;
        file->read((char*)&ans, sizeof(int32_t));

        rightAnswers.push_back(ans);
    }
}

void OrderIndication::setWatchMistakesEnabled(bool flag)
{

    setWatchMistakesEnabled_general(flag);

    if (flag == false) {
        delete userAnswers;
        userAnswers = nullptr;
    }

    for (int i = 0; i < ans_amount; i++)
        optionsComboBoxes[i]->setAttribute(Qt::WA_TransparentForMouseEvents, flag);


}

void OrderIndication::switchAnswers(Answers answers) {

    currentAnswers = answers;

    if (answers == Answers::RIGHT)
        for (int i = 0; i < ans_amount; i++)
            optionsComboBoxes[i]->setCurrentIndex(rightAnswers[i]);
    else
        for (int i = 0; i < ans_amount; i++)
            optionsComboBoxes[i]->setCurrentIndex((*userAnswers)[i]);

}
