//
// Created by 19912 on 2024/10/4.
//

#include "StartupDialog.h"

StartupDialog::StartupDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Startup Dialog");
    this->setFixedSize(740, 600);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QTextEdit *aboutTextEdit = new QTextEdit(this);
    aboutTextEdit->setReadOnly(true);
    layout->addWidget(aboutTextEdit);

    QFile file("./about.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        aboutTextEdit->setText(in.readAll());
        file.close();
    } else {
        aboutTextEdit->setText("Failed to open the about.txt file.");
    }

    QCheckBox *dontShowAgainCheckBox = new QCheckBox("Don't show this again", this);
    layout->addWidget(dontShowAgainCheckBox);

    QPushButton *continueButton = new QPushButton("Continue", this);
    layout->addWidget(continueButton);

    connect(continueButton, &QPushButton::clicked, this, &StartupDialog::accept);
    connect(dontShowAgainCheckBox, &QCheckBox::toggled, this, &StartupDialog::setDontShowAgain);
}

bool StartupDialog::dontShowAgain() const {
    return m_dontShowAgain;
}

void StartupDialog::setDontShowAgain() {
    m_dontShowAgain = true;
}
