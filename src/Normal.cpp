//
// Created by 19912 on 2024/9/28.
//

#include "Normal.h"
#include <cmath>

Expression::Expression(std::string &_exp, int ans) {
    this->exp = _exp;
    this->ans = ans;
}

void Expression::print_exp() const {
    printf("%s\n", exp.c_str());
}

Expression::Expression(const Expression &other) {
    this->exp = other.exp;
    this->ans = other.ans;
}

inline void process_cell(std::stack<double> &num, std::stack<char> &op) {
    char opr = op.top();
    double operand_r, operand_l;
    operand_r = num.top();
    num.pop();
    operand_l = num.top();
    num.pop();
    double res = Expression::cal_cell(operand_l, operand_r, opr);
    num.push(res);
    op.pop();
}

void Expression::cal_exp() {
    if (exp.empty()) throw "Empty expression!";
    // 科学计数法尚不支持
    if (exp.find('e') != std::string::npos) throw "Sci not supported yet!";
    // 检查括号匹配
    std::stack<char> check;
    for (int i = 0; i < exp.size(); ++i) {
        if (exp[i] == '(') check.push('(');
        if (exp[i] == ')') {
            if (check.empty()) throw "Mismatched ()!";
            check.pop();
        }
    }
    if (!check.empty()) throw "Mismatched ()!";

    std::stack<double> num;
    std::stack<char> op;

    for (int i = 0; i < exp.size(); ++i) {
        if (exp[i] == ' ') continue;
        if (isdigit(exp[i])) {
            double acc = 0;
            do {
                acc = acc * 10 + exp[i] - '0';
                i++;
            } while (isdigit(exp[i]));
            if (exp[i] == '.') {
                i++;
                double dec = 0.1;
                while (isdigit(exp[i])) {
                    acc += (exp[i] - '0') * dec;
                    dec /= 10;
                    i++;
                }
            }

            // 单目运算符
            if (exp[i] == '+' && exp[i + 1] == '+') {
                i++;
                num.push(acc + 1);
                continue;
            }
            if (exp[i] == '-' && exp[i + 1] == '-') {
                i++;
                num.push(acc - 1);
                continue;
            }

            num.push(acc);
            i--;
        } else {
            // 遇到（ 直接入栈
            if (exp[i] == '(') {
                op.push('(');
                continue;
            }
            // 遇到 ） 弹出直到遇到（
            if (exp[i] == ')') {
                while (op.top() != '(') {
                    process_cell(num, op);
                }
                op.pop();
                continue;
            }
            // 空栈直接入
            if (op.empty()) {
                op.push(exp[i]);
                continue;
            }
            // 一般情况
            while (!op.empty() && op_cmp(exp[i], op.top())) {
                process_cell(num, op);
            }
            op.push(exp[i]);
        }
    }
    // 计算剩余的运算符
    while (!op.empty()) {
        process_cell(num, op);
    }

    ans = num.top();
}

void Expression::print_exp_ans() const {
    // 如果是整数，输出整数，否则输出浮点数
    if (ans == (int) ans) printf("%s = %d\n", exp.c_str(), (int) ans);
    else printf("%s = %lf\n", exp.c_str(), ans);
}

bool Expression::op_cmp(char curr, char stack_op) {
    if (stack_op == '(') return false;
    if (curr == '+' || curr == '-') return true;
    if (curr == '*' || curr == '/' || curr == '%')
        return stack_op == '*' || stack_op == '/' || stack_op == '%' || stack_op == '^';
    if (curr == '^') return stack_op == '^';
    return false;
}

double Expression::cal_cell(double l, double r, char op) {
    // l->left operand, r->right operand, op->operator
    switch (op) {
        case '+':
            return l + r;
        case '-':
            return l - r;
        case '*':
            return l * r;
        case '/':
//            try {
//                if (r == 0) throw "Division by zero!";
//            } catch (const char *msg) {
//                printf("%s\n", msg);
//                exit(1);
//            }
            if (r == 0) {
                throw "Division by zero!";
            }
            return l / r;
        case '%':
            if (r == 0) {
                throw "Division by zero!";
            }
            return (int) l % (int) r;
        case '^':
            return pow(l, r);
        case '&':
            return (int) l & (int) r;
        case '|':
            return (int) l | (int) r;
        default:
            throw "Invalid operator!";
    }
}

double Expression::getAns() const {
    return ans;
}

const std::string &Expression::getExp() const {
    return exp;
}
