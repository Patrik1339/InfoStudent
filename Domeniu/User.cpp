#include "User.h"


User::User(const int id, const std::string& nume, const std::string& email, const std::string& password):
    id(id), nume(nume), email(email), password(password) {}

int User::getId() const {
    return id;
}

const std::string &User::getNume() const {
    return nume;
}

const std::string& User::getEmail() const {
    return email;
}

const std::string& User::getPassword() const {
    return password;
}

bool User::operator==(const User &ot) const {
    return id == ot.id && nume == ot.nume && email == ot.email && password == ot.password;
}