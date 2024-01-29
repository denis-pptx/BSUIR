#include <iostream>
#include <typeinfo>
using namespace std;

// Базовый класс иерархии
class Expression {
public:
    virtual double evaluate() const = 0;
    virtual ~Expression() { };
};

// Класс для представления чисел
class Number : public Expression {
private:
    double value;
public:
    Number(double value)
        : value(value) {}

    double evaluate() const override {
        return value;
    }
};

// Класс для описания бинарной операции (+ - * /)
class BinaryOperation : public Expression {
private:
    Expression const *left;
    Expression const *right;
    char op;
public:
    BinaryOperation(Expression* left, char op, Expression* right)
        : left(left), right(right), op(op) {}

    ~BinaryOperation() override {
        delete left;
        delete right;
    }

    double evaluate() const override {
        if (op == '+')
            return left->evaluate() + right->evaluate();
        else if (op == '-')
            return left->evaluate() - right->evaluate();
        else if (op == '*')
            return left->evaluate() * right->evaluate();
        else if (op == '/')
            return left->evaluate() / right->evaluate();
        else
            exit(0);
    }
};

bool check_equals(Expression const *left, Expression const *right) {

    int* a = nullptr;
    int* b = nullptr;

    memcpy(&a, left, 4);
    memcpy(&b, right, 4);

    return a == b;

}
int main() {

     cout << endl << check_equals(new Number(0), reinterpret_cast<Expression*>(new int(0)));
    return 0;


    Expression* sube = new BinaryOperation(new Number(4.5), '+', new Number(-4));
    Expression* expr = new BinaryOperation(new Number(3), '/', sube);
    cout << expr->evaluate() << "\n";
    Expression* keke = new BinaryOperation(new BinaryOperation(new Number(4.5), '+', new Number(-4)), '*', new BinaryOperation(new Number(4.5), '+', new Number(-4)));
    cout << keke->evaluate() << "\n";
    delete expr;

    /////////////////////////////////

    cout.setf(ios_base::boolalpha);

    cout << endl << check_equals(new Number(0), new Number(0));
    cout << endl << check_equals(new BinaryOperation(new Number(0), '+', new Number(0)),
                                 new BinaryOperation(new Number(0), '+', new Number(0)));
    cout << endl << check_equals(new Number(0), new BinaryOperation(new Number(0), '+', new Number(0)));

}


