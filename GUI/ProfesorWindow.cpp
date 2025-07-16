#include "ProfesorWindow.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QHeaderView>
#include "../Erori/RepositoryError.h"


void ProfesorWindow::initializareGUI() {
    lyMain = new QVBoxLayout;

    lySus = new QHBoxLayout;
    const std::string str_lbl = "Profesor: " + user->getNume();
    nume = new QLabel(QString::fromStdString(str_lbl));
    nume->setStyleSheet("font: 14pt;");
    lySus->addWidget(nume, 0, Qt::AlignLeft | Qt::AlignTop);
    btnLogout = new QPushButton("Logout");
    btnLogout->setStyleSheet("background-color: grey;");
    lySus->addWidget(btnLogout, 0, Qt::AlignRight | Qt::AlignTop);
    lyMain->addLayout(lySus);

    lyMaterii = new QVBoxLayout;
    lyMaterii->setSpacing(5);
    lyMaterii->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    labelMaterii = new QLabel("Alege o materie");
    lyMaterii->addWidget(labelMaterii, 0, Qt::AlignLeft);

    comboMaterii = new QComboBox;
    comboMaterii->setMaximumWidth(200);
    const std::vector<Materie>& materii = service.getMaterii(*user);
    for (const auto& materie : materii) {
        comboMaterii->addItem(QString::fromStdString(materie.getDenumire()));
    }
    lyMaterii->addWidget(comboMaterii, 0, Qt::AlignLeft);
    lyMain->addLayout(lyMaterii);

    lyJos = new QHBoxLayout;

    model = new ModelTabelMaterii;
    tabelaNoteMaterie = new QTableView;
    tabelaNoteMaterie->setModel(model);
    tabelaNoteMaterie->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    lyJos->addWidget(tabelaNoteMaterie);

    lyFormular = new QFormLayout;
    campNumeStudent = new QLineEdit;
    campNumeStudent->setPlaceholderText("Nume Student");
    lyFormular->addRow("Nume Student", campNumeStudent);
    campNota = new QLineEdit;
    campNota->setPlaceholderText("Nota");
    lyFormular->addRow("Nota", campNota);
    btnModificareNota = new QPushButton("Modifica nota");
    lyFormular->addRow(btnModificareNota);
    lyJos->addLayout(lyFormular);

    lyMain->addLayout(lyJos);

    lyMain->addStretch();

    this->setLayout(lyMain);
    this->resize(600, 300);
    this->setStyleSheet("background-color: #A2B2C3; color: black;");
    this->setWindowTitle("Profesor");
}


void ProfesorWindow::conectareSemnale() {
    connect(btnLogout, &QPushButton::clicked, [this]() {
        mainWindow->show();
        this->close();
        this->deleteLater();
    });

    connect(comboMaterii, &QComboBox::currentIndexChanged, [this]() {
        reincarcareTabel();
    });

    connect(tabelaNoteMaterie->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
        const auto idx = tabelaNoteMaterie->selectionModel()->selectedIndexes();
        const int row = idx.at(0).row();

        const QModelIndex idxNume = model->index(row, 0);
        const QModelIndex idxNota = model->index(row, 1);

        const QString nume_student = idxNume.data(Qt::DisplayRole).toString();
        campNumeStudent->setText(nume_student);
        const QString nota = idxNota.data(Qt::DisplayRole).toString();
        campNota->setText(nota);
    });

    connect(btnModificareNota, &QPushButton::clicked, [this]() {
        const auto nota_Q = campNota->text();
        const int nota = nota_Q.toInt();
        if(nota < 1 || nota > 10) {
            QMessageBox::warning(this, "Eroare", "Nota trebuie sa fie intre 1 si 10!");
            return;
        }
        const auto nume_student_Q = campNumeStudent->text();
        if(nume_student_Q.isEmpty()) {
            QMessageBox::warning(this, "Eroare", "Trebuie sa introduci numele unui student!");
            return;
        }
        std::string nume_student = nume_student_Q.toStdString();
        const auto materie_Q = comboMaterii->currentText();
        const std::string materie = materie_Q.toStdString();
        try {
            service.modificaNota(nume_student, materie, nota);
            reincarcareTabel();
        } catch(const RepositoryError& re) {
            QMessageBox::warning(this, "Eroare", re.what());
        }
    });
}

void ProfesorWindow::reincarcareTabel() const {
    const std::string denumire_materie = comboMaterii->currentText().toStdString();
    std::vector<Nota> note_materie;
    const std::vector<Nota> note = service.getAllNote();
    for(auto nota: note) {
        if(nota.getMaterie().getDenumire() == denumire_materie) note_materie.push_back(nota);
    }
    model->setNote(note_materie);
}

ProfesorWindow::ProfesorWindow(QWidget* mainWindow, Service& service, Profesor* student):
    UserWindow(mainWindow, service, student) {
    initializareGUI();
    conectareSemnale();
}
