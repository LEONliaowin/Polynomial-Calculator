//
// Created by 19912 on 2024/9/26.
//

#include "Polynomial.h"
#include <iostream>
#include <cmath>
#include <regex>

Polynomial::Polynomial(int n, int *arr) {
    this->n = n;
    for (int i = 0; i < 2 * n; i += 2) {
        this->coe.push_back(arr[i]);
        this->exp.push_back(arr[i + 1]);
    }
}

Polynomial::Polynomial() {
    this->n = 0;
}

Polynomial::Polynomial(Polynomial &p) {
    this->n = p.n;
    this->coe = p.coe;
    this->exp = p.exp;
}

Polynomial::Polynomial(std::string poly) {
    // Define the regular expression for polynomial terms
    std::regex term_regex(R"(([+-]?\d*)x(?:\^(\d+))?|([+-]?\d+))");
    //                         match[1]^  match[2]^            ^match[3]
    // Match each term in the polynomial, create an iterator
    auto terms_begin = std::sregex_iterator(poly.begin(), poly.end(), term_regex);
    // Use an empty iterator as the end iterator
    auto terms_end = std::sregex_iterator();

    // Iterate through each term
    for (std::sregex_iterator i = terms_begin; i != terms_end; ++i) {
        // Dereference each iterator to get the match result
        std::smatch match = *i;
        if (match[3].matched) {
            // If the third match is present, it's a constant term
            int coefficient = std::stoi(match[3].str());
            exp.push_back(0);
            coe.push_back(coefficient);
            n++;
        } else {
            // Otherwise, it's a term with an exponent
            int coefficient = (match[1].str().empty() || match[1].str() == "+") ? 1 : (match[1].str() == "-" ? -1
                                                                                                             : std::stoi(
                            match[1].str()));
            int exponent = match[2].matched ? std::stoi(match[2].str()) : 1;
            exp.push_back(exponent);
            coe.push_back(coefficient);
            n++;
        }
    }
    // sort the polynomial
    for (int i = 0; i < this->n; ++i) {
        for (int j = i + 1; j < this->n; ++j) {
            if (this->exp[i] < this->exp[j]) {
                std::swap(this->exp[i], this->exp[j]);
                std::swap(this->coe[i], this->coe[j]);
            }
            if (this->exp[i] == this->exp[j]) {
                this->coe[i] += this->coe[j];
                this->coe[j] = 0;
            }
        }
    }
    for (int i = 0; i < this->n; ++i) {
        if (this->coe[i] == 0) {
            this->coe.erase(this->coe.begin() + i);
            this->exp.erase(this->exp.begin() + i);
            this->n--;
            i--;
        }
    }
}

Polynomial::~Polynomial() {
    this->coe.clear();
    this->exp.clear();
}

void Polynomial::print() const {
    if (n == 0) printf("0");
    bool empty = true;

    for (int i = 0; i < n; ++i) {
        if (coe[i] == 0) continue;
        if (i != 0) {
            if (coe[i] > 0) printf(" + ");
            else printf(" - ");
        }
        if (coe[i] != 1 || (coe[i] == 1 && exp[i] == 0)) printf("%d", abs(coe[i]));
        if (exp[i] != 0) printf("x");
        if (exp[i] != 0 && exp[i] != 1) printf("^%d", exp[i]);
    }

    printf("\n");
}

Polynomial Polynomial::operator+(const Polynomial &other) {
    int i = 0, j = 0;
    Polynomial res;

    while (i < this->n && j < other.n) {
        if (this->exp[i] > other.exp[j]) {
            res.coe.push_back(this->coe[i]);
            res.exp.push_back(this->exp[i]);
            i++;
            res.n++;
        } else if (this->exp[i] < other.exp[j]) {
            res.coe.push_back(other.coe[j]);
            res.exp.push_back(other.exp[j]);
            j++;
            res.n++;
        } else {
            res.coe.push_back(this->coe[i] + other.coe[j]);
            res.exp.push_back(this->exp[i]);
            i++;
            j++;
            res.n++;
        }
    }
    while (i < this->n) {
        res.coe.push_back(this->coe[i]);
        res.exp.push_back(this->exp[i]);
        i++;
        res.n++;
    }
    while (j < other.n) {
        res.coe.push_back(other.coe[j]);
        res.exp.push_back(other.exp[j]);
        j++;
        res.n++;
    }
    return res;
}

Polynomial &Polynomial::operator=(const Polynomial &other) {
    n = other.n;
    coe = other.coe;
    exp = other.exp;
    return *this;
}

void Polynomial::operator+=(const Polynomial &other) {
    int i = 0, j = 0;
    while (i < n && j < other.n) {
        if (exp[i] < other.exp[j]) {
            coe.insert(coe.begin() + i, other.coe[j]);
            exp.insert(exp.begin() + i, other.exp[j]);
            n++;
            j++;
            i++;
        } else if (exp[i] > other.exp[j]) {
            i++;
        } else {
            coe[i] += other.coe[j];
            if (coe[i] == 0) {
                coe.erase(coe.begin() + i);
                exp.erase(exp.begin() + i);
                n--;
            }
            j++;
        }
    }

    while (j < other.n) {
        exp.push_back(other.exp[j]);
        coe.push_back(other.coe[j]);
        j++;
        n++;
    }
}

Polynomial Polynomial::mul(int _coe, int _exp) const {
    Polynomial res;
    res.n = n;
    for (auto c: coe) res.coe.push_back(c * _coe);
    for (auto c: exp) res.exp.push_back(c + _exp);
    return res;
}

Polynomial Polynomial::operator*(const Polynomial &other) {
    Polynomial res;

    for (int i = 0; i < n; ++i) {
        int _coe = coe[i], _exp = exp[i];
        res += other.mul(_coe, _exp);
    }
    return res;
}

Polynomial Polynomial::operator-(const Polynomial &other) {
    int i = 0, j = 0;
    Polynomial res;

    while (i < n && j < other.n) {
        if (exp[i] > other.exp[j]) {
            res.exp.push_back(exp[i]);
            res.coe.push_back(coe[i]);
            res.n++;
            i++;
        } else if (exp[i] < other.exp[j]) {
            res.exp.push_back(other.exp[j]);
            res.coe.push_back(-other.coe[j]);
            res.n++;
            j++;
        } else {
            if (coe[i] != other.coe[j]) {
                res.coe.push_back(coe[i] - other.coe[j]);
                res.exp.push_back(exp[i]);
                res.n++;
                j++;
                i++;
            } else {
                i++;
                j++;
            }
        }
    }
    while (i < this->n) {
        res.coe.push_back(this->coe[i]);
        res.exp.push_back(this->exp[i]);
        i++;
        res.n++;
    }
    while (j < other.n) {
        res.coe.push_back(other.coe[j]);
        res.exp.push_back(other.exp[j]);
        j++;
        res.n++;
    }
    return res;
}

Polynomial Polynomial::operator-=(const Polynomial &other) {
    int i = 0, j = 0;
    while (i < n && j < other.n) {
        if (exp[i] > other.exp[j]) {
            i++;
        } else if (exp[i] < other.exp[j]) {
            coe.insert(coe.begin() + i, -other.coe[j]);
            exp.insert(exp.begin() + i, other.exp[j]);
            n++;
            j++;
            i++;
        } else {
            coe[i] -= other.coe[j];
            if (coe[i] == 0) {
                coe.erase(coe.begin() + i);
                exp.erase(exp.begin() + i);
                n--;
            } else {
                i++;
            }
            j++;
        }
    }

    while (j < other.n) {
        exp.push_back(other.exp[j]);
        coe.push_back(-other.coe[j]);
        j++;
        n++;
    }
    return *this;
}

double Polynomial::operator[](double x) const {
    double acc = 0;
    for (int i = 0; i < n; ++i) {
        acc += coe[i] * pow(x, exp[i]);
    }
    return acc;
}

Polynomial CalFromString(const std::string str) {
    //    std::stack<Polynomial> polys;
    Polynomial ans;

    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '\'') {
            ans = ans.derivative();
            continue;
        }
        if (str[i] == '(') {
            int j = i + 1;
            std::string poly_str;
            while (str[j] != ')') {
                if (str[j] != ' ') {
                    poly_str += str[j];
                }
                j++;
            }
            Polynomial poly = Polynomial(poly_str);
            if (i == 0) {
                ans = poly;
            } else if (str[i - 1] == '+') {
                ans += poly;
            } else if (str[i - 1] == '-') {
                ans -= poly;
            } else if (str[i - 1] == '*') {
                ans = ans * poly;
            }
            i = j;
        }
    }

    return ans;
}

Polynomial Polynomial::derivative() const {
    if (n == 0) return Polynomial();
    Polynomial res;
    for (int i = 0; i < n; ++i) {
        if (exp[i] == 0) continue;
        res.coe.push_back(coe[i] * exp[i]);
        res.exp.push_back(exp[i] - 1);
        res.n++;
    }
    return res;
}

std::string Polynomial::GetStringOfPoly() const {
    std::string res;
    if (n == 0) {
        res = "0";
        return res;
    }
    bool empty = true;

    for (int i = 0; i < n; ++i) {
        if (coe[i] == 0) continue;
        if (i != 0 && coe[i] > 0) res += "+";
        if (coe[i] != 1 || (coe[i] == 1 && exp[i] == 0)) res += std::to_string(coe[i]);
        if (exp[i] != 0) res += "x";
        if (exp[i] != 0 && exp[i] != 1) res += "^" + std::to_string(exp[i]);
    }
    if (res.empty()) res = "0";

    return res;
}
