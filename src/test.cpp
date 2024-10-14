//
// Created by 19912 on 2024/9/28.
//

#include "Normal.h"

//#include "Polynomial.h"

//#include "History.h"

int main() {

    // test Polynomial
    std::string exp = "999/3/3/5";

    Expression e(exp, 0);

    e.cal_exp();

    e.print_exp_ans();

    return 0;
}
