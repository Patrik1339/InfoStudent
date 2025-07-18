#include "Student.h"


Student::Student(const int id, const std::string& nume, const std::string& email, const std::string& password,
                const int grupa): User(id, nume, email, password), grupa(grupa) {}

int Student::getGrupa() const {
    return grupa;
}

void Student::setAtributes(const std::string& nume, const std::string& email, const std::string& password, int grupa) {
    this->nume = nume;
    this->email = email;
    this->password = password;
    this->grupa = grupa;
}

bool Student::operator==(const Student& ot) const {
    return id == ot.id && nume == ot.nume && email == ot.nume && password == ot.password && grupa == ot.grupa;
}
