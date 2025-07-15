#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>

#include "../Service/Service.h"


class MainWindow final: public QWidget {
private:
    Service service;
    QVBoxLayout* lyMain;
    QLabel* titlu;
    QWidget* containerFormular;
    QFormLayout* lyFormular;
    QHBoxLayout* lyOrizontal;
    QHBoxLayout* lyButon;
    QLineEdit* campEmail;
    QLineEdit* campParola;
    QPushButton* btnLogin;

    void initializareGUI();
    void conectareSemnale();

public:
    explicit MainWindow(const Service& service);
};
