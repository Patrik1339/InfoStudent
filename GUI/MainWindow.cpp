#include "MainWindow.h"
#include <QMessageBox>

#include "AdminWindow.h"
#include "ProfesorWindow.h"
#include "StudentWindow.h"
#include "UserWindow.h"
#include "../Erori/RepositoryError.h"


void MainWindow::initializareGUI() {
    lyMain = new QVBoxLayout;

    titlu = new QLabel("InfoStudent");
    titlu->setStyleSheet("font: 18pt;");
    titlu->setAlignment(Qt::AlignHCenter);
    lyMain->addWidget(titlu);

    containerFormular = new QWidget;
    containerFormular->setFixedWidth(300);
    lyFormular = new QFormLayout(containerFormular);
    campEmail = new QLineEdit;
    lyFormular->addRow("Email", campEmail);
    campParola = new QLineEdit;
    campParola->setEchoMode(QLineEdit::Password);
    lyFormular->addRow("Parola", campParola);

    lyOrizontal = new QHBoxLayout;
    lyOrizontal->addWidget(containerFormular);
    lyMain->addLayout(lyOrizontal);

    btnLogin = new QPushButton("Login");
    btnLogin->setFixedWidth(100);
    lyButon = new QHBoxLayout;
    lyButon->addWidget(btnLogin);
    lyMain->addLayout(lyButon);

    this->setLayout(lyMain);
    this->setStyleSheet("background-color: #A2B2C3; color: black;");
    this->resize(600, 300);
}

void MainWindow::conectareSemnale() {
    connect(btnLogin, &QPushButton::clicked, [this]() {
        const auto email = campEmail->text().toStdString();
        const auto parola = campParola->text().toStdString();
        const bool empty_email_field = email.empty();
        const bool empty_password_field = parola.empty();
        if(empty_email_field && empty_password_field) {
            QMessageBox::warning(this, "Eroare", "Trebuie sa introduceti emailul si parola!\n");
            return;
        }
        if(empty_email_field) {
            QMessageBox::warning(this, "Eroare", "Trebuie sa introduceti emailul!\n");
            return;
        }
        if(empty_password_field) {
            QMessageBox::warning(this, "Eroare", "Trebuie sa introduceti parola!\n");
            return;
        }
        try {
            if(email == "admin" && parola == "admin") {
                const auto admin_window = new AdminWindow(service);
                admin_window->show();
                service.addObserver(admin_window);
                return;
            }

            User* user = service.login(email, parola);
            campEmail->clear();
            campParola->clear();

            if(const auto student = dynamic_cast<Student*>(user)) {
                const auto student_window = new StudentWindow(this, service, student);
                student_window->show();
                service.addObserver(student_window);
            }
            else if(const auto profesor = dynamic_cast<Profesor*>(user)) {
                const auto profesor_window = new ProfesorWindow(this, service, profesor);
                profesor_window->show();
                service.addObserver(profesor_window);
            }
            else {
                QMessageBox::warning(this, "Eroare", "Tip de utilizator invalid!\n");
            }
        } catch(const RepositoryError& re) {
            QMessageBox::warning(this, "Eroare", re.what());
        }
    });
}

MainWindow::MainWindow(const Service& service): service(service) {
    initializareGUI();
    conectareSemnale();
}
