#pragma once
#include <exception>
#include <string>

using std::exception, std::string;


class RepositoryError final: public exception {
private:
    string mesaj;

public:
    explicit RepositoryError(const string& mesaj): mesaj(mesaj) {}

    const char *what() const noexcept override {
        return mesaj.c_str();
    }
};