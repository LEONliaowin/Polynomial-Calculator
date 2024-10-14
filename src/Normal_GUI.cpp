//
// Created by 19912 on 2024/9/29.
//

#include "Normal_GUI.h"
#include "Normal.h"
#include <string>

Normal_Calculator::Normal_Calculator(QWidget *parent) : QWidget(parent) {
    // 创建布局管理器
    QVBoxLayout *layout = new QVBoxLayout(this);
    // 创建显示框
    display = new QLineEdit(this);
    // 设置显示框只读
    display->setReadOnly(true);
    // 设置显示框右对齐
    display->setAlignment(Qt::AlignRight);
    display->setFont(QFont("Consolas", 24));
    layout->addWidget(display);

    // 创建按钮布局
    QGridLayout *gridLayout = new QGridLayout();
    // 创建按钮
    QStringList buttons = {"7", "8", "9", "+", "4", "5", "6", "-", "1", "2", "3", "*", "^", "0", "=", "/", "(", ")",
                           "%", "C", "<="};

    // 将按钮添加到布局中
    int pos = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (pos < buttons.size()) {
                QPushButton *button = new QPushButton(buttons[pos], this);
                button->setMinimumHeight(50);
                gridLayout->addWidget(button, i, j);
                connect(button, &QPushButton::clicked, this, &Normal_Calculator::buttonClicked);
                pos++;
            }
        }
    }
    // 将按钮布局添加到主布局
    layout->addLayout(gridLayout);
    // 设置主布局
    setLayout(layout);

    // 设置快捷键
    QShortcut *undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    connect(undoShortcut, &QShortcut::activated, this, &Normal_Calculator::undo);

    QShortcut *redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    connect(redoShortcut, &QShortcut::activated, this, &Normal_Calculator::redo);
}

void Normal_Calculator::buttonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;

    QString buttonText = button->text();
    handleEvent(buttonText);
}

void Normal_Calculator::keyPressEvent(QKeyEvent *event) {
    QString keyText = event->text();
    if (keyText == "\b") {
        keyText = "<=";
    }
    if (keyText == "\r") {
        keyText = "=";
    }
    handleEvent(keyText);
}

void Normal_Calculator::handleEvent(QString buttonText) {
    if (exceptionStatus) {
        display->clear();
        exceptionStatus = false;
    }
    if (buttonText == "=") {
        inputString = display->text();
        std::string exp = inputString.toStdString();
        history.add(inputString);
        Expression e(exp, 0);
        try {
            e.cal_exp();
        } catch (const char* msg) {
            display->setText(msg);
            exceptionStatus = true;
            return;
        } catch (...) {
            display->setText("error");
            exceptionStatus = true;
            return;
        }
        QString ans = QString::number(e.getAns());
        history.add(ans);
        display->setText(ans);
    } else if (buttonText == 'C' || buttonText == 'c') {
        display->clear();
    } else if (buttonText == "<=") {
        QString text = display->text();
        if (text.size() > 0) {
            text.chop(1);
            display->setText(text);
        }
    } else {
        display->setText(display->text() + buttonText);
    }
}

void Normal_Calculator::undo() {
    if (history.isOldest()) return;
    QString Qexp = history.undo();
    display->setText(Qexp);
}

void Normal_Calculator::redo() {
    if (history.isNewest()) return;
    QString Qexp = history.redo();
    display->setText(Qexp);
}
