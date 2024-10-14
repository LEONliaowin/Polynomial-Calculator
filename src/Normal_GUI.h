//
// Created by 19912 on 2024/9/29.
//

#ifndef CALCULATOR_GUI_NORMAL_GUI_H
#define CALCULATOR_GUI_NORMAL_GUI_H


#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QShortcut>

#include "History.h"

class Normal_Calculator : public QWidget {
public:
    // 构造函数
    explicit Normal_Calculator(QWidget *parent = nullptr);
// 信号槽
private slots:

    // 按钮点击事件
    void buttonClicked();

    void handleEvent(QString buttonText);

    void keyPressEvent(QKeyEvent *event) override;

    void undo();

    void redo();

private:
    QLineEdit *display;

    QString inputString;

    History history;

    bool exceptionStatus = false;
};

//#include "Normal_Calculator.moc"


#endif //CALCULATOR_GUI_NORMAL_GUI_H
