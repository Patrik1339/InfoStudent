#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "UserWindow.h"
#include "../Service/Service.h"
#include <QTableView>
#include "Model.h"


class StudentWindow final: public UserWindow {
private:
    QVBoxLayout* lyMain;
    QHBoxLayout* lySus;
    QTableView* tabelNote;
    Model* model;
    QPushButton* btnLogout;
    QLabel* nume;
    QLabel* lblNote;

    void initializareGUI();
    void conectareSemnale();

public:
    StudentWindow(QWidget* mainWindow, Service& service, Student* student);
};
