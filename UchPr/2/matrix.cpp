#pragma once
#include "matrix.h"


template<typename _Type>
void Matrix<_Type>::loadFromFile(std::string file) //загрузка матрицы из файла
{
    _value.clear();
    std::ifstream s(file);
    std::string in;
    int len = 1;
    getline(s, in);
    bool flag = false;
    for  (char c : in) {
        if (c == ' ' && (c + 1) != ' ' && (c + 1) != 0) {
            len++;
            flag = true;
        } else {
            flag = false;
        }
    }
    if(flag)
        len--;

    s.seekg(0);
    MatrixLine line;
    while (!s.eof()) {
        line.clear();
        for (int i = 0; i < len; i++) {


            _Type * h = new _Type;
            s >> *h;
            if(s.eof() && (i < (len - 1)))
                break;
            // std::cout << h;
            line.push_back(*h);
            delete h;
        }
        _value.push_back(line);
    }
    s.close();
}

template<typename _Type>
void Matrix<_Type>::saveToFile(std::string file) //запись матрицы в файл
{
    std::ofstream s(file);
    for  (auto line : _value) {
        for (int i = 0; i < getColCount(); i++) {
            s << line[i];
            if (i != getColCount() - 1)
                s << ' ';
        }
        s << std::endl;
    }
    s.close();
}
template<typename _Type>
void Matrix<_Type>::readFromKeyboard() //загрузка матрицы из файла
{
    int x, y;
    std::cout << "Введите размер м-ци:  (2 числа через пробел)\n";
    std::cin >> x >> y;
    if ((x == 0) || (y == 0))
        return;
    _value.clear();
    std::string in;
    MatrixLine line;
    for (int i = 0; i < x; i++) {
        std::cout << "Введите " << i + 1 << "строку (" << y << " чисел через пробел):\n";
        line.clear();
        for (int j = 0; j < y; j++) {
            _Type h;
            std::cin >> h;
            line.push_back(h);
        }
        _value.push_back(line);
    }
}




template<typename _Type>
void Matrix<_Type>::clear(int rows, int cols, _Type def) //очистка памяти матрицы
{
    _value.clear();
    for (auto i = 0; i < rows; i++) {
        auto line = MatrixLine(cols);
        std::fill(line.begin(), line.end(), def);
        _value.push_back(line);
    }
}

/***************************************************************************/



template<typename _Type>
Matrix<_Type> Matrix<_Type>::operator+(const Matrix &that) // оператор сложения матриц
{
    if  (getRowCount() != that.getRowCount() ||
        getColCount() != that.getColCount()) {
        return *this;
    }

    Matrix result(getRowCount(), getColCount(), 0);
    for (int i = 0; i < getRowCount(); i++) {
        for (int j = 0; j < getColCount(); j++) {
            result.put(i, j, get(i, j) + that.get(i, j));
        }
    }
    return result;
}

template<typename _Type>
Matrix<_Type> Matrix<_Type>::operator-(const Matrix &that) //оператор вычитания матриц
{
    if (getRowCount() != that.getRowCount() ||
        getColCount() != that.getColCount()) {
        return *this;
    }

    Matrix result(getRowCount(), getColCount(), 0);
    for (int i = 0; i < getRowCount(); i++) {
        for (int j = 0; j < getColCount(); j++) {
            result.put(i, j, get(i, j) - that.get(i, j));
        }
    }
    return result;
}


template<typename _Type>
Matrix<_Type> Matrix<_Type>::operator*(_Type number) // оператор умножения матрицы на число
{
    Matrix  result(getRowCount(), getColCount(), 0);

    for (int i = 0; i < getRowCount(); i++) {
        for (int j = 0; j < getColCount(); j++) {
            result.put(i, j, get(i, j) * number);
        }
    }
    return result;
}

template<typename _Type>
Matrix<_Type> Matrix<_Type>::operator*(const Matrix &that) //оператор перемножения матриц
{
    if (getColCount() != that.getRowCount()) {
        std::cout << "Matrix size error!\n";
        return *this;
    }
    Matrix result(getRowCount(), that.getColCount(), 0);
    for (int i = 0; i < getRowCount(); i++) {
        int value = 0;
        for (int j = 0; j < that.getColCount(); j++) {
            for (int k = 0; k < getColCount(); k++) {
                value += get(i, k) * that.get(k, j);
                result.put(i, j, value);
            }
            value = 0;
        }
    }
    return result;
}
template<typename _Type>
void Matrix<_Type>::operator=(const Matrix &that) //оператор присваивания
{
    _value.clear();
    for(auto line : that._value) {
        _value.push_back(line);
    }
    return;
}
/////////////////////////////////////////////////////////////////
template<typename _Type>
int Matrix<_Type>::getRowCount() const // получить количество строк
{
    return _value.size();
}

template<typename _Type>
int Matrix<_Type>::getColCount() const //получить количество столбцов
{
    if (_value.empty())
        return 0;
    return _value[0].size();
}

template<typename _Type>
Matrix<_Type> Matrix<_Type>::transponse() //транспонирование матрицы
{
    Matrix mtx = Matrix(getColCount(), getRowCount(), 0);
    for (int i = 0; i < getRowCount(); i++) {
        for (int j = 0; j < getColCount(); j++) {
            mtx.put(j, i, get(i, j));
        }
    }
    return mtx;
}



template<typename _Type>
_Type Matrix<_Type>::get(int row, int col) const // получить значение элемента матрицы
{
    if ((unsigned int)row >= _value.size())
        return 0;
    auto line = _value[row];
    if ((unsigned int)col >= line.size())
        return 0;
    return line[col];
}

template<typename _Type>
void Matrix<_Type>::put(int row, int col, _Type value) // присвоить значение элементу матрицы
{
    if (row < _value.size()) {
        auto line = _value[row];
        if (col < line.size())
            _value[row][col] = value;
    }
}

template<typename _Type>
void Matrix<_Type>::oneM(int sizeS) {
    _value.clear();
    Matrix<_Type> temp(sizeS, sizeS, 0);
    *this = temp;
    for (int i = 0; i < sizeS; ++i)
    {
        put(i, i, 1);
    }
}


template<typename _Type>
int Matrix<_Type>::individualFind()
{
    std::cout << '\n' << getRowCount() << " x "<< getColCount() << '\n';
    int max = 0;
    for (int i = 0; i < getRowCount(); ++i) {
        for (int j = 0; j < getColCount(); ++j) {
            for (int k = 1; isCorrect(i, j, k - 1) == true; ++k)
                if (max < k)
                    max = k;
        }
    }
    return max;
}


template<typename _Type>
bool Matrix<_Type>::isCorrect(int rowFirst, int colFirst, int sizeS)
{
    if (((rowFirst + sizeS) > getRowCount()) || ((colFirst + sizeS) > getColCount())) {
        return false;
    }

    for (int i = 0; i <= sizeS; ++i)
        if ((get(rowFirst + sizeS, colFirst + i) != 0) || (get(rowFirst + i, colFirst + sizeS) != 0)) {
            return false;
        }
    return true;
}



template<typename _Type>
std::ostream &operator<<(std::ostream &output, const Matrix<_Type> &m) // оператор вывода матрицы
{
    if (m.getRowCount()) {
        for  (auto line : m._value) {
            // std::cout << "for\n" << m._value;
            for  (auto item : line)
                output << item << ' ';
            output << std::endl;
        }
    }
    return output;
}