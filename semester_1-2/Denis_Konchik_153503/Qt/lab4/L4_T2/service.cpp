#include "ui_mainwindow.h"
#include "mainwindow.h"


// Разделить код на слова
void MainWindow::SplitCode() {

    splitedCode.clear();

    size_t row = 0;

    // Проходим строкой по вектору строк
    for (string line : code) {


        size_t i = 0;

        // Если встречаем оператор, то
        // отделяем его с двух сторон пробелами
        while (i < line.size()) {

            char smb = line[i];
            if (isSymb(smb)) {
                line.insert(i, ' ');
                line.insert((i += 2), ' ');
            }

            i++;
        }

        size_t column = 0;

        // Разделяем строку на отдельные слова и
        // закидываем в вектор пар "строка - координата"
        string word = string::Strtok::strtok(line.c_str(), " \n\t");

        while (word.size() != 0) {

            splitedCode.push_back({word, Coords(row, column++)});
            word = string::Strtok::strtok(nullptr, " \n\t");
        }

        string::Strtok::reset();
        row++;
    }

    // Прпоустить строки с комметариями
    SkipComments();

    // Найти пользовательские типы
    SearchUserTypes();

    // Найти функции и их прототипы
    SearchFunc();

}

// Пропустить строки с комментариями
void MainWindow::SkipComments() {


    // Поиск многострочных комментариев

    size_t i = 0;

    while(i < splitedCode.size()) {

        // Если встретили комбинацию "/*"
        if (i + 1 && splitedCode[i].first == '/' && splitedCode[i + 1].first == '*') {

            // Удаляем слова, пока не встретится комбинация "*/"
            while (i  + 1 < splitedCode.size() &&
                   !(splitedCode[i].first == '*' && splitedCode[i+1].first == '/'))
                splitedCode.erase(splitedCode.begin() + i);

            // Также удалить и "*/"
            if (i + 1 < splitedCode.size() &&
                    (splitedCode[i].first == '*' && splitedCode[i+1].first == '/')) {

                splitedCode.erase(splitedCode.begin() + i);
                splitedCode.erase(splitedCode.begin() + i);
            }

        } else {
            i++;
        }
    }

    // Проходим код на поиск однострчоных комментариев
    for (size_t i = 0; i < splitedCode.size(); i++) {


        // Если текущее слово и следующее слеши
        if (i + 1 < splitedCode.size() && splitedCode[i].first == '/' && splitedCode[i + 1].first == '/') {

            // Ряд, который стереть
            int row = splitedCode[i].second.row;


            // Убираем все слова в текущем ряду
            while (i < splitedCode.size() && splitedCode[i].second.row == row)
                splitedCode.erase(splitedCode.begin() + i);


            // Стать на предыдущее слово
            i--;
        }
    }





}

// Пропустить кавычки
void MainWindow::SkipQuotation(size_t& i) {

    size_t size = splitedCode.size();

    while (i < size && (splitedCode[i].first == '"' ||
           splitedCode[i].first == '\'')) {

        // Скипаем конструкции " ... "
        while (i < size && splitedCode[i].first == '"') {

            // Стать на следующее слово
            i++;

            while (i < size && splitedCode[i].first != '"')
                i++;

            // Стать на следующее слово
            i++;
        }

        // Скипаем конструкции ' ... '
        while (i < size && splitedCode[i].first == '\'') {

            // Стать на следующее слово
            i++;

            while (i < size && splitedCode[i].first != '\'')
                i++;

            // Стать на следующее слово
            i++;
        }
    }


}

// Поиск пользовательских типов данных
void MainWindow::SearchUserTypes() {

    userClasses.clear();
    userStructs.clear();
    baseTypes.clear();

    size_t i = 0;
    size_t size = splitedCode.size();
    while (i < size) {

        SkipQuotation(i);

        // Если слово "class" / "struct" в определении шаблона
        if (i < size && splitedCode[i].first == '<')
            i++;
        else if (i < size && splitedCode[i].first == "class") {

            // Перейди на следующее слово после "class"
            i++;

            // Если класс шаблонный, пропустить возможное < ... >
            if (i < size && splitedCode[i].first == '<') {

                while (i < size && splitedCode[i].first != '>')
                    i++;

                // Стать на имя класса
                i++;
            }

            userClasses.push_back(splitedCode[i].first);

        } else if (i < size && splitedCode[i].first == "struct") {

            // Перейди на следующее слово после "struct"
            i++;

            // Если структура шаблонная, пропустить возможное < ... >
            if (i < size && splitedCode[i].first == '<') {

                while (i < size && splitedCode[i].first != '>')
                    i++;

                // Стать на имя структуры
                i++;
            }

            userStructs.push_back(splitedCode[i].first);
        }

        i++;
    }


    // Добавить к типам модификаторы
    createTypesMod();

    // Объединить слова
    uniteWords();

}

// Оъединить слова
void MainWindow::uniteWords() {

    // Объединение типов данных из 2,3,4,5 слов в одно слово

    size_t i = 0;
    while (i < splitedCode.size()) {

        // Тип из пяти слов
        if (i + 4 < splitedCode.size()) {
            string fiveWords;
            fiveWords = splitedCode[i].first + " " + splitedCode[i + 1].first + " " +
                    splitedCode[i + 2].first + " " + splitedCode[i + 3].first + " " + splitedCode[i + 4].first;

            if (isType(fiveWords)) {
                splitedCode.insert(splitedCode.begin() + i, {fiveWords, splitedCode[i].second});
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
            }

            // Переименование колонок слов в этом ряду

            // Начиная от этой колонки
            size_t start_column = splitedCode[i].second.column;

            // В этом ряду
            size_t in_row = splitedCode[i].second.row;

            // Производим изменения
            size_t tmp_i = i;
            while ((size_t)splitedCode[tmp_i].second.row == in_row) {
                splitedCode[tmp_i].second.column = start_column++;
                tmp_i++;
            }


        }
        // Тип из четырех слов
        if (i + 3 < splitedCode.size()) {
            string fourWords;
            fourWords = splitedCode[i].first + " " + splitedCode[i + 1].first + " " +
                    splitedCode[i + 2].first + " " + splitedCode[i + 3].first;

            if (isType(fourWords)) {
                splitedCode.insert(splitedCode.begin() + i, {fourWords, splitedCode[i].second});
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
            }

            // Переименование колонок слов в этом ряду

            // Начиная от этой колонки
            size_t start_column = splitedCode[i].second.column;

            // В этом ряду
            size_t in_row = splitedCode[i].second.row;

            // Производим изменения
            size_t tmp_i = i;
            while ((size_t)splitedCode[tmp_i].second.row == in_row) {
                splitedCode[tmp_i].second.column = start_column++;
                tmp_i++;
            }


        }
        // Тип из трех слов
        if (i + 2 < splitedCode.size()) {
            string threeWords;
            threeWords = splitedCode[i].first + " " + splitedCode[i + 1].first + " " + splitedCode[i + 2].first;

            if (isType(threeWords)) {
                splitedCode.insert(splitedCode.begin() + i, {threeWords, splitedCode[i].second});
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
            }

            // Переименование колонок слов в этом ряду

            // Начиная от этой колонки
            size_t start_column = splitedCode[i].second.column;

            // В этом ряду
            size_t in_row = splitedCode[i].second.row;

            // Производим изменения
            size_t tmp_i = i;
            while ((size_t)splitedCode[tmp_i].second.row == in_row) {
                splitedCode[tmp_i].second.column = start_column++;
                tmp_i++;
            }
        }
        // Тип из двух слов
        if (i + 1 < splitedCode.size()) {
            string twoWords;
            twoWords = splitedCode[i].first + " " + splitedCode[i + 1].first;

            if (isType(twoWords)) {
                splitedCode.insert(splitedCode.begin() + i, {twoWords, splitedCode[i].second});
                splitedCode.erase(splitedCode.begin() + i + 1);
                splitedCode.erase(splitedCode.begin() + i + 1);
            }

            // Переименование колонок слов в этом ряду

            // Начиная от этой колонки
            size_t start_column = splitedCode[i].second.column;

            // В этом ряду
            size_t in_row = splitedCode[i].second.row;

            // Производим изменения
            size_t tmp_i = i;
            while ((size_t)splitedCode[tmp_i].second.row == in_row) {
                splitedCode[tmp_i].second.column = start_column++;
                tmp_i++;
            }
        }


        i++;
    }
}
// Добавить к типам типы с модификаторами
void MainWindow::createTypesMod() {


    size_t bT = baseTypesOrig.size();
    size_t uS = userStructs.size();
    size_t uC = userClasses.size();


    baseTypes = baseTypesOrig;
   // for (const auto& i : baseTypesOrig)
      //  baseTypes.push_back(i);

    // Добавляем в каждый вектор с типами
    // типы с модификаторами
    for (const auto& mod : modifers) {

        for (size_t i = 0; i < bT; i++)
            baseTypes.push_back(mod + " " + baseTypesOrig[i]);

        for (size_t i = 0; i < uS; i++)
            userStructs.push_back(mod + " " + userStructs[i]);

        for (size_t i = 0; i < uC; i++)
            userClasses.push_back(mod + " " + userClasses[i]);
    }
}

// Поиск функций
void MainWindow::SearchFunc() {

    // Очистить вектор прототипов
    funcProt.clear();

    // Очистить вектор перегрузок
    overloaded.clear();

    // Очистить координаты перегруженных функций
    coords.clear();

    // Число слов
    size_t size = splitedCode.size();

    size_t i = 0;

    // Перебор всех слов
    while (i < size) {

        SkipQuotation(i);

        // Временное i
        size_t i_tmp = i;

        // Прототип ли это
        bool isProt = false;


        // Если текущее слово - тип
        if (isType(splitedCode[i_tmp].first)) {


            // Стать на следующее слово
            i_tmp++;

            // Если тип возвращаемого значения - шаблонный класс / структура,
            // то пропустить <...>
            if (i_tmp < size && splitedCode[i_tmp].first == '<') {

                while (i_tmp < size && splitedCode[i_tmp].first != '>')
                    i_tmp++;

                i_tmp++;
            }

            // Если это указатель / l-value или r-value ссылка
            if (i_tmp < size && splitedCode[i_tmp].first == '*')
                i_tmp++;
            else if (i_tmp + 1 < size && splitedCode[i_tmp].first == '&' &&
                     splitedCode[i_tmp + 1].first == '&')
                i_tmp+= 2;
            else if (i_tmp < size && splitedCode[i_tmp].first == '&')
                i_tmp++;


            // Кейс с MainWindow:: и т.п
            while(i_tmp + 2 < size && isType(splitedCode[i_tmp].first) &&
                  splitedCode[i_tmp + 1].first == ':' && splitedCode[i_tmp + 2].first == ':') {

                // Пропустить два раза :
                i_tmp += 3;
            }


            // Имя функции в прототипе
            string funcName = splitedCode[i_tmp].first;

            // Координата имени функции
            Coords coords(splitedCode[i_tmp].second.row, splitedCode[i_tmp].second.column);

            // Переход на '('
            i_tmp++;


            // Если текущее слово — '('
            if (i_tmp < size && splitedCode[i_tmp].first == '(') {

                // Проверка на недопустимые символы в прототипе функции
                bool check = true;

                // Пока не найдем кобинацию ') {'
                while (i_tmp + 1 < size && splitedCode[i_tmp].first != ')' && splitedCode[i_tmp + 1].first != '{') {

                    // Если это ';' или ':', то это не функция
                    if (splitedCode[i_tmp].first == ':' ||
                            splitedCode[i_tmp].first == ';') {

                        check = false;
                        break;
                    }

                    // Стать на следующее слово
                    i_tmp++;
                }

                // Если это комбинация ') {',
                // то это функция
                if (check && i_tmp + 1 < size && splitedCode[i_tmp].first == ')' && splitedCode[i_tmp + 1].first == '{') {

                    // Это прототип
                    isProt = true;
                }

            }

            // Если это прототип
            if (isProt)
            {
                // Прототип функции
                string prototype;

                // Копируем в него слова от i до i_tmp (до конца)
                for (size_t j = i; j <= i_tmp; j++)
                    prototype += splitedCode[j].first + ' ';

                // Добавить прототип в вектор прототипов
                funcProt.push_back(pair(Prototype(funcName, prototype), coords));
                // Устанавливаем текущее слово i_tmp
                i = i_tmp;
            }
        }

        // Переход к следующему слову
        i++;
    }

    // Удаление повторяющихся прототипов
    for (size_t i = 0; funcProt.size() && i < funcProt.size() - 1; i++) {

        for (size_t j = i + 1; j < funcProt.size(); j++)
            if (funcProt[j].first.funcName == funcProt[i].first.funcName &&
                    funcProt[j].first.prototype == funcProt[i].first.prototype) {
                funcProt.erase(funcProt.begin() + j);
                i--;
                break;
            }
    }

 //   for (const auto& item : funcProt)
 //       qDebug() << item.first.prototype.c_str() << " " << item.first.funcName.c_str();






    // Поиск уникальный названий функций
    for (size_t i = 0; i < funcProt.size(); i++) {

        bool isUnique = true;

        for (size_t j = 0 ; j < overloaded.size(); j++) {
            if (overloaded[j].first == funcProt[i].first.funcName) {
                isUnique = false;
                break;
            }
        }

        if (isUnique)
            overloaded.push_back(pair(string(funcProt[i].first.funcName), vector<string>()));

    }

    // Поиск прототипов к функциям
    for (size_t i = 0; i < overloaded.size(); i++) {
        vector<Coords> tmp;
        for (size_t j = 0; j < funcProt.size(); j++)
            if (funcProt[j].first.funcName == overloaded[i].first) {
                overloaded[i].second.push_back(funcProt[j].first.prototype);
                tmp.push_back(funcProt[j].second);
            }
        coords.push_back(tmp);
    }

}

// Поиск изменений переменных
void MainWindow::SearchVarEdit() {

    // Очистить вектор
    coordsVarEdit.clear();

    // Если кода нет
    if (splitedCode.empty())
        return;

    // Вставить два пустых слова в начало и в конец
    int begin_row = splitedCode.front().second.row;
    int end_row = splitedCode.back().second.row;
    int end_column = splitedCode.back().second.column;

    splitedCode.insert(splitedCode.begin(), pair(string(""), Coords(begin_row, 0)));
    splitedCode.insert(splitedCode.begin(), pair(string(""), Coords(begin_row, 0)));

    splitedCode.push_back(pair(string(""), Coords(end_row, ++end_column)));
    splitedCode.push_back(pair(string(""), Coords(end_row, ++end_column)));

    // Число слов
    size_t size = splitedCode.size();

    size_t i = 0;

    while(i < size) {


        // Если много звездочек от указателей подряд
        if (i > 0 && i + 1 < size && splitedCode[i].first == '*' && splitedCode[i + 1].first == '*') {
            // Пропустить их
            while (i < size && splitedCode[i].first == '*')
                i++;
        }

        // Если арифметическая операция
        if (i > 0 &&  i + 1 < size &&
                isArithm(splitedCode[i].first) && !isType(splitedCode[i - 1].first) && !isType(splitedCode[i + 1].first)) {

            coordsVarEdit.push_back(splitedCode[i].second);

            // Если это составное присваивание
            if (splitedCode[i + 1].first == "=") {
                // Перейти на следующее слово после "="
                // т.к. сейчас стоим на арифметическом операторе
                i+= 2;
            }
            // Если подряд два одинаковых оператора
            else if (splitedCode[i].first == splitedCode[i+1].first) {

                // Если это не инкремент / декремент
                if(!(splitedCode[i].first == "+" || splitedCode[i].first == "-"))
                    coordsVarEdit.pop_back();

                i+= 2;
            }
            else {
                i++;
            }


        }
        // Если "!"
        else if (i > 0 &&  i + 1 < size &&
                 splitedCode[i].first == '!' && !isType(splitedCode[i - 1].first) && !isType(splitedCode[i + 1].first)) {

            coordsVarEdit.push_back(splitedCode[i].second);

            i++;
        }
        // Если "="
        else if (i > 0 &&  i + 1 < size &&
                 splitedCode[i].first == '=' && !isType(splitedCode[i - 1].first) && !isType(splitedCode[i + 1].first)) {

            // Если это "=="
            if (splitedCode[i + 1].first == "=") {

                // Перейти на следующее слово после "=="
                // сейчас мы стояли на первом "="
                i += 2;
            }
            else {
                coordsVarEdit.push_back(splitedCode[i].second);
                i++;
            }
        }
        else {

            // Переход на следующее слово
            i++;
        }
    }

    // Удалить добавленное
    splitedCode.erase(splitedCode.begin());
    splitedCode.erase(splitedCode.begin());

    splitedCode.pop_back();
    splitedCode.pop_back();

}

// Поиск переменных и их начальных значений
void MainWindow::SearchVariables() {

    // Очистить вектор с переменными
    variables.clear();

    typesDeclare.clear();

    // Число слов
    size_t size = splitedCode.size();

    size_t i = 0;

    while(i < size) {


        // Если это слово "class", то пропускаем до '{'
        if (splitedCode[i].first == "class" ||
                splitedCode[i].first == "struct") {

            while (i < size && splitedCode[i].first != '{')
                i++;

            i++;
        }

        // Если это конструктор, то пропускаем до {
        if (i+3 < size && isType(splitedCode[i].first) &&
                splitedCode[i+1].first == ':' && splitedCode[i+2].first == ':' &&
                splitedCode[i+3].first == splitedCode[i].first) {

            while(i<size && splitedCode[i].first != '{')
                i++;

            i++;
        }
        else if (i < size && isType(splitedCode[i].first) &&
                 splitedCode[i+1].first == '(' && splitedCode[i+2].first == ')') {

            while(i<size && splitedCode[i].first != '{')
                i++;

            i++;
        }

        // Кейс с MainWindow:: и т.п
        if (i + 2 < size && isType(splitedCode[i].first) &&
                splitedCode[i + 1].first == ':' && splitedCode[i + 2].first == ':') {

            while(i + 2 < size && isType(splitedCode[i].first) &&
                  splitedCode[i + 1].first == ':' && splitedCode[i + 2].first == ':') {

                // Пропустить два раза :
                i += 3;
            }

            // Пропустить до {

            while(i<size && splitedCode[i].first != '{')
                i++;

            i++;

        }

        // Временное i
        size_t i_tmp = i;

        // Если это тип
        if (i_tmp < size && isType(splitedCode[i_tmp].first)) {


            // И слева либо ничего либо ; либо символ
            if ((i_tmp == 0) || (i_tmp >= 1 && isSymb(splitedCode[i_tmp - 1].first))) {

                // Стать на следующее слово
                i_tmp++;

                // Если тип - шаблонный класс / структура,
                // то пропустить <...>
                if (i_tmp < size && splitedCode[i_tmp].first == '<') {

                    while (i_tmp < size && splitedCode[i_tmp].first != '>')
                        i_tmp++;

                    i_tmp++;
                }

                // Если это указатель / l-value или r-value ссылка
                if (i_tmp < size && splitedCode[i_tmp].first == '*')
                    i_tmp++;
                else if (i_tmp + 1 < size && splitedCode[i_tmp].first == '&' &&
                         splitedCode[i_tmp + 1].first == '&')
                    i_tmp+= 2;
                else if (i_tmp < size && splitedCode[i_tmp].first == '&')
                    i_tmp++;


                // Тут уже стоим на имени переменной

                // Проверка на случай, когда функция
                // член класса и объявлена вне его
                // void MainWindow::func(...) ... ... ...
//                while (i_tmp + 3 < size && isType(splitedCode[i_tmp].first) &&
//                       splitedCode[i_tmp + 1].first == ':' && splitedCode[i_tmp + 2].first == ':' &&
//                       (isFuncName(splitedCode[i_tmp + 3].first) || isType(splitedCode[i_tmp + 3].first))) {

//                    i_tmp += 3;
//                }

                // Если это имя функции, то пропускаем слова до {
                if (isFuncName(splitedCode[i_tmp].first)) {

                    while (i_tmp < size && splitedCode[i_tmp].first != '{')
                        i_tmp++;
                }
                else {

                    // Тип переменной
                    string varType;
                    for (size_t j = i; j < i_tmp; j++)
                        varType += splitedCode[j].first + " ";


                    //variables

                    // Вся стркоа с переменной
                    string varStr = varType;

                    // Доходим до конца строки с переменной
                    while(i_tmp < size && splitedCode[i_tmp].first != ';') {
                        varStr+= splitedCode[i_tmp].first + " ";
                        i_tmp++;
                    }

                 //   qDebug() << varStr.c_str();

                    variables.push_back(pair(varType, varStr));

                    // Координата имени переменной
                    Coords coords(splitedCode[i_tmp].second.row, splitedCode[i_tmp].second.column);
                }


            }
        }

        // Стать на следующее слово
        i = i_tmp;
        i++;
    }



    // Сет с типами
    QSet<QString> types;

    for (const auto& i : variables)
        types.insert(i.first.c_str());

    for (const auto& it : types) {


        // Добавить в вектор тип
        typesDeclare.push_back(pair(string(it.toStdString().c_str()), vector<string>()));

        for (const auto& strVar : variables) {
            if (strVar.first == typesDeclare.back().first)
                typesDeclare.back().second.push_back(strVar.second);
        }
    }
}

// Поиск ошибок
void MainWindow::SearchMistakes() {

    // Поиск if(), if { ... }, while { ... }, while(true), while(false)
    // #endif для каждого #if

    // Очистить вектор ошибок
    mistakes.clear();

    // Стек для координат открывающих #if
    std::stack<size_t> stck;

    // Число слов
    size_t size = splitedCode.size();
    size_t i = 0;

    while (i < size) {

        SkipQuotation(i);

        size_t row = splitedCode[i].second.row;

        // Если текущее слово - "if"
        if (splitedCode[i].first == "if") {

            // Если это "if ()"
            if (i + 2 < size &&
                    splitedCode[i + 1].first == "(" && splitedCode[i + 2].first == ")") {

                string mistake = "if ( ) { ... } ";

                mistakes.push_back(pair(mistake, row));

                // Стоим на if    (if () { ... })
                // перепрыгиваем на "{"
                i += 3;
            }
            // Если это "if { ... }"
            else if (i + 1 < size && splitedCode[i + 1].first == "{") {

                string mistake = "if { ... } ";

                mistakes.push_back(pair(mistake, row));

                // Стоим на if (if { ... })
                // перепригиваем на {
                i++;
            }

        }
        // Если текущее слово - "while"
        else if (splitedCode[i].first == "while") {

            // Если это "while(true / false)"
            if (i + 3 < size &&
                    splitedCode[i + 1].first == "(" &&
                    (splitedCode[i + 2].first == "true" || splitedCode[i + 2].first == "false") &&
                    splitedCode[i + 3].first == ")") {

                string bl = splitedCode[i + 2].first;
                string mistake = "while (" + bl + ") { ... } ";

                mistakes.push_back(pair(mistake, row));

                // Стоим на while (while(true / false) { ... } )
                // перепригиваем на "{"
                i += 4;
            }
            // Если это "while { ... }
            else if (i + 1 < size && splitedCode[i + 1].first == "{") {

                string mistake = "while { ... } ";

                mistakes.push_back(pair(mistake, row));

                // Стоим на while (while { ... })
                // перепрыгиваем на "{"
                i++;
            }

        }
        // Если текущее слово "#"
        else if (i < size && splitedCode[i].first == "#") {

            // "Если это if"
            if (i + 1 < size &&
                    splitedCode[i + 1].first.size() >= 2 &&
                    splitedCode[i + 1].first[0] == 'i' && splitedCode[i + 1].first[1] == 'f') {
                stck.push(row);
                i++;
            }
            else if (i + 1 < size && !stck.empty() && splitedCode[i + 1].first == "endif") {
                stck.pop();
                i++;
            }
            else if (i + 1 < size && stck.empty() && splitedCode[i + 1].first == "endif") {
                stck.push(row);
                i++;
            }
        }
        // Стать на следующее слово
        i++;
    }

    // Проверка на закрытие директив "#if...#

    // Стек в обратном порядке
    std::stack<size_t> rev;

    while(!stck.empty()) {
        rev.push(stck.top());
        stck.pop();
    }

    while (!rev.empty()) {
        mistakes.push_back(pair(string("#if ... #endif"), rev.top()));
        rev.pop();
    }





}

// Число классов
size_t MainWindow::CountClasses() {

    size_t classAmount = 0;

    // Число слов
    size_t size = splitedCode.size();

    size_t i = 0;

    while (i < size) {

        SkipQuotation(i);

        // Если текущее слово - имя функции, то пропустить до {
        if (isFuncName(splitedCode[i].first)) {

            while (i < size && splitedCode[i].first != '{')
                i++;
        }

        // Временное i
        size_t i_tmp = i;

        bool isClass = false;


        // Если текущее слово - класс
        if (isUserClass(splitedCode[i_tmp].first)) {

            // Стать на следующее слово
            i_tmp ++;

            // Пропустить возможные < ... >
            if (i_tmp < size && splitedCode[i_tmp].first == '<') {

                while (i_tmp < size && splitedCode[i_tmp].first != '>')
                    i_tmp++;

                // Стать на следующее слово после '>'
                i_tmp++;
            }

            // Если это указатель
            if (i_tmp < size && splitedCode[i_tmp].first == '*') {

                // Стать на имя указателя
                i_tmp++;

                // Стать на знак после имени
                i_tmp++;

                // Если это '='
                if (i_tmp < size && splitedCode[i_tmp].first == '=') {

                    // Стать на слово после '='
                    i_tmp++;

                    // Если это "new"
                    if (i_tmp < size && splitedCode[i_tmp].first == "new") {

                        // Доходим до ';'
                        while (i_tmp < size && splitedCode[i_tmp].first != ';')
                            i_tmp++;

                        // Стать на символ перед ';'
                        i_tmp--;

                        // Если это не ']', как у массива
                        if (i_tmp < size && splitedCode[i_tmp].first != ']')
                            isClass = true;
                    }
                    // Иначе
                    //else {
                    //    isClass = true;
                    //}
                }
            }
            // Иначе - это имя класса
            else {

                // Стать на следующее слово после имени класса
                i_tmp++;

                // Если это ';' или '='
                if (i_tmp < size &&  (splitedCode[i_tmp].first == ';' || splitedCode[i_tmp].first == '=')) {
                    isClass = true;
                }
                // Если это '('
                else if (splitedCode[i_tmp].first == '(') {

                    if(i_tmp > 0 && !isFuncName(splitedCode[i_tmp - 1].first))
                        isClass = true;
                }
            }

        }


        // Если действительно был класс
        if (isClass) {
            classAmount++;
            i = i_tmp;
        }

        i++;
    }

    return classAmount;
}

// Число структур
size_t MainWindow::CountStructs() {

    size_t structAmount = 0;

    // Число слов
    size_t size = splitedCode.size();

    size_t i = 0;

    while (i < size) {

        SkipQuotation(i);

        // Если текущее слово - имя функции, то пропустить до {
        if (isFuncName(splitedCode[i].first)) {

            while (i < size && splitedCode[i].first != '{')
                i++;
        }

        // Временное i
        size_t i_tmp = i;

        bool isStruct = false;


        // Если текущее слово - структура
        if (isUserStruct(splitedCode[i_tmp].first)) {

            // Стать на следующее слово
            i_tmp ++;

            // Пропустить возможные < ... >
            if (i_tmp < size && splitedCode[i_tmp].first == '<') {

                while (i_tmp < size && splitedCode[i_tmp].first != '>')
                    i_tmp++;

                // Стать на следующее слово после '>'
                i_tmp++;
            }

            // Если это указатель
            if (i_tmp < size && splitedCode[i_tmp].first == '*') {

                // Стать на имя указателя
                i_tmp++;

                // Стать на знак после имени
                i_tmp++;

                // Если это '='
                if (i_tmp < size && splitedCode[i_tmp].first == '=') {

                    // Стать на слово после '='
                    i_tmp++;

                    // Если это "new"
                    if (i_tmp < size && splitedCode[i_tmp].first == "new") {

                        // Доходим до ';'
                        while (i_tmp < size && splitedCode[i_tmp].first != ';')
                            i_tmp++;

                        // Стать на символ перед ';'
                        i_tmp--;

                        // Если это не ']', как у массива
                        if (i_tmp < size && splitedCode[i_tmp].first != ']')
                            isStruct = true;
                    }
                    // Иначе
                    //else {
                    //    isStruct = true;
                    //}
                }
            }
            // Иначе - это имя структуры
            else {

                // Стать на следующее слово после имени структуры
                i_tmp++;

                // Если это ';' или '='
                if (i_tmp < size && (splitedCode[i_tmp].first == ';' || splitedCode[i_tmp].first == '=')) {
                    isStruct = true;
                }
                // Если это '('
                else if (splitedCode[i_tmp].first == '(') {

                    if(i_tmp > 0 && !isFuncName(splitedCode[i_tmp - 1].first))
                        isStruct = true;
                }

            }

        }


        // Если действительно был класс
        if (isStruct) {
            structAmount++;
            i = i_tmp;
        }

        i++;
    }

    return structAmount;
}

// Число массивов
size_t MainWindow::CountArrays() {

    size_t arrayAmount = 0;

    // Перебор слов на поиск массивов
    size_t size = splitedCode.size();
    size_t i = 0;

    while (i < size) {

        SkipQuotation(i);

        // Если текущее слово - имя функции, то пропустить до {
        if (isFuncName(splitedCode[i].first)) {

            while (i < size && splitedCode[i].first != '{')
                i++;
        }

        // Временное i
        size_t i_tmp = i;

        bool isArray = false;


        // Если текущее слово - тип
        if (isType(splitedCode[i_tmp].first)) {

            // Стать на следующее слово
            i_tmp++;

            // Пропустить возможные < ... >
            if (i_tmp < size && splitedCode[i_tmp].first == '<') {

                while (i_tmp < size && splitedCode[i_tmp].first != '>')
                    i_tmp++;

                // Стать на следующее слово после '>'
                i_tmp++;
            }

            // Если это указатель
            if (i_tmp < size && splitedCode[i_tmp].first == '*') {

                // Стать на имя указателя
                i_tmp++;

                // Стать на знак после имени
                i_tmp++;

                // Если это '='
                if (i_tmp < size && splitedCode[i_tmp].first == '=') {

                    // Стать на слово после '='
                    i_tmp++;

                    // Если это "new"
                    if (i_tmp < size && splitedCode[i_tmp].first == "new") {

                        // Доходим до ';'
                        while (i_tmp < size && splitedCode[i_tmp].first != ';')
                            i_tmp++;

                        // Стать на символ перед ';'
                        i_tmp--;

                        // Если это ']'
                        if (i_tmp < size && splitedCode[i_tmp].first == ']')
                            isArray = true;
                    }

                }
            }
            // Иначе - это имя массива
            else {

                // Стать на следующее слово после имени массива
                i_tmp++;

                // Если это '['
                if (i_tmp < size && splitedCode[i_tmp].first == '[')
                    isArray = true;
            }

        }

        // Если это был массив
        if (isArray) {
            arrayAmount++;
            i = i_tmp;
        }


        i++;

    }

    return arrayAmount;
}

// Локальные переменные и их координаты
void MainWindow::CountLocalVariable() {

    coordsVar.clear();

    // Перебор слов на поиск локальных переменных
    size_t size = splitedCode.size();
    size_t i = 0;

    // Стек для подсчета скобок
    // в блоке кода мы или нет
    std::stack<char> branches;

    while (i < size) {

        SkipQuotation(i);

        // Если текущее слово — '{'
        if (i < size && (splitedCode[i].first == '{' || (!branches.empty() && branches.top() == '{'))) {

            if (splitedCode[i].first == '{')
                branches.push('{');

            // Временное i
            size_t i_tmp = i;

            // Если предыдущее слово - ')' ,
            // то есть закрытие параметров фукнкции
            if (i_tmp > 0 && splitedCode[i_tmp - 1].first == ')') {

                // Стать на слово ')'
                i_tmp--;

                // Стать на слово до ')'
                i_tmp--;

                // Пока не дойдем до открытия параметров функции — '('
                while (i_tmp > 0 && splitedCode[i_tmp].first != '(') {


                    // Если встретили ')', то пропустить блок от
                    // соответствующей '(' до этой ')'
                    if (splitedCode[i_tmp].first == ')') {

                        std::stack<char> stack;

                        stack.push(')');

                        // Стать на слово до ложной ')'
                        i_tmp--;

                        while (!stack.empty() && i_tmp > 0) {

                            if (splitedCode[i_tmp].first == ')')
                                stack.push(')');
                            else if (splitedCode[i_tmp].first == '(')
                                stack.pop();


                            i_tmp--;

                        }
                    }


                    // Если это тип и предыдущий символ — ',' или '('
                    if ((isType(splitedCode[i_tmp].first) && i_tmp > 0) &&
                            (splitedCode[i_tmp - 1].first == ',' || splitedCode[i_tmp - 1].first == '(')) {

                            coordsVar.push_back(splitedCode[i_tmp].second);
                    }

                    // Перейти на слово назад
                    i_tmp--;
                }
            }

            // Пока не дойдем до завершения блока кода
            while (i < size && splitedCode[i].first != '}') {

                // Если это тип
                if (isType(splitedCode[i].first)) {
                    coordsVar.push_back(splitedCode[i].second);

                    // Пока не дойдем до конца строки — ';'
                    while (i < size && splitedCode[i].first != ';')
                        i++;

                }




                // Стать на следующее слово
                i++;


            }

            // Если текущее слово - закрывающая скобка
            if(i < size && !branches.empty() && splitedCode[i].first == '}')
                branches.pop();

        }



        // Стать на следующее слово
        i++;




    }
}

// Ветвления
void MainWindow::CountBranches() {

    branching.clear();

    // Перебор слов на поиск ветвлений
    size_t size = splitedCode.size();
    size_t i = 0;

    // Стек для скобочек
    std::stack<char> bracket;

    while (i < size) {

        SkipQuotation(i);

        // Если текущее слово - имя функции или "struct" или "class", то пропустить до {
        if (isFuncName(splitedCode[i].first)
                || splitedCode[i].first == "struct" || splitedCode[i].first == "class") {

            while (i < size && splitedCode[i].first != '{')
                i++;

            i++;
        }

        // Если текущее слово — "for" / "while" / "do", то пропускаем
        // слова до '{'
        if (splitedCode[i].first == "for" || splitedCode[i].first == "while" || splitedCode[i].first == "do") {

            while (i < size && splitedCode[i].first != '{')
                i++;

            // Стать на следующее слово
            i++;
        }

        // Если тукщее слово "if" / "else if"
        if ((i < size && splitedCode[i].first == "if") ||
                (i + 1 < size && splitedCode[i].first == "else" && splitedCode[i + 1].first == "if")) {

            // Пока не дойдем до "{"
            while (i < size && splitedCode[i].first != "{") {
                i++;
                SkipQuotation(i);
            }

            // Если это "{"
            if (i < size && splitedCode[i].first == "{") {
                bracket.push('{');
                branching.push_back(pair(bracket.size(), splitedCode[i].second));
            }
        }
        // Если это "else"
        else if (splitedCode[i].first == "else") {

            // Если следующее слово "{"
            if (i + 1 < size && splitedCode[i+1].first == "{"){
                bracket.push('{');
                branching.push_back(pair(bracket.size(), splitedCode[i].second));
            }
        }
        // Если это "}"
        else if (i < size && splitedCode[i].first == '}' && bracket.size())
            bracket.pop();

        // Стать на следующее слово
        i++;

    }

}
