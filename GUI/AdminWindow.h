#pragma once
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QVBoxLayout>
#include <QWidget>
#include "ModelGeneral.h"
#include "../Observer/Observer.h"
#include "../Service/Service.h"


class AdminWindow final: public QWidget, public Observer {
private:
    Service& service;

    QVBoxLayout* lyMain;
    QHBoxLayout* lySecundar;
    QVBoxLayout* lyVertical;
    QComboBox* comboTabela;
    QTableView* tabela;
    ModelTabelGeneral* model;
    QFormLayout* lyFormular;
    QLineEdit* campId;
    QLineEdit* campNume;
    QLineEdit* campEmail;
    QLineEdit* campParola;
    QLineEdit* campNota;
    QLineEdit* campGrupa;
    QLineEdit* campDepartament;
    QLineEdit* campDenumireMaterie;
    QLabel* lblCampId;
    QLabel* lblCampNume;
    QLabel* lblCampEmail;
    QLabel* lblCampParola;
    QLabel* lblCampNota;
    QLabel* lblCampGrupa;
    QLabel* lblCampDepartament;
    QLabel* lblCampDenumireMaterie;
    QPushButton* btnAdauga;
    QPushButton* btnModifica;
    QPushButton* btnSterge;
    std::unordered_map<QWidget*, int> widgets;
    std::unordered_map<std::string, int> tipuri = {{"studenti", 0}, {"profesori", 1}, {"materii", 2}, {"note", 3}};

    void initializareGUI();
    void conectareSemnale();
    void reincarcareTabela() const;
    void createField(QLabel* label, QLineEdit* camp, int id);
    void updateObserver() override;

public:
    explicit AdminWindow(Service& service);
};