#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "UserWindow.h"
#include "../Service/Service.h"
#include <QTableView>
#include "Model.h"
#include "../Observer/Observer.h"


class StudentWindow final: public UserWindow, public Observer {
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
    void updateObserver() override;

public:
    StudentWindow(QWidget* mainWindow, Service& service, Student* student);
};
