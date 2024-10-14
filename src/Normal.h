//
// Created by 19912 on 2024/9/28.
//

#ifndef CALCULATOR_GUI_NORMAL_H
#define CALCULATOR_GUI_NORMAL_H

#include <string>
#include <stack>
#include <cctype>


class Expression {
public:
    std::string exp;
    double ans = 0;

    // constructor
    Expression(std::string &_exp, int ans);

    Expression(const Expression &other);

    ~Expression() = default;

    // methods
    void print_exp() const;

    void print_exp_ans() const;

    void cal_exp();

    static bool op_cmp(char, char);

    static double cal_cell(double l, double r, char  op);

    double getAns() const;

    const std::string &getExp() const;

};


#endif //CALCULATOR_GUI_NORMAL_H
