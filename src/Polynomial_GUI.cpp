#include "Polynomial_GUI.h"

Polynomial_calculator::Polynomial_calculator(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFont(QFont("Consolas", 24));
    layout->addWidget(display);

    QGridLayout *gridLayout = new QGridLayout();
    QStringList buttons = {"7", "8", "9", "+", "4", "5", "6", "-", "1", "2", "3", "*", "C", "0", "X", "^", "<=", "(",
                           ")", "'", "=", "|x=", "()"};

    for (int i = 0; i < buttons.size(); ++i) {
        int row = i / 4;
        int col = i % 4;
        QPushButton *button = new QPushButton(buttons[i], this);
        button->setMinimumHeight(50);
        gridLayout->addWidget(button, row, col);
        connect(button, &QPushButton::clicked, this, &Polynomial_calculator::buttonClicked);
    }

    layout->addLayout(gridLayout);
    setLayout(layout);

    QShortcut *undo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    connect(undo, &QShortcut::activated, this, &Polynomial_calculator::undo);

    QShortcut *redo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    connect(redo, &QShortcut::activated, this, &Polynomial_calculator::redo);
}

void Polynomial_calculator::buttonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    bool haveRes = false;
    if (!button) return;

    QString buttonText = button->text();
    handleEvent(buttonText);
}

void Polynomial_calculator::keyPressEvent(QKeyEvent *event) {
    QString keyText;
    // Handle the backspace key
    switch (event->key()) {

        case Qt::Key_Backspace:
            keyText = "<=";
            break;
        case Qt::Key_Return:
        case Qt::Key_Enter:
            keyText = "=";
            break;
        case Qt::Key_X:
            keyText = "x";
            break;
        case Qt::Key_Bar:
            keyText = "|x=";
            break;
        default:
            keyText = event->text();
    }

    handleEvent(keyText);
}

void Polynomial_calculator::handleEvent(QString buttonText) {
    if (buttonText == "=") {
        // Handle the "=" button click
        if (XMode) {
            try {
                XMode = false;
                QString Qexp = display->text();
                history.add(Qexp);
                std::string exp = Qexp.toStdString();
                exp = exp.substr(exp.rfind("|") + 3);
                double x = stod(exp);
                x = XModePoly[x];
                if ((int) x == x) {
                    QString Qexp = std::to_string((int) x).c_str();
                    display->setText(Qexp);
                    history.add(Qexp);
                    return;
                } else {
                    Qexp = std::to_string(x).c_str();
                    display->setText(Qexp);
                    history.add(Qexp);
                    return;
                }
            } catch (...) {
                display->setText("input missing");
                ErrorMode = true;
                return;
            }
        }
        QString Qexp = display->text();
        history.add(Qexp);
        std::string exp = Qexp.toStdString();
        if (exp[0] != '(' || (exp[exp.size() - 1] != ')' && exp[exp.size() - 1] != '\'')) {
            Polynomial p = Polynomial(exp);
            std::string p_cstr = p.GetStringOfPoly();
            display->setText(p_cstr.c_str());
            history.add(p_cstr.c_str());
            haveRes = true;
        } else {
            Polynomial p = CalFromString(exp);
            std::string p_cstr = p.GetStringOfPoly();
            display->setText(p_cstr.c_str());
            history.add(p_cstr.c_str());
            haveRes = true;
        }
    } else if (buttonText == "C" || buttonText == "c") {
        display->clear();
    } else if (buttonText == "<=") {
        QString text = display->text();
        if (text.size() > 0) {
            text.chop(1);
            display->setText(text);
        }
    } else if (buttonText == "|x=") {
        QString Qexp = display->text();
        if (Qexp.size() == 0) return;
        if (Qexp[0] != '(' || Qexp[Qexp.size() - 1] != ')') {
            Qexp = "(" + Qexp + ")";
        }
        display->setText(Qexp);
        history.add(Qexp);
        std::string exp = Qexp.toStdString();
        XModePoly = CalFromString(exp);
        display->setText(display->text() + "|x=");
        this->XMode = true;
    } else if (buttonText == "()") {
        // 左边加左括号，右边加右括号
        if (haveRes) haveRes = false;
        QString Qexp = display->text();
        Qexp = "(" + Qexp + ")";
        display->setText(Qexp);
    } else if (buttonText == '\'') {
        // 左边加左括号，右边加右括号
        if (haveRes) haveRes = false;
        QString Qexp = display->text();
        Qexp = "(" + Qexp + ")'";
        display->setText(Qexp);
    } else {
        if (ErrorMode) {
            display->clear();
            haveRes = false;
            ErrorMode = false;
        }
        display->setText(display->text() + buttonText);
    }
}

void Polynomial_calculator::undo() {
    if (history.isOldest()) return;
    QString Qexp = history.undo();
    display->setText(Qexp);
}

void Polynomial_calculator::redo() {
    if (history.isNewest()) return;
    QString Qexp = history.redo();
    display->setText(Qexp);
}
