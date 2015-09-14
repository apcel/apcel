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
	std::cout << "Матрица A+B:" << std::endl << a + b << std::endl;
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
	//std::cout << "Transp.: " << std::endl << a.transponse() << std::endl;
}



void //перемножение матриц
__test_operatorUMN()
{
	Matrix<int> a(3, 3, 2);
	Matrix<int> b(2, 2, 3);
	std::cout << "Матрица A:" << std::endl << a;
	std::cout << "Матрица B:" << std::endl << b;
	std::cout << "Матрица A*B:" << std::endl << a*b << std::endl;
}


void //загрузка матрицы из файкла
__test_LoadByFile()
{
	Matrix <int> m(3, 3, 0);
	m.loadFromFile("matrix2.txt");
}

void //запись матрицы в файл
__test_SaveFile()
{
	Matrix <int> m(3, 3, 0);
	m.saveToFile("matrix2.txt");
}

void // В матрице, состоящей из нулей и единиц, найдите квадрат (квадратная подматрица) наибольшего размера, состоящая только из нулей.
__test_podmatrix()
{
	Matrix<int> m(6, 6, 1);
	for (int i = 1; i < m.getRowCount() - 1; i++)
	{
		for (int j = 1; j < m.getColCount() - 1; j++)
		{
			m.put(i, j, 0);
		}
	}
	m.put(3, 3, 1);
	cout << "Индивидуальное задание (вариант №13):" << endl << "Исходная матрица: " << endl;
	for (int i = 0; i < m.getRowCount(); i++)
	{
		for (int j = 0; j < m.getColCount(); j++)
		{
			cout << m.get(i, j) << " ";
		}
		cout << endl;
	}
	int col = 0, i, j, i1, j1, tmp, tmp1;
	for (i = 0; i < m.getRowCount(); i++) {
		for (j = 0; j < m.getColCount(); j++) {
			if (m.get(i, j) == 0) {
				tmp = 1;
				for (j1 = j; (j1 < m.getColCount()) && (m.get(i, j1) == 0); j1++) {
					tmp1 = 1;
					for (i1 = i; (i1 < m.getRowCount()) && (m.get(i1, j1) == 0); i1++)
						tmp1++;
					if (!tmp) {
						tmp = tmp1;
					} else {
						if (tmp > tmp1)
							tmp = tmp1;
					}
					if (col < tmp * (j1 - j + 1))
						col = tmp * (j1 - j + 1); //площадь
				}
			}
		}
	}
	cout << endl << "Подматрица. Размер подматрицы = " << col << endl;;
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
	cout << "Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n'q' для выхода\n";
	cin >> key;
	Matrix <int> m(3, 3, 0);
	while (key != 'q')
	{
		switch (key)
		{
		case '1':
			//cout << "\nВаша матрица: \n" << Matrix<int>::readFromKeyboard() << endl;

			m.loadFromFile("matrix2.txt");
			break;
		case '2':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_operatorPlus();
			break;
		case '3':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_operatorMinus();
			break;
		case '4':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_operatorUMN();
			break;
		case '5':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_transposition();
			break;
		case '6':
			cout << "\nВвод матрицы из файла..." << endl;
			cout << "Вывод матриц в файл..." << endl;
			__test_podmatrix();
			break;
		}
		system("pause");
		system("cls");
		cout << "Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №13):\n'q' для выхода\n";
		cin >> key;
	}

	//__test_isSymmetric();
	//__test_operatorPlus();
	//__test_operatorMinus();
	//__test_determinant();
	//__test_isMinor();
	//__test_operatorUMN();
	//__test_equality();
	//__test_transposition();
	//__test_minCol();
	//__test_LoadByFile();
	//__test_SaveFile();
	return EXIT_SUCCESS;
}