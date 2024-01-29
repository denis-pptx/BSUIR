#include "OrderIndication.h"



OrderIndication::OrderIndication(QWidget *parent) :
    Task(TaskType::ORDER_INDICATION, parent)
{
    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

    int c = 0;
    for (const auto& i : optionsComboBoxes)
        i->setCurrentIndex(c++);
}

Task* OrderIndication::getCopy() {
    OrderIndication* ret = new OrderIndication;

    ret->copy_general(this);

    for (int i = 0; i < ret->ans_amount; i++) {
        ret->optionsComboBoxes[i]->setCurrentIndex(this->optionsComboBoxes[i]->currentIndex());
        ret->optionsLinesEdit[i]->setText(this->optionsLinesEdit[i]->text());
    }

    return ret;
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

    optionsLayout->addWidget(optionsComboBoxes.back(), ans_amount, 0);
    optionsLayout->addWidget(optionsLinesEdit.back(), ans_amount, 1);

    connect(optionsComboBoxes.back(), &QComboBox::currentIndexChanged, this, &TaskView::taskEdited);
    connect(optionsLinesEdit.back(), &QLineEdit::textEdited, this, &TaskView::taskEdited);

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

void OrderIndication::write(QFile* file)
{

    // Записать общие для всех заданий свойства
    write_general(file);

    // Правильные ответы
    for (int i = 0; i < ans_amount; i++) {
        int32_t ans = optionsComboBoxes[i]->currentIndex();
        file->write((char*)&(ans), sizeof(int32_t));
    }
}


void OrderIndication::read(QFile* file) {

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильные ответы
    for (int32_t i = 0; i < ans_amount; i++) {

        int32_t ans = 0;
        file->read((char*)&ans, sizeof(int32_t));

        optionsComboBoxes[i]->setCurrentIndex(ans);
    }
}

QString OrderIndication::toString(bool solved) {
    QString string = "Укажите порядок (цифрами 1-" + QString::number(optionsLinesEdit.size()) + ")\n";

    string += ui->textEdit->toPlainText() + "\n";

    for (int i = 0; i < optionsLinesEdit.size(); i++) {

        if (solved)
            string += QString::number(optionsComboBoxes[i]->currentIndex() + 1) + ". " + optionsLinesEdit[i]->text();
        else
            string += "_ " + optionsLinesEdit[i]->text();

        string += "\n";
    }

    string += "Стоимость: " + QString::number(ui->priceSpinBox->value()) + ".";

    return string;
}
