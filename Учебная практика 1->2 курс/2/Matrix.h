#pragma once

#include <iostream>
#include <vector>
//#include <algorithm>
#define apcel_RAND_MIN -1000
#define apcel_RAND_MAX 1000


template<typename __Type>
class MyMatrix: public std::vector<__Type> {
  private:
    std::vector<__Type> temp;
    int sizeM, sizeN;
    __Type container[2][2];
  public:
    std::ostream & operator << (std::ostream &output);
    std::istream & operator >> (std::istream &output);
    MyMatrix<__Type> &operator +  (const MyMatrix<__Type> &m);
    __Type & operator () (const unsigned long el);
    __Type & operator () (const unsigned long m, const unsigned long n);
    void transpone();
    MyMatrix()
    {
    	sizeN = 0;
    	sizeM = 0;
    	fprintf(stderr, "%s\n", "Сработал конструктор");
    }
};

// template<typename __Type>
//std::ostream &operator << (std::ostream &output, const MyMatrix<__Type> &v);//вывод вектора