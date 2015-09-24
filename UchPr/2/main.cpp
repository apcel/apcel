#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include "matrix.cpp"
using namespace std;

void //сложение матриц
__test_operatorPlus()
{
    Matrix<int> a(3, 3, 2);
    Matrix<int> b(3, 3, 3);
    std::cout << "Матрица A:" << std::endl << a;
    std::cout << "Матрица B:" << std::endl << b;
    Matrix<int> c (0, 0, 0);
    c = a + b;
    std::cout << "Матрица A+B:" << std::endl << c << std::endl;
}

void // вычитание матриц
__test_operatorMinus()
{
    Matrix<int> a(3, 3, 2);
    Matrix<int> b(3, 3, 3);
    std::cout << "Матрица A:" << std::endl << a;
    std::cout << "Матрица B:" << std::endl << b;
    std::cout << "Матрица A-B:" << std::endl << a - b << std::endl;
}

void //транспонирование матрицы
__test_transposition()
{
    Matrix <int> a(8, 4, 1);
    a.put(5, 1, 2);
    a.put(2, 3, 1);
    a.put(2, 2, 2);
    std::cout << "Матрица: " << std::endl << a << std::endl;
    std::cout << "Transp.: " << std::endl << a.transponse() << std::endl;
}



void //перемножение матриц
__test_operatorUMN()
{
    Matrix<int> a(3, 4, 2);
    Matrix<int> b(4, 3, 3);
    Matrix<int> ed(0, 0, 0);
    ed.oneM(4);

    std::cout << "Матрица A:" << std::endl << a;
    std::cout << "Матрица B:" << std::endl << b;
    std::cout << "Матрица A*B:" << std::endl << a*b << std::endl;
    std::cout << "Матрица А*E" << std::endl << a*ed << std::endl;
}


void //загрузка матрицы из файка
__test_LoadByFile()
{
    Matrix <int> m(3, 3, 0);
    m.loadFromFile("matrix1.txt");
    std::cout << "Загружена матрица \n" << m << endl;
}

void //запись матрицы в файл
__test_SaveFile()
{
    Matrix<int> m(8, 8, 1);
    for (int i = 1; i < m.getRowCount() - 1; i++)
    {
        for (int j = 1; j < m.getColCount() - 1; j++)
        {
            m.put(i, j, 0);
        }
    }
    m.put(3, 2, 1);
    std::cout << "Матрица: \n" << m << endl;
    //m.saveToFile("matrix1.txt");
    ofstream f("matrix1.txt");
    f << m;
    std::cout << "Сохранено.\n";
}

void // В матрице, состоящей из нулей и единиц, найдите квадрат (квадратная подматрица) наибольшего размера, состоящая только из нулей.
__test_podmatrix()
{
    Matrix<int> m(8, 8, 1);
    for (int i = 1; i < m.getRowCount() - 1; i++)
    {
        for (int j = 1; j < m.getColCount() - 1; j++)
        {
            m.put(i, j, 0);
        }
    }
    m.put(3, 2, 1);
    cout << "Индивидуальное задание (вариант №13):" << endl << "Исходная матрица: " << endl;
    for (int i = 0; i < m.getRowCount(); i++)
    {
        for (int j = 0; j < m.getColCount(); j++)
        {
            cout << m.get(i, j) << " ";
        }
        cout << endl;
    }
    int col = 0;

    col = m.individualFind();
    cout << endl << "Подматрица. Размер подматрицы = " << col << " x " << col << endl;;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "0" << " ";
        }
        cout << endl;
    }
}

int //главная ф-ция (меню)
main(int argc, char **argv)
{
    setlocale(0, "Russian");
    char key;
    //cout << "\tМеню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n'q' для выхода\n";
    // cout << "Here-1";
    //cin >> key;
    key = 0;
    // cout << "Here0\n";
    Matrix <int> m(3, 3, 0);
    while (key != 'q')
    {
        cout << "\n\n\tМеню:\n" <<
                "0) Вывод матрицы на экран\n" <<
                "1) Ввод матрицы с клавиатуры\n"
                "2) Сложение матриц\n" <<
                "3) Вычитание матриц\n" <<
                "4) Умножение матриц\n" <<
                "5) Транспонирование матрицы\n" <<
                "6) Ввод матрицы из файла\n" <<
                "7) Вывод матрицы в файл\n" <<
                "a)Индивидуальное задание(вариант №13):\n" <<
                "'q' для выхода\n>> ";
        //key = 0;
        cin >> key;
        //cout << "While";
        cout << endl;
        switch (key)
        {
        case '0':
            cout << m;
            break;
        case '1':
            m.readFromKeyboard();
            break;
        case '2':
            __test_operatorPlus();
            break;
        case '3':
            __test_operatorMinus();
            break;
        case '4':
            __test_operatorUMN();
            break;
        case '5':
            __test_transposition();
            break;
        case '6':
            __test_LoadByFile();
            break;
        case '7':
            __test_SaveFile();
            break;
        case 'a':
            __test_podmatrix();
            break;
        }
    }
    return EXIT_SUCCESS;
}