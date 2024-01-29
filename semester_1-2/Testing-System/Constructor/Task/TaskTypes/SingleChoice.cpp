#include "SingleChoice.h"



SingleChoice::SingleChoice(QWidget *parent) :
    Task(TaskType::SINGLE_CHOICE, parent)
{

    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

    optionsRadioButtons[0]->setChecked(true);

}

Task* SingleChoice::getCopy() {
    SingleChoice* ret = new SingleChoice;

    ret->copy_general(this);

    for (int i = 0; i < ret->ans_amount; i++) {
        ret->optionsRadioButtons[i]->setChecked(this->optionsRadioButtons[i]->isChecked());
        ret->optionsLinesEdit[i]->setText(this->optionsLinesEdit[i]->text());
    }

    return ret;
}

void SingleChoice::plus() {

    optionsRadioButtons.push_back(new QRadioButton);
    optionsLinesEdit.push_back(new QLineEdit);


    optionsLayout->addWidget(optionsRadioButtons.back(), ans_amount, 0);
    optionsLayout->addWidget(optionsLinesEdit.back(), ans_amount, 1);


    connect(optionsRadioButtons.back(), &QRadioButton::clicked, this, &TaskView::taskEdited);
    connect(optionsLinesEdit.back(), &QLineEdit::textEdited, this, &TaskView::taskEdited);

    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);

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

void SingleChoice::write(QFile* file)
{
    // Записать общие для всех заданий свойства
    write_general(file);

    // Правильный ответ
    for (int i = 0; i < ans_amount; i++)
        if (optionsRadioButtons[i]->isChecked()) {
            file->write((char*)&i, sizeof(int32_t));
            break;
        }
}

void SingleChoice::read(QFile* file) {

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильный ответ
    int32_t rightAnswer;
    file->read((char*)&rightAnswer, sizeof(int32_t));

    optionsRadioButtons[rightAnswer]->setChecked(true);
}

QString SingleChoice::toString(bool solved) {
    QString string = "Выберите ответ (единственный) \n";

    string += ui->textEdit->toPlainText() + "\n";

    for (int i = 0; i < optionsLinesEdit.size(); i++) {

        if (solved && optionsRadioButtons[i]->isChecked())
            string += "◉ " + optionsLinesEdit[i]->text();
        else
            string += "○ " + optionsLinesEdit[i]->text();

        string += "\n";
    }

    string += "Стоимость: " + QString::number(ui->priceSpinBox->value()) + ".";

    return string;
}






