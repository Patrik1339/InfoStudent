#pragma once
#include "Materie.h"
#include "Student.h"


class Nota {
private:
    int id;
    int valoare;
    Student* student;
    Materie* materie;

public:
    Nota(int id, int valoare, Student* student, Materie* materie);
    ~Nota() = default;

    [[nodiscard]] int getId() const;
    [[nodiscard]] int getValoare() const;
    [[nodiscard]] const User& getStudent() const;
    [[nodiscard]] const Materie& getMaterie() const;
    void setValoare(int valoare_noua);
};
