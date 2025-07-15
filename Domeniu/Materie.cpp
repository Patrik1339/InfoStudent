#include "Materie.h"


Materie::Materie(const int id, const std::string& denumire, Profesor* profesor): id(id), denumire(denumire),
    profesor(profesor) {}

int Materie::getId() const {
    return id;
}

const std::string& Materie::getDenumire() const {
    return denumire;
}

const Profesor& Materie::getProfesor() const {
    return *profesor;
}

void Materie::setAtributes(const std::string &denumire, Profesor *profesor) {
    this->denumire = denumire;
    this->profesor = profesor;
}
