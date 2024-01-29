#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>


// Максимальная длина вопроса
#define MAX_QUESTION_LEN 2000

class TextEdit : public QTextEdit {
private:
    void onTextChanged() {

        if (toPlainText().length() > MAX_QUESTION_LEN)
            textCursor().deletePreviousChar();
    }
public:
    TextEdit(QWidget* parent = nullptr) : QTextEdit(parent) {

       connect(this, &QTextEdit::textChanged, this, &TextEdit::onTextChanged);
    }
};

#endif // TEXTEDIT_H
