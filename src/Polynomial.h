//
// Created by 19912 on 2024/9/26.
//

#ifndef CALCULATOR_POLYNOMIAL_H
#define CALCULATOR_POLYNOMIAL_H

#include <vector>
#include <string>
#include <stack>

//using namespace std;

class Polynomial {
public:
    int n{};
    std::vector<int> coe;
    std::vector<int> exp;

    // constructor
    Polynomial();

    Polynomial(int n, int *arr);

    Polynomial(std::string exp);

    Polynomial(Polynomial &p);

    // destructor
    ~Polynomial();

    // member function
    void print() const;

    // operator overloading
    Polynomial operator+(const Polynomial &other);

    void operator+=(const Polynomial &other);

    Polynomial operator-(const Polynomial &other);

    Polynomial operator-=(const Polynomial &other);

    Polynomial &operator=(const Polynomial &other);

    Polynomial operator*(const Polynomial &other);

    Polynomial mul(int coe, int exp) const;

    double operator[](double x) const;

    Polynomial derivative() const;

    std::string GetStringOfPoly() const;

};

Polynomial CalFromString(std::string str);


#endif //CALCULATOR_POLYNOMIAL_H
