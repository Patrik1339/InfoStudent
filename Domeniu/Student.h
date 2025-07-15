#pragma once
#include <string>
#include "User.h"


class Student final: public User {
private:
    int grupa;

public:
    Student(int id, const std::string& nume, const std::string& email, const std::string& password, int grupa);
    ~Student() override = default;

    [[nodiscard]] int getGrupa() const;
    void setAtributes(const std::string& nume, const std::string& email, const std::string& password, int grupa);
};