#ifndef POLYNOMIAL_CALCULATOR_H
#define POLYNOMIAL_CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QShortcut>

#include "History.h"
#include "Polynomial.h"


class Polynomial_calculator : public QWidget {
Q_OBJECT

public:
    explicit Polynomial_calculator(QWidget *parent = nullptr);

private slots:

    void buttonClicked();

    void handleEvent(QString buttonText);

    void keyPressEvent(QKeyEvent *event) override;

    void undo();

    void redo();

private:
    QLineEdit *display;

    History history;

    bool haveRes = false;

    bool XMode = false;

    bool ErrorMode = false;

    Polynomial XModePoly;
};

#endif // POLYNOMIAL_CALCULATOR_H