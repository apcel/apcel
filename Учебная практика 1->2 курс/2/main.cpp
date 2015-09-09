#include <iostream>
#include <string>
#include <ctime>
#include <cstring>
#include "matrix.h"
using namespace std;


int //главная ф-ция (меню)
main(int argc, char **argv)
{
	setlocale(0, "Russian");
	char key;
	cout << "Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №14):\n'q' для выхода\n";
	cin >> key;
	while (key != 'q')
	{
		switch (key)
		{
		case '1':
			cout << "\nВаша матрица: \n" << Matrix<int>::ReadKeyboard() << endl;
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
			__test_minCol();
			break;
		}
		system("pause");
		system("cls");
		cout << "Меню:\n1)ввод матрицы с клавиатуры\n2)сложение матриц\n3)вычитание матриц\n4)умножение матриц\n5)транспонирование матрицы\n6)Индивидуальное задание(вариант №14):\n'q' для выхода\n";
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
	system("pause");
	return EXIT_SUCCESS;
}