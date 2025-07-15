#include "Profesor.h"


Profesor::Profesor(const int id, const std::string& nume, const std::string& email, const std::string& password,
                    const std::string& departament): User(id, nume, email, password), departament(departament) {}

const std::string& Profesor::getDepartament() const {
    return departament;
}

void Profesor::setAtributes(const std::string &nume, const std::string &email, const std::string &password,
    const std::string &departament) {
    this->nume = nume;
    this->email = email;
    this->password = password;
    this->departament = departament;
}
