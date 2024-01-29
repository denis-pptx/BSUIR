#include "MultipleChoice.h"

MultipleChoice::MultipleChoice(QWidget *parent) :
    Task(TaskType::MULTIPLE_CHOICE, parent)
{

    for (int i = 0; i < START_OPT_NUM; i++)
        plus();

}

Task* MultipleChoice::getCopy() {

    MultipleChoice* ret = new MultipleChoice;

    ret->copy_general(this);

    for (int i = 0; i < ret->ans_amount; i++) {
        ret->optionsCheckBoxes[i]->setChecked(this->optionsCheckBoxes[i]->isChecked());
        ret->optionsLinesEdit[i]->setText(this->optionsLinesEdit[i]->text());
    }

    return ret;
}

void MultipleChoice::plus() {

    optionsCheckBoxes.push_back(new QCheckBox);
    optionsLinesEdit.push_back(new QLineEdit);
    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);

    optionsLayout->addWidget(optionsCheckBoxes.back(), ans_amount, 0);
    optionsLayout->addWidget(optionsLinesEdit.back(), ans_amount, 1);

    connect(optionsCheckBoxes.back(), &QCheckBox::stateChanged, this, &TaskView::taskEdited);
    connect(optionsLinesEdit.back(), &QLineEdit::textEdited, this, &TaskView::taskEdited);

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

void MultipleChoice::write(QFile* file)
{
    // Записать общие для всех заданий свойства
    write_general(file);

    // Правильные ответы
    for (int i = 0; i < ans_amount; i++) {
        bool ans = optionsCheckBoxes[i]->isChecked();
        file->write((char*)&(ans), sizeof(bool));
    }
}

void MultipleChoice::read(QFile* file) {

    // Считать общие для всех заданий свойства
    read_general(file);

    // Правильные ответы
    for (int32_t i = 0; i < ans_amount; i++) {

        bool ans = 0;
        file->read((char*)&ans, sizeof(bool));

        optionsCheckBoxes[i]->setChecked(ans);
    }
}

QString MultipleChoice::toString(bool solved) {
    QString string = "Выберите ответ (возможно несколько) \n";

    string += ui->textEdit->toPlainText() + "\n";

    for (int i = 0; i < optionsLinesEdit.size(); i++) {

        if (solved && optionsCheckBoxes[i]->isChecked())
            string += "▣ " + optionsLinesEdit[i]->text();
        else
            string += "□ " + optionsLinesEdit[i]->text();

        string += "\n";
    }

    string += "Стоимость: " + QString::number(ui->priceSpinBox->value()) + ".";

    return string;
}
