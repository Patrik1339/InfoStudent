#pragma once
#include <string>
#include <vector>
#include "../Domeniu/Nota.h"
#include "../Domeniu/Materie.h"
#include "../Domeniu/Profesor.h"
#include "../Domeniu/Student.h"


class Repository {
private:
    std::vector<User*> users;
    std::vector<Student> studenti;
    std::vector<Profesor> profesori;
    std::vector<Materie> materii;
    std::vector<Nota> note;

    void loadDatabase();
    void incarcaStudenti();
    void incarcaProfesori();
    void incarcaMaterii();
    void incarcaNote();
    void updateDatabase() const;
    void updateStudenti() const;
    void updateProfesori() const;
    void updateMaterii() const;
    void updateNote() const;

public:
    Repository();
    ~Repository() = default;

    std::vector<User*>& getUsers();
    std::vector<Nota>& getNote();
    std::vector<Materie>& getMaterii();
    std::vector<Student>& getStudenti();
    std::vector<Profesor>& getProfesori();
    void modificaStudent(const std::vector<Student>::iterator& it, const std::string& nume,
        const std::string& email, const std::string& password, int grupa) const;
    void modificaProfesor(const std::vector<Profesor>::iterator& it, const std::string& nume,
        const std::string& email, const std::string& password, const std::string& departament) const;
    void modificaMaterie(const std::vector<Materie>::iterator& it, const std::string& denumire, Profesor& profesor) const;
    void modificaNota(const std::vector<Nota>::iterator& it, int valoare) const;
    void addStudent(Student& student);
    void addProfesor(Profesor& profesor);
    void addMaterie(const Materie& materie);
    void addNota(const Nota& nota);
};