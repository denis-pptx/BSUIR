// Лабораторная 4, задача 10. Выполнена: Кончик Д. С.

/*
Построить магический квадрат любого порядка, используя любой алгоритм.
Выделение памяти через функции языка С.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int input_N();
void change(int* a, int* b);

// Квадрат
int** odd_magic(int** magic, int val); // Нечетный 
int** even_even_magic(int** magic, int val); // Четно-четный (4*k)
int** even_noeven_magic(int** magic, int val); // Четно-нечетный (4*k + 2)

int main()
{
    setlocale(LC_ALL, "Rus");

    // Ввод данных
    int N;
    do {
        cout << "Введите порядок магического квадрата (> 2): ";
        N = input_N();
    } while (N <= 2);
   
  


    // Магический квадрат N * N
    int** magic = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        magic[i] = (int*)malloc(N * sizeof(int));
    }

    // Построение квадрата в зависимости от четности порядка
    if (N % 2 == 1) {
        magic = odd_magic(magic, N);
    } else if (N % 4 == 0) {
        magic = even_even_magic(magic, N);
    } else if (N % 2 == 0 && N % 2 != 4) {
        magic = even_noeven_magic(magic, N);
    } else {
        cout << "???";
    }
    
    // Вывод магического квадрата
    int max = N * N; // Максимальный элемент
    int digit = 0; // Число цифр в максимальном элементе
    while (max) {
        digit++;
        max /= 10;
    } digit += 2; // Ширина вывода



    cout << "\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << setw(digit) << magic[i][j];
        }
        cout << "\n";
    }
    

    
    cout << "\nСуммы в строках: \n";
    int S = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            S += magic[i][j];
        }
        cout << S << endl;
        S = 0;
    }

    cout << "\nСуммы в столбцах: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            S += magic[j][i];
        }
        cout << S << endl;
        S = 0;
    }

    cout << "\nСумма в главной диагонали: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                S += magic[i][j];
            }
        }
    }
    cout << S << endl;
    S = 0;

    cout << "\nСумма в побочной диагонали: \n";
    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            if (i + j == N - 1) {
                S += magic[i][j];
            }
        }
    }
    cout << S << endl;


    for (int i = 0; i < N; i++) {
        free(magic[i]);
    } free(magic);

    return 0;
}

int input_N() {
    int x;

    // Пока не будет введено корректное значение
    while (true) {
        cin >> x;

        // Пропуск пробелов после элемента
        while (cin.peek() == ' ')
            cin.ignore(1, ' ');

        // Проверка предыдущего извлечения данных из буфера
        // Извлечение неудачное / удачное, но остались неизвлеченные символы / число отрицательное
        if (cin.fail() || cin.peek() != '\n' || x <= 0) {
            cin.clear(); // Возвращение в обычный режим работы
            cin.ignore(10000, '\n'); // Игнор 'n' символов до Enter
            cout << "Повторите ввод: ";
        }
        else {
            return x;
        }
    }
}

int** odd_magic(int** magic, int val) {
    

    // МЕТОД ТЕРРАС

    int N = val;

    int N_full = N + (N / 2) * 2; // Длина стороны квадрата 'full'
    // 'full' - квадрат, вмещающий магический квадрат и наложенный на него под углом 45° такой же квадрат
    int** full = (int**)malloc(N_full * sizeof(int*));
    for (int i = 0; i < N_full; i++) {
        full[i] = (int*)malloc(N_full * sizeof(int));
    }

    // Заполнение квадрата 'full' нулями
    for (int i = 0; i < N_full; i++) {
        for (int j = 0; j < N_full; j++) {
            full[i][j] = 0;
        }
    }

    // Заполнение квадрата 'full'
    // m, n - координаты элемента в квадрате под углом 45°
    int m = N_full / 2, m_save;
    int n = 0, n_save;

    // start, end - от какого до какого числа идут элементы в данной строке квадрата под углом 45°  
    int start = 1;
    int end = N;

    for (int i = 0; i < N; i++) {
        m_save = m; n_save = n; // Координаты элемента в предыдущей итерации
        for (int j = start; j <= end; j++) {
            full[m--][n++] = j;
        }
        start += N; end += N;
        m = m_save + 1; n = n_save + 1;
    }

    // Смещение террас для получения магического квадрата в квадрате 'full'
    int terrace_h = N / 2; // Высота террасы

    // Левая терраса
    for (int i = terrace_h + 1; i <= terrace_h + N - 2; i++) {
        for (int j = 0; j < terrace_h; j++) {
            if (full[i][j] != 0) {
                full[i][j + N] = full[i][j];
            }
        }
    }

    // Правая терраса
    for (int i = terrace_h + 1; i <= terrace_h + N - 2; i++) {
        for (int j = N_full - 1; j > N + terrace_h - 1; j--) {
            if (full[i][j] != 0) {
                full[i][j - N] = full[i][j];
            }
        }
    }

    // Верхняя терраса
    for (int i = 0; i < terrace_h; i++) {
        for (int j = terrace_h + 1; j < terrace_h + N - 1; j++) {
            if (full[i][j] != 0) {
                full[i + N][j] = full[i][j];
            }
        }
    }

    // Нижняя терраса
    for (int i = terrace_h + N; i <= N_full - 1; i++) {
        for (int j = terrace_h + 1; j < terrace_h + N - 1; j++) {
            if (full[i][j] != 0) {
                full[i - N][j] = full[i][j];
            }
        }
    }


    // Выделение из магического квадрата из квадрата 'full'
    m = 0, n = 0; // Координаты элемента в 'magic'
    for (int i = terrace_h; i < N_full - terrace_h; i++) {
        for (int j = terrace_h; j < N_full - terrace_h; j++) {
            magic[m][n++] = full[i][j];
        }
        m++; n = 0;
    }

    for (int i = 0; i < N_full; i++) {
        free(full[i]);
    } free(full);

    return magic;
}

int** even_even_magic(int** magic, int val) {
   
    // МЕТОД РАУЗ-БОЛЛА

    int N = val;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            magic[i][j] = (j + 1) + i * N;
        }
    }

    // 'back' - квадрат заполнен от N^2 до 1 по убыванию
    int** back = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        back[i] = (int*)malloc(N * sizeof(int));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            back[i][j] = N* N - (j + i * N);
        }
    }

   
    // Обход магического квадрата. Если элемент находится на одной из диагоналей
    // то присвоить ему значение соответствуюшего элемента в квадрате 'back'

    int n = 0, m = 0; // координаты текущего элемента
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            n = i;
            m = j;

            // Приведение координат элемента к координатам квадрата
            // 4x4 в левом верхнем углу
            while (n > 3)
                n -= 4;

            while (m > 3)
                m -= 4;

            // Проверка всех комбинаций координат элементов, принадлежащим
            // диагоналям в квадрате 4x4 в левом верхнем углу
            if (n == m || n + m == 3)
                magic[i][j] = back[i][j];

        }
    }


    for (int i = 0; i < N; i++) {
        free(back[i]);
    } free(back);

    return magic;
}

int** even_noeven_magic(int** magic, int val) {

    // http://www.klassikpoez.narod.ru/mojmetod.htm

    int N = val;

    int N_little = N / 2; // Размерность 4-ёх маленьких квадратов
    
    // Квадрат в левом верхнем углу
    int** little = (int**)malloc(N_little * sizeof(int*));
    for (int i = 0; i < N_little; i++) {
        little[i] = (int*)malloc(N_little * sizeof(int));
    }

    // Делаем его магическим
    little = odd_magic(little, N_little);

    // Помещаем его в левый верхний угол искомого квадрата
    for (int i = 0; i < N_little; i++) {
        for (int j = 0; j < N_little; j++) {
            magic[i][j] = little[i][j];
        }
    }

    // Далее по алгоритму составляем остальные 
    // три малеьких квадрата

    int add = N_little * N_little; // Добавка к элементам 3-ёх маленьких квадратов
    int m = 0, n = 0; // Координаты элементов в квадрате 'little'

    // Справа от 'little'
    for (int i = 0; i < N_little; i++) {
        for (int j = N_little; j < N; j++) {
            magic[i][j] = little[m][n++] + add * 2;
        }
        m++; n = 0;
    }

    // Снизу от 'little'
    m = 0, n = 0;
    for (int i = N_little; i < N; i++) {
        for (int j = 0; j < N_little; j++) {
            magic[i][j] = little[m][n++] + add * 3;
        }
        m++; n = 0;
    }

    // Право-низ от 'little'
    m = 0, n = 0;
    for (int i = N_little; i < N; i++) {
        for (int j = N_little; j < N; j++) {
            magic[i][j] = little[m][n++] + add * 1;
        }
        m++; n = 0;
    }

    for (int i = 0; i < N_little; i++) {
        free(little[i]);
    } free(little);

    // Меняем местами некоторые элементы,
    // как это показано в алгоритме
    change(&magic[0][0], &magic[N_little][0]);
    change(&magic[N_little - 1][0], &magic[N - 1][0]);

    for (int i = 1; i < N_little - 1; i++) {
        change(&magic[i][1], &magic[i + N_little][1]);
    }

    int x = (N - 2) / 4 - 1; // Сколько столбцов из середины поменять
    for (int i = 0; i < N_little; i++) {
        for (int j = N_little - x; j < N_little + x; j++) {
            change(&magic[i][j], &magic[i + N_little][j]);
        }
    }
   

    return magic;
}

void change(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}