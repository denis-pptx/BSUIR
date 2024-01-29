#include "Comparison.h"

Comparison::Comparison(QWidget *parent) :
    Task(TaskType::COMPARISON, parent)
{

    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

}

Task* Comparison::getCopy() {

    Comparison* ret = new Comparison;

    ret->copy_general(this);

    for (int i = 0; i < ret->ans_amount; i++) {
        ret->comboBox[i]->setCurrentIndex(this->comboBox[i]->currentIndex());
        ret->optionsLinesEdit[2 * i]->setText(this->optionsLinesEdit[2 * i]->text());
        ret->optionsLinesEdit[2 * i + 1]->setText(this->optionsLinesEdit[2 * i + 1]->text());
    }

    return ret;
}

void Comparison::plus() {

    for (const auto& i : comboBox)
        i->addItem(QString::number(ans_amount + 1));

    comboBox.push_back(new QComboBox);

    for (int i = 0; i < ans_amount + 1; i++)
        comboBox.back()->addItem(QString::number(i + 1));

    comboBox.back()->setCurrentIndex(ans_amount);
    optionsLayout->addWidget(comboBox.back(), ans_amount, 0);
    connect(comboBox.back(), &QComboBox::currentIndexChanged, this, &TaskView::taskEdited);

    for (int i = 0; i < 2; i++) {
        optionsLinesEdit.push_back(new QLineEdit);
        optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);


        optionsLayout->addWidget(optionsLinesEdit[ans_amount * 2 + i], ans_amount, i == 0 ? 1 : 3);

        connect(optionsLinesEdit[ans_amount * 2 + i], &QLineEdit::textEdited, this, &TaskView::taskEdited);
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

void Comparison::write(QFile* file)
{
    // Записать общие для всех заданий свойства
    write_general(file);

    // Правильные ответы
    for (int i = 0; i < ans_amount; i++) {
        int32_t ans = comboBox[i]->currentIndex();
        file->write((char*)&(ans), sizeof(int32_t));
    }

}

void Comparison::read(QFile* file) {


    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильные ответы
    for (int32_t i = 0; i < ans_amount; i++) {

        int32_t ans = 0;
        file->read((char*)&ans, sizeof(uint32_t));
        comboBox[i]->setCurrentIndex(ans);
    }


}

QString Comparison::toString(bool solved) {
    QString string = "Укажите соответствие (цифрами 1-" + QString::number(optionsLinesEdit.size() / 2) + ")\n";
    string += ui->textEdit->toPlainText() + "\n";

    int max_len = 0; // Максимальная длина в первой колонке

    for (int i = 0; i < optionsLinesEdit.size(); i += 2) {
        if (max_len < optionsLinesEdit[i]->text().length())
            max_len = optionsLinesEdit[i]->text().length();
    }

    for (int i = 0; i < optionsLinesEdit.size(); i += 2) {

        if (solved)
            string += QString::number(comboBox[i / 2]->currentIndex() + 1) + ". " + optionsLinesEdit[i]->text();
        else
            string += QString("_ ") + optionsLinesEdit[i]->text();

        for (int j = optionsLinesEdit[i]->text().length(); j <= max_len; j++)
            string += " ";

        string += "     " + QString::number(i / 2 + 1) + QString(". ") + optionsLinesEdit[i + 1]->text() + '\n';
    }

    string += "Стоимость: " + QString::number(ui->priceSpinBox->value()) + ".";

    return string;
}




