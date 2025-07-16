#pragma once
#include <algorithm>
#include <string>
#include "../Erori/ValidationError.h"
#include "../Domeniu/Student.h"


class Validator {
public:
    static void ValideazaUser(const User& user) {
        std::string erori;
        if(user.getId() < 0) erori += "Id invalid!\n";
        if(!user.getEmail().find('@')) erori += "Email invalid!\n";
        if(!std::ranges::any_of(user.getPassword(), [](const char c) {
            return !std::isalnum(c) && !std::isspace(c);
        })) erori += "Parola trebuie sa contina un caracter special!\n";
        if(!erori.empty()) throw ValidationError(erori);
    }
};
