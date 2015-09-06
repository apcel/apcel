#pragma once
#include "Matrix.h" // Объявление структуры класса

/////////////////////////////////////////////////////
/////////////////////операторы///////////////////////

template<typename __Type>
std::ostream & MyMatrix<__Type>::operator << (std::ostream &output)
{


}
template<typename __Type>
std::istream & MyMatrix<__Type>::operator >> (std::istream &output)
{

}
template<typename __Type>
MyMatrix<__Type> & MyMatrix<__Type>::operator + (const MyMatrix<__Type> &m)
{

}



template<typename __Type>
void MyMatrix<__Type>::transpone()
{
	for (int i = 0; i <= sizeN; ++i)
		for (int j = i; j <= sizeM; ++j)
		//	std::swap(container[i][j], container[j][i]);
			true;

}

///////////////////сортировка///////////////////////////////

/////////////////////Поиск////////////////////////////////
template<typename __Type>
int MyMatrix<__Type>::sizeRow()
{


}
template<typename __Type>
int MyMatrix<__Type>::sizeCol()
{
	return temp.size();

}