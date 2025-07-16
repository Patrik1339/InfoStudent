#pragma once
#include <exception>
#include <string>


class ValidationError final: public std::exception {
private:
    std::string mesaj;

public:
    explicit ValidationError(const std::string& mesaj): mesaj(mesaj) {}

    const char *what() const noexcept override {
        return mesaj.c_str();
    }
};