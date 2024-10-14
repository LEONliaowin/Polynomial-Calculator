#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QTextEdit>
#include <QTextStream>
#include <QLabel>
#include <QString>

#include "Polynomial.h"
#include "Normal_GUI.h"
#include "Polynomial_GUI.h"
#include "StartupDialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QFile config("./config.txt");
    bool showStartupDialog = false;
    if (config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&config);
        showStartupDialog = in.readAll().toInt();
        config.close();
    }

    if (showStartupDialog) {
        StartupDialog startupDialog;
        startupDialog.exec();
        if (startupDialog.dontShowAgain()) {
            if (config.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&config);
                out << "0";
                config.close();
            }
        }
    }

    QStackedWidget stackedWidget;

    QWidget *menuWidget = new QWidget();
    menuWidget->setWindowTitle("Calculator GUI");
//    menuWidget->resize(720, 480);
    QWidget *polynomialWidget = new QWidget();
    polynomialWidget->setWindowTitle("Polynomial");
//    polynomialWidget->resize(720, 480);
    QWidget *normalwidget = new QWidget();
    normalwidget->setWindowTitle("Normal");
//    normalwidget->resize(720, 480);
    QWidget *aboutWidget = new QWidget();
    aboutWidget->setWindowTitle("About");
//    aboutWidget->resize(720, 480);

    // Create label for title
    QLabel *titleLabel = new QLabel("Calculator", menuWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(QFont("Consolas", 48));

    // Create buttons
    QPushButton *polynomialButton = new QPushButton("Polynomial", menuWidget);
    QPushButton *normalButton = new QPushButton("Normal", menuWidget);
    QPushButton *aboutButton = new QPushButton("About", menuWidget);

    QPushButton *return_poly = new QPushButton("Return", polynomialWidget);
    QPushButton *return_normal = new QPushButton("Return", normalwidget);
    QPushButton *return_about = new QPushButton("Return", aboutWidget);

    // Set minimum size for buttons
    polynomialButton->setMinimumHeight(150);
    normalButton->setMinimumHeight(150);
    aboutButton->setMinimumHeight(150);
    return_poly->setMinimumHeight(50);
    return_normal->setMinimumHeight(50);
    return_about->setMinimumHeight(50);

    // Use layout managers
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);
    menuLayout->setContentsMargins(50, 20, 50, 20); // Set margins
    menuLayout->addWidget(titleLabel);
    menuLayout->addWidget(polynomialButton);
    menuLayout->addWidget(normalButton);
    menuLayout->addWidget(aboutButton);
    menuWidget->setLayout(menuLayout);

    QVBoxLayout *aboutLayout = new QVBoxLayout(aboutWidget);

    QTextEdit *aboutTextEdit = new QTextEdit(aboutWidget);
    aboutTextEdit->setReadOnly(true);
    aboutLayout->addWidget(aboutTextEdit);

    QFile file("./about.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        aboutTextEdit->setText(in.readAll());
        file.close();
    } else {
        aboutTextEdit->setText("Failed to open the about.txt file.");
    }
    aboutLayout->addWidget(return_about);

    // Add normal_calculator to normal widget
    QVBoxLayout *normalLayout = new QVBoxLayout();
    Normal_Calculator *normal_calculator = new Normal_Calculator(normalwidget);
    normalLayout->addWidget(normal_calculator);
    normalLayout->addWidget(return_normal);
    normalwidget->setLayout(normalLayout);

    // Add polynomial_calculator to polynomial widget
    QVBoxLayout *polynomialLayout = new QVBoxLayout();
    Polynomial_calculator *polynomial_calculator = new Polynomial_calculator(polynomialWidget);
    polynomialLayout->addWidget(polynomial_calculator);
    polynomialLayout->addWidget(return_poly);
    polynomialWidget->setLayout(polynomialLayout);

    // Add widgets to stackedWidget
    stackedWidget.addWidget(menuWidget);
    stackedWidget.addWidget(polynomialWidget);
    stackedWidget.addWidget(normalwidget);
    stackedWidget.addWidget(aboutWidget);

    // Connect buttons to switch views
    QObject::connect(polynomialButton, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentWidget(polynomialWidget);
        polynomial_calculator->setFocus();
    });

    QObject::connect(return_poly, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentWidget(menuWidget);
    });

    QObject::connect(normalButton, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentWidget(normalwidget);
        normal_calculator->setFocus();
    });

    QObject::connect(return_normal, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentWidget(menuWidget);
    });

    QObject::connect(aboutButton, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentWidget(aboutWidget);
    });

    QObject::connect(return_about, &QPushButton::clicked, [&]() {
        stackedWidget.setCurrentWidget(menuWidget);
    });

    stackedWidget.show();

    return QApplication::exec();
}