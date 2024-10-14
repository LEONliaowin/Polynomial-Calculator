//
// Created by 19912 on 2024/10/4.
//

#ifndef CALCULATOR_GUI_STARTUPDIALOG_H
#define CALCULATOR_GUI_STARTUPDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

class StartupDialog : public QDialog {
Q_OBJECT

public:
    StartupDialog(QWidget *parent = nullptr);

    bool dontShowAgain() const;

private slots:

    void setDontShowAgain();

private:
    bool m_dontShowAgain = false;
};


#endif //CALCULATOR_GUI_STARTUPDIALOG_H
