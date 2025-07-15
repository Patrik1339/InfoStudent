#pragma once
#include <string>
#include <vector>

#include "Profesor.h"
#include "Student.h"
#include "User.h"


class Materie {
private:
    int id;
    std::string denumire;
    Profesor* profesor;

public:
    Materie(int id, const std::string& denumire, Profesor* profesor);
    ~Materie() = default;

    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string& getDenumire() const;
    [[nodiscard]] const Profesor& getProfesor() const;
    void setAtributes(const std::string& denumire, Profesor* profesor);
};
