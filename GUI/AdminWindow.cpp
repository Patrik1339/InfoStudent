#include "AdminWindow.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include <ranges>
#include "../Erori/RepositoryError.h"
#include "../Erori/ValidationError.h"


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
    campId = new QLineEdit;
    lblCampId = new QLabel("Id");
    createField(lblCampId, campId, -1);

    campNume = new QLineEdit;
    lblCampNume = new QLabel("Nume");
    createField(lblCampNume, campNume, 5);

    campEmail = new QLineEdit;
    lblCampEmail = new QLabel("Email");
    createField(lblCampEmail, campEmail, 4);

    campParola = new QLineEdit;
    lblCampParola = new QLabel("Parola");
    createField(lblCampParola, campParola, 4);

    campNota = new QLineEdit;
    lblCampNota = new QLabel("Nota");
    createField(lblCampNota, campNota, 3);

    campGrupa = new QLineEdit;
    lblCampGrupa = new QLabel("Grupa");
    createField(lblCampGrupa, campGrupa, 0);

    campDepartament = new QLineEdit;
    lblCampDepartament = new QLabel("Departament");
    createField(lblCampDepartament, campDepartament, 1);

    campDenumireMaterie = new QLineEdit;
    lblCampDenumireMaterie = new QLabel("Denumire materie");
    createField(lblCampDenumireMaterie, campDenumireMaterie, 6);

    for(auto [widget, id]: widgets) {
        if(id == 0 || id == 4 || id == 5) widget->show();
    }

    lyVertical->addLayout(lyFormular);

    btnAdauga = new QPushButton("Adauga");
    btnModifica = new QPushButton("Modifica");
    lyVertical->addWidget(btnAdauga);
    lyVertical->addWidget(btnModifica);

    lySecundar->addLayout(lyVertical);
    lyMain->addLayout(lySecundar);

    this->setLayout(lyMain);
    this->setStyleSheet("background-color: #A2B2C3; color: black;");
    this->resize(800, 300);
    this->setWindowTitle("Admin");
}

void AdminWindow::conectareSemnale() {
    connect(btnAdauga, &QPushButton::clicked, [this]() {
        const std::string tip = comboTabela->currentText().toStdString();
        switch(tipuri.at(tip)) {
        case 0: {
            const auto id = campId->text().toInt();
            const auto nume = campNume->text().toStdString();
            const auto email = campEmail->text().toStdString();
            const auto parola = campParola->text().toStdString();
            const auto grupa = campGrupa->text().toInt();
            try {
                service.adaugaStudent(id, nume, email, parola, grupa);
                model->setStudenti(service.getAllStudenti());
            } catch(const RepositoryError& re) {
                QMessageBox::warning(this, "Eroare", re.what());
            } catch(const ValidationError& ve) {
                QMessageBox::warning(this, "Eroare", ve.what());
            }
            break;
        }
        case 1: {
            const auto id = campId->text().toInt();
            const auto nume = campNume->text().toStdString();
            const auto email = campEmail->text().toStdString();
            const auto parola = campParola->text().toStdString();
            const auto departament = campDepartament->text().toStdString();
            try {
                service.adaugaProfesor(id, nume, email, parola, departament);
                model->setProfesori(service.getAllProfesori());
            } catch(const RepositoryError& re) {
                QMessageBox::warning(this, "Eroare", re.what());
            } catch(const ValidationError& ve) {
                QMessageBox::warning(this, "Eroare", ve.what());
            }
            break;
        }
        case 2: {
            const auto id = campId->text().toInt();
            const auto denumire = campDenumireMaterie->text().toStdString();
            const auto nume_profesor = campNume->text().toStdString();
            try {
                service.adaugaMaterie(id, denumire, nume_profesor);
                model->setMaterii(service.getAllMaterii());
            } catch(const RepositoryError& re) {
                QMessageBox::warning(this, "Eroare", re.what());
            }
            break;
        }
        case 3: {
            const auto id = campId->text().toInt();
            const auto nume_student = campNume->text().toStdString();
            const auto valoare_nota = campNota->text().toInt();
            const auto denumire_materie = campDenumireMaterie->text().toStdString();
            try {
                service.adaugaNota(id, valoare_nota, nume_student, denumire_materie);
                model->setNote(service.getAllNote());
            } catch(const RepositoryError& re) {
                QMessageBox::warning(this, "Eroare", re.what());
            }
            break;
        }
            default: break;
        }
    });

    connect(comboTabela, &QComboBox::currentTextChanged, [this](const QString& tip) {
        model->setTip(tip.toStdString());
        for(const auto widget: widgets|std::views::keys) widget->hide();
        switch(tipuri.at(tip.toStdString())) {
            case 0: {
                for(auto [widget, id]: widgets) {
                    if(id == 0 || id == 4 || id == 5 || id == -1) widget->show();
                }
                break;
            }
            case 1: {
                for(auto [widget, id]: widgets) {
                    if(id == 1 || id == 4 || id == 5 || id == -1) widget->show();
                }
                break;
            }
            case 2: {
                for(auto [widget, id]: widgets) {
                    if(id == 2 || id == 6 || id == 5 || id == -1) widget->show();
                }
                break;
            }
            case 3: {
                for(auto [widget, id]: widgets) {
                    if(id == 3 || id == 5 || id == 6 || id == -1) widget->show();
                }
                break;
            }
            default: break;
        }
    });

    connect(btnModifica, &QPushButton::clicked, [this]() {
        const auto tip = comboTabela->currentText().toStdString();

        const int id = campId->text().toInt();
        const int id_materie = campId->text().toInt();
        const std::string nume = campNume->text().toStdString();
        const std::string email = campEmail->text().toStdString();
        const std::string parola = campParola->text().toStdString();
        const int grupa = campGrupa->text().toInt();
        const std::string departament = campDepartament->text().toStdString();
        const std::string denumireMaterie = campDenumireMaterie->text().toStdString();
        const int nota = campNota->text().toInt();

        try {
            switch(tipuri.at(tip)) {
                case 0:
                    service.modificaStudent(id, nume, email, parola, grupa);
                    break;
                case 1:
                    service.modificaProfesor(id, nume, email, parola, departament);
                    break;
                case 2:
                    service.modificaMaterie(id_materie, denumireMaterie, id);
                    break;
                case 3:
                    service.modificaNota(nume, denumireMaterie, nota);
                    break;
                default: break;
            }
            reincarcareTabela();
        } catch(const RepositoryError& re) {
            QMessageBox::warning(this, "Eroare", re.what());
        } catch(const std::out_of_range&) {
            QMessageBox::warning(this, "Eroare", "Tip invalid de entitate.");
        }
    });

    connect(tabela->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        const auto idx = tabela->selectionModel()->selectedIndexes();
        const int row = idx.at(0).row();
        const std::string tip = comboTabela->currentText().toStdString();

        switch(tipuri.at(tip)) {
            case 0: {
                const QModelIndex idxId = model->index(row, 0);
                const QModelIndex idxNume = model->index(row, 1);
                const QModelIndex idxEmail = model->index(row, 2);
                const QModelIndex idxParola = model->index(row, 3);
                const QModelIndex idxGrupa = model->index(row, 4);
                campId->setText(model->data(idxId, Qt::DisplayRole).toString());
                campNume->setText(model->data(idxNume, Qt::DisplayRole).toString());
                campEmail->setText(model->data(idxEmail, Qt::DisplayRole).toString());
                campParola->setText(model->data(idxParola, Qt::DisplayRole).toString());
                campGrupa->setText(model->data(idxGrupa, Qt::DisplayRole).toString());
                break;
            }
            case 1: {
                const QModelIndex idxId = model->index(row, 0);
                const QModelIndex idxNume = model->index(row, 1);
                const QModelIndex idxEmail = model->index(row, 2);
                const QModelIndex idxParola = model->index(row, 3);
                const QModelIndex idxDepartament = model->index(row, 4);
                campId->setText(model->data(idxId, Qt::DisplayRole).toString());
                campNume->setText(model->data(idxNume, Qt::DisplayRole).toString());
                campEmail->setText(model->data(idxEmail, Qt::DisplayRole).toString());
                campParola->setText(model->data(idxParola, Qt::DisplayRole).toString());
                campDepartament->setText(model->data(idxDepartament, Qt::DisplayRole).toString());
                break;
            }
            case 2: {
                const QModelIndex idxIdMaterie = model->index(row, 0);
                const QModelIndex idxDenumire = model->index(row, 1);
                const QModelIndex idxNumeProfesor = model->index(row, 2);
                campId->setText(model->data(idxIdMaterie, Qt::DisplayRole).toString());
                campDenumireMaterie->setText(model->data(idxDenumire, Qt::DisplayRole).toString());
                campNume->setText(model->data(idxNumeProfesor, Qt::DisplayRole).toString());
                break;
            }
            case 3: {
                const QModelIndex idxNume = model->index(row, 1);
                const QModelIndex idxDenumire = model->index(row, 2);
                const QModelIndex idxNota = model->index(row, 3);
                campNume->setText(model->data(idxNume, Qt::DisplayRole).toString());
                campDenumireMaterie->setText(model->data(idxDenumire, Qt::DisplayRole).toString());
                campNota->setText(model->data(idxNota, Qt::DisplayRole).toString());
                break;
            }
            default: break;
        }

    });
}

void AdminWindow::reincarcareTabela() const {
    model->setStudenti(service.getAllStudenti());
    model->setProfesori(service.getAllProfesori());
    model->setMaterii(service.getAllMaterii());
    model->setNote(service.getAllNote());
}

void AdminWindow::createField(QLabel* label, QLineEdit* camp, int id) {
    camp->setPlaceholderText(label->text());
    lyFormular->addRow(label, camp);
    widgets.insert({camp, id});
    widgets.insert({label, id});
    if(id != -1) {
        camp->hide();
        label->hide();
    }
}

AdminWindow::AdminWindow(Service &service) : service(service) {
    initializareGUI();
    conectareSemnale();
}
