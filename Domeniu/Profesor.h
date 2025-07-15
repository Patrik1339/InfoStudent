#pragma once
#include "User.h"


class Profesor: public User {
private:
    std::string departament;

public:
    Profesor(int id, const std::string& nume, const std::string& email, const std::string& password, const std::string& departament);
    ~Profesor() override = default;

    [[nodiscard]] const std::string& getDepartament() const;
    void setAtributes(const std::string& nume, const std::string& email, const std::string& password, const std::string& departament);
};