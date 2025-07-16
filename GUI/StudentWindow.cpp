#include "StudentWindow.h"
#include "../Erori/RepositoryError.h"
#include <QHeaderView>
#include "../Service/Service.h"


void StudentWindow::initializareGUI() {
    lyMain = new QVBoxLayout;

    lySus = new QHBoxLayout;

    const std::string str_lbl = "Student: " + user->getNume();
    nume = new QLabel(QString::fromStdString(str_lbl));
    nume->setStyleSheet("font: 14pt;");
    lySus->addWidget(nume);

    btnLogout = new QPushButton("Logout");
    btnLogout->setStyleSheet("background-color: grey;");
    lySus->addWidget(btnLogout);
    lyMain->addLayout(lySus);

    lblNote = new QLabel("Note");
    lblNote->setAlignment(Qt::AlignHCenter);
    lyMain->addWidget(lblNote);

    tabelNote = new QTableView;
    model = new Model(service.getNote(*user));
    tabelNote->setModel(model);
    tabelNote->resizeColumnsToContents();
    tabelNote->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    lyMain->addWidget(tabelNote);

    this->setLayout(lyMain);
    this->resize(600, 300);
    this->setStyleSheet("background-color: #A2B2C3; color: black;");
    this->setWindowTitle("Student");
}

void StudentWindow::conectareSemnale() {
    connect(btnLogout, &QPushButton::clicked, [this]() {
        mainWindow->show();
        this->close();
        this->deleteLater();
    });
}

void StudentWindow::updateObserver() {
    model->setNote(service.getNote(*user));
}

StudentWindow::StudentWindow(QWidget* mainWindow, Service& service, Student* student):
    UserWindow(mainWindow, service, student) {
    initializareGUI();
    conectareSemnale();
}
