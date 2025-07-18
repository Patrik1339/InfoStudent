#pragma once
#include <string>


class User {
protected:
    int id;
    std::string nume;
    std::string email;
    std::string password;

public:
    User() = default;
    User(int id, const std::string& nume, const std::string& email, const std::string& password);
    virtual ~User() = default;

    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string& getNume() const;
    [[nodiscard]] const std::string& getEmail() const;
    [[nodiscard]] const std::string& getPassword() const;

    bool operator==(const User& ot) const;
};