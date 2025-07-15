#include "AdminWindow.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include "../Erori/RepositoryError.h"


void AdminWindow::initializareGUI() {
    lyMain = new QVBoxLayout;
    lySecundar = new QHBoxLayout;
    lyVertical = new QVBoxLayout;

    comboTabela = new QComboBox;
    comboTabela->addItem("studenti");
    comboTabela->addItem("profesori");
    comboTabela->addItem("materii");
    comboTabela->addItem("note");
    lyMain->addWidget(comboTabela);

    tabela = new QTableView;
    model = new ModelTabelGeneral("studenti", service.getAllStudenti(), service.getAllProfesori(), service.getAllMaterii(), service.getAllNote());
    tabela->setModel(model);
    tabela->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tabela->resizeColumnsToContents();
    lySecundar->addWidget(tabela);

    lyFormular = new QFormLayout;
    campIdStudent = new QLineEdit;
    lblCampIdStudent = new QLabel("Id student");
    campIdStudent->setPlaceholderText("Id student");
    lyFormular->addRow(lblCampIdStudent, campIdStudent);
    campuri.push_back(campIdStudent);
    labeluri.push_back(lblCampIdStudent);

    campIdProfesor = new QLineEdit;
    campIdProfesor->setPlaceholderText("Id profesor");
    lblCampIdProfesor = new QLabel("Id profesor");
    lyFormular->addRow(lblCampIdProfesor, campIdProfesor);
    campIdProfesor->hide();
    lblCampIdProfesor->hide();
    campuri.push_back(campIdProfesor);
    labeluri.push_back(lblCampIdProfesor);

    campIdMaterie = new QLineEdit;
    lblCampIdMaterie = new QLabel("Id materie");
    campIdMaterie->setPlaceholderText("Id materie");
    lyFormular->addRow(lblCampIdMaterie, campIdMaterie);
    campuri.push_back(campIdMaterie);
    labeluri.push_back(lblCampIdMaterie);

    campNume = new QLineEdit;
    lblCampNume = new QLabel("Nume");
    campNume->setPlaceholderText("Nume");
    lyFormular->addRow(lblCampNume, campNume);
    campuri.push_back(campNume);
    labeluri.push_back(lblCampNume);

    campEmail = new QLineEdit;
    lblCampEmail = new QLabel("Email");
    campEmail->setPlaceholderText("Email");
    lyFormular->addRow(lblCampEmail, campEmail);
    campuri.push_back(campEmail);
    labeluri.push_back(lblCampEmail);

    campParola = new QLineEdit;
    lblCampParola = new QLabel("Parola");
    campParola->setPlaceholderText("Parola");
    lyFormular->addRow(lblCampParola, campParola);
    campuri.push_back(campParola);
    labeluri.push_back(lblCampParola);

    campNota = new QLineEdit;
    lblCampNota = new QLabel("Nota");
    campNota->setPlaceholderText("Nota");
    lyFormular->addRow(lblCampNota, campNota);
    campuri.push_back(campNota);
    labeluri.push_back(lblCampNota);

    campGrupa = new QLineEdit;
    lblCampGrupa = new QLabel("Grupa");
    campGrupa->setPlaceholderText("Grupa");
    lyFormular->addRow(lblCampGrupa, campGrupa);
    campuri.push_back(campGrupa);
    labeluri.push_back(lblCampGrupa);

    campDepartament = new QLineEdit;
    lblCampDepartament = new QLabel("Departament");
    campDepartament->setPlaceholderText("Departament");
    lyFormular->addRow(lblCampDepartament, campDepartament);
    campuri.push_back(campDepartament);
    labeluri.push_back(lblCampDepartament);

    campDenumireMaterie = new QLineEdit;
    lblCampDenumireMaterie = new QLabel("Denumire materie");
    campDenumireMaterie->setPlaceholderText("Denumire materie");
    lyFormular->addRow(lblCampDenumireMaterie, campDenumireMaterie);
    campuri.push_back(campDenumireMaterie);
    labeluri.push_back(lblCampDenumireMaterie);

    ascundeCampuri();
    campIdStudent->show();
    lblCampIdStudent->show();
    campNume->show();
    lblCampNume->show();
    campEmail->show();
    lblCampEmail->show();
    campParola->show();
    lblCampParola->show();
    campGrupa->show();
    lblCampGrupa->show();

    lyVertical->addLayout(lyFormular);

    btnModifica = new QPushButton("Modifica");
    lyVertical->addWidget(btnModifica);

    lySecundar->addLayout(lyVertical);
    lyMain->addLayout(lySecundar);

    this->setLayout(lyMain);
    this->setStyleSheet("background-color: #A2B2C3; color: black;");
    this->resize(800, 300);
}

void AdminWindow::conectareSemnale() {
    connect(comboTabela, &QComboBox::currentTextChanged, [this](const QString& text) {
        model->setTip(text.toStdString());
        ascundeCampuri();
        std::unordered_map<std::string, int> tipuri = {{"studenti", 0}, {"profesori", 1}, {"materii", 2}, {"note", 3}};
        switch(tipuri.at(text.toStdString())) {
            case 0: {
                campIdStudent->show();
                lblCampIdStudent->show();
                campNume->show();
                lblCampNume->show();
                campEmail->show();
                lblCampEmail->show();
                campParola->show();
                lblCampParola->show();
                campGrupa->show();
                lblCampGrupa->show();
                break;
            }
            case 1: {
                campIdProfesor->show();
                lblCampIdProfesor->show();
                campNume->show();
                lblCampNume->show();
                campEmail->show();
                lblCampEmail->show();
                campParola->show();
                lblCampParola->show();
                campDepartament->show();
                lblCampDepartament->show();
                break;
            }
            case 2: {
                campIdMaterie->show();
                lblCampIdMaterie->show();
                campDenumireMaterie->show();
                lblCampDenumireMaterie->show();
                campIdProfesor->show();
                lblCampIdProfesor->show();
                break;
            }
            case 3: {
                campNume->show();
                lblCampNume->show();
                campDenumireMaterie->show();
                lblCampDenumireMaterie->show();
                campNota->show();
                lblCampNota->show();
            }
            default: return;
        }
    });

    connect(btnModifica, &QPushButton::clicked, [this]() {
        const auto tip = comboTabela->currentText().toStdString();

        const int id = campIdStudent->text().toInt();
        const int id_materie = campIdMaterie->text().toInt();
        const std::string nume = campNume->text().toStdString();
        const std::string email = campEmail->text().toStdString();
        const std::string parola = campParola->text().toStdString();
        const int grupa = campGrupa->text().toInt();
        const std::string departament = campDepartament->text().toStdString();
        const std::string denumireMaterie = campDenumireMaterie->text().toStdString();
        const int nota = campNota->text().toInt();

        const std::unordered_map<std::string, int> tipuri = {
            {"studenti", 0}, {"profesori", 1}, {"materii", 2}, {"note", 3}
        };

        try {
            switch(tipuri.at(tip)) {
                case 0:
                    service.modificaStudent(id, nume, email, parola, grupa);
                    break;
                case 1:
                    service.modificaProfesor(id, nume, email, parola, departament);
                    break;
                case 2:
                    service.modificaMaterie(id_materie, denumireMaterie, id);  // id = id_profesor
                    break;
                case 3:
                    service.modificaNota(nume, denumireMaterie, nota);  // ⚠️ modifică în funcție de semnătură
                    break;
                default:
                    return;
            }
            reincarcareTabela();
        } catch(const RepositoryError& re) {
            QMessageBox::warning(this, "Eroare", re.what());
        } catch(const std::out_of_range&) {
            QMessageBox::warning(this, "Eroare", "Tip invalid de entitate.");
        }
    });
}

void AdminWindow::reincarcareTabela() const {
    model->setStudenti(service.getAllStudenti());
    model->setProfesori(service.getAllProfesori());
    model->setMaterii(service.getAllMaterii());
    model->setNote(service.getAllNote());
}

void AdminWindow::ascundeCampuri() const {
    for(const auto camp: campuri) {
        camp->hide();
    }
    for(const auto lbl: labeluri) {
        lbl->hide();
    }
}

AdminWindow::AdminWindow(Service &service) : service(service) {
    initializareGUI();
    conectareSemnale();
}
