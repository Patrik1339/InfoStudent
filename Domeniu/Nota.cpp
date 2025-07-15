#include "Nota.h"


Nota::Nota(const int id, const int valoare, Student* student, Materie* materie): id(id), valoare(valoare),
    student(student), materie(materie) {}

int Nota::getId() const {
    return id;
}

int Nota::getValoare() const {
    return valoare;
}

const User& Nota::getStudent() const {
    return *student;
}

const Materie& Nota::getMaterie() const {
    return *materie;
}

void Nota::setValoare(const int valoare_noua) {
    valoare = valoare_noua;
}
