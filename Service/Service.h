#pragma once
#include "../Repository/Repository.h"
#include "../Domeniu/Nota.h"


class Service {
private:
    Repository& repository;

public:
    explicit Service(Repository& repository);
    ~Service() = default;

    [[nodiscard]] User* login(const std::string& email, const std::string& password) const;

    std::vector<Nota> getNote(const User& user) const;
    std::vector<Materie> getMaterii(const User& user) const;
    [[nodiscard]] const std::vector<Student>& getAllStudenti() const;
    [[nodiscard]] const std::vector<Profesor>& getAllProfesori() const;
    [[nodiscard]] const std::vector<Materie>& getAllMaterii() const;
    [[nodiscard]] const std::vector<Nota>& getAllNote() const;
    void modificaStudent(int id, const std::string& nume, const std::string& email, const std::string& password, int grupa) const;
    void modificaProfesor(int id, const std::string& nume, const std::string& email, const std::string& password, const std::string& departament) const;
    void modificaMaterie(int id, const std::string& denumire, int id_profesor) const;
    void modificaNota(const std::string& nume_student, const std::string& materie, int valoare_nota_noua) const;
    void modificaNota(int id_student, int id_materie, int valoare_nota_noua) const;
};