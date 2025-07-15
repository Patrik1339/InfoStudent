#pragma once
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "UserWindow.h"
#include <QComboBox>
#include <QFormLayout>
#include <QTableView>

#include "ModelTabelMaterii.h"


class ProfesorWindow final: public UserWindow {
private:
    QVBoxLayout* lyMain;
    QHBoxLayout* lySus;
    QPushButton* btnLogout;
    QLabel* nume;
    QVBoxLayout* lyMaterii;
    QLabel* labelMaterii;
    QComboBox* comboMaterii;
    QTableView* tabelaNoteMaterie;
    QHBoxLayout* lyJos;
    QFormLayout* lyFormular;
    QLineEdit* campNumeStudent;
    QLineEdit* campNota;
    QPushButton* btnModificareNota;
    ModelTabelMaterii* model;

    void initializareGUI();
    void conectareSemnale();
    void reincarcareTabel() const;

public:
    ProfesorWindow(QWidget* mainWindow, Service& service, Profesor* student);
};
