#pragma once
#include <QWidget>
#include "../Domeniu/User.h"
#include "../Service/Service.h"


class UserWindow: public QWidget {
protected:
    QWidget* mainWindow;
    Service& service;
    User* user;

public:
    explicit UserWindow(QWidget* mainWindow, Service& service, User* user): mainWindow(mainWindow), service(service),
        user(user) {}
};
