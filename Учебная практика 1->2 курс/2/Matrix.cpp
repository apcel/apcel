#pragma once
#include "Matrix.h" // Объявление структуры класса

/////////////////////////////////////////////////////
/////////////////////операторы///////////////////////

template<typename __Type>
std::ostream & MyMatrix<__Type>::operator << (std::ostream &output)
{
	for(int i = 0; i <= sizeN; ++i) {
		for (int j = i; j <= sizeM; ++j)
			std::cout << temp[i][j];
		std::cout<<std::endl;
	}
}
template<typename __Type>
std::istream & MyMatrix<__Type>::operator >> (std::istream &output)
{
	int j;
	int i;
	for(i = 0; temp[i][j] != EOF; ++i) {
		{
			std::cin >> temp[i][j];
		} for (j = i; temp[i][j] != "\n"; ++j)
		sizeM == j - 1;
	}
	sizeN == i - 1;
}
template<typename __Type>
MyMatrix<__Type> & MyMatrix<__Type>::operator + (const MyMatrix<__Type> &m)
{

}



template<typename __Type>
void MyMatrix<__Type>::transpone()
{
	this->sizeN = sizeCol;
	this->sizeM = sizeRow;
	for (int i = 0; i <= sizeN; ++i)
		for (int j = i; j <= sizeM; ++j)
			std::swap(temp[i][j], temp[j][i]);
			//true;
}

///////////////////сортировка///////////////////////////////

/////////////////////Поиск////////////////////////////////
template<typename __Type>
int MyMatrix<__Type>::sizeRow()
{
	return temp.size();

}
template<typename __Type>
int MyMatrix<__Type>::sizeCol()
{
	return temp[0].size();

}