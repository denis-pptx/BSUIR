#include "Entry.h"


Entry::Entry(QWidget *parent) :
    Task(TaskType::ENTRY, parent)
{

    optionsLinesEdit.push_back(new QLineEdit);
    optionsLinesEdit.back()->setMaxLength(MAX_POINT_LEN);

    optionsLayout->addWidget(optionsLinesEdit.back(), 0, 0);

    connect(optionsLinesEdit.back(), &QLineEdit::textEdited, this, &TaskView::taskEdited);

    optionsWidget->setLayout(optionsLayout);

    ui->scrollArea->setWidget(optionsWidget);

    ui->plusButton->setEnabled(false);
    ui->minusButton->setEnabled(false);

    ans_amount = 1;
}

Task* Entry::getCopy() {

    Entry* ret = new Entry();

    ret->optionsLinesEdit.back()->setText(this->optionsLinesEdit.back()->text());
    ret->copy_general(this);

    return ret;
}

void Entry::write(QFile* file)
{
    // Записать общие для всех заданий свойства
    write_general(file);

}

void Entry::read(QFile* file) {

    // Считать общие для всех заданий свойства
    read_general(file);
}

QString Entry::toString(bool solved) {
    QString string = "Напишите ответ \n";

    string += ui->textEdit->toPlainText() + "\n";

    if (solved)
        string += "Ответ: " + optionsLinesEdit.back()->text() + ".";
    else
        string += "Ответ: _________________";

    string += "\nСтоимость: " + QString::number(ui->priceSpinBox->value()) + ".";

    return string;
}
