#ifndef POLISHENTRY_H
#define POLISHENTRY_H


#include <QString>
#include <QDebug>
#include "stack.h"
using namespace my_stack;


class PolishEntry
{
private:
    double numbers[5];
    QString infix;
    QString postfix;
    double answer;

    // Приоеритет операций
    int priority(QString symbol) {
        if (symbol == '+' || symbol == '-')
            return 1;

        if (symbol == '*' || symbol == '/')
            return 2;

        return 0;
    }

    // Из инфиксной формы в постфиксную
    QString convert(QString& infix)
    {
        QString postfix = "";

        // Стек для операций
        stack<QChar> s;

        int i = 0;
        // Пока не закончилась строка
        while (infix[i] != '\0')
        {
            // Если операнд, то добавить к выражению
            if (infix[i] >= 'a' && infix[i] <= 'z')
            {
                postfix += infix[i];
                i++;
            }
            // Если открывающая скобка,
            // то добавить её в стек
            else if (infix[i] == '(')
            {
                s.push(infix[i]);
                i++;
            }
            // Если закрывающая собка, то выталкивать знаки,
            // пока не встретится открывающая скобка
            else if (infix[i] == ')')
            {
                while (s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
                i++;
            }
            // Если знак, то выталкивать знаки с приоритетом
            // большим или равным, чем у этого знака
            else
            {
                while (!s.empty() && (priority(infix[i]) <= priority(s.top()))) {
                    postfix += s.top();
                    s.pop();
                }

                // Добавить знак в стек
                s.push(infix[i]);
                i++;
            }
        }

        // Вытолкнуть и добавить все оставшееся
        while (!s.empty()) {
            postfix += s.top();
            s.pop();
        }

        return postfix;
    }

    // Операция
    double execute(char op, double left, double right) {

        if (op == '+')
            return left + right;
        else if (op == '-')
            return left - right;
        else if (op == '*')
            return left * right;
        else if (right == 0)
            throw(std::invalid_argument("division by zero"));
        else
            return left / right;
    }

    // Разобрать запись
    double parsePostfix(QString& postfix) {

        // Стек для чисел
        stack<double> s;

        for (int i = 0; i < postfix.size(); i++) {

            char symbol = postfix[i].toLatin1();

            // Если символ знак, то посчитать верхние два элемента в стеке
            // этим знаком и и засунуть результат в стек
            if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
                double right = s.top(); s.pop();
                double left = s.top(); s.pop();

                s.push(execute(symbol, left, right));
            }
            // Если символ цифра, то засунуть в стек
            else {
                double value = numbers[symbol - 'a'];
                s.push(value);
            }
        }

        // Единственный элемент в стеке - ответ
        return s.top();
    }

    // Корректно ли выражение
    bool isCorrect() {
        QString expression = infix;

        int bracket = 0;
        for (int i = 0; i < expression.size(); i++)
            if (expression[i] == '(')
                bracket++;
             else if (expression[i] == ')')
                bracket--;

        if (bracket != 0)
            return false;

        if (expression.size() == 0)
            return false;


        for (int i = 0; i < expression.size(); i++) {

            QChar c = expression[i];
            if (!(c == '+' || c == '-' || c == '/' || c == '*' || c == '(' || c == ')' ||
                  ('a' <= c && c <= 'e')))
                return false;

            QChar next = expression[i + 1];
            if ('a' <= c && c <= 'e' &&
                    (('a' <= next && next <= 'e') || next == '('))
                return false;

        }

        return true;
    }

public:

    PolishEntry(double* numbers, QString infix) {

        for (int i = 0; i < 5; i++)
            this->numbers[i] = numbers[i];
        this->infix = infix;

        if (!isCorrect())
            throw(std::exception());

        postfix = convert(infix);
        answer = parsePostfix(postfix);
    }

    // Заменить на другие данные
    void reset(double* numbers, QString infix) {
        for (int i = 0; i < 5; i++)
            this->numbers[i] = numbers[i];
        this->infix = infix;

        postfix = convert(infix);
        answer = parsePostfix(postfix);
    }

    double* getNumbers() { return numbers; }
    QString getInfix() { return infix; }
    QString getPostfix() { return postfix; }
    double getAnswer() { return answer; }

    QString getColumnByIndex(int index) {
        enum Columns { Infix, Postfix, a, b, c, d, e, Resault };
        Columns column = (Columns)index;

        if (column == Infix)
            return infix;
        else if (column == Postfix)
            return postfix;
        else if (column == Resault)
            return QString::number(answer, 'f', 2);

        return QString::number(numbers[column - 2]);
    }
};
#endif // POLISHENTRY_H
