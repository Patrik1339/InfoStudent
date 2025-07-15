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
                return;
            }
            User* user = service.login(email, parola);
            this->hide();
            campEmail->clear();
            campParola->clear();
            UserWindow* user_window;
            if(typeid(*user) == typeid(Student)) user_window = new StudentWindow(this, service, dynamic_cast<Student*>(user));
            else user_window = new ProfesorWindow(this, service, dynamic_cast<Profesor*>(user));
            user_window->show();
        } catch(const RepositoryError& re) {
            QMessageBox::warning(this, "Eroare", re.what());
        }
    });
}

MainWindow::MainWindow(const Service& service): service(service) {
    initializareGUI();
    conectareSemnale();
}
