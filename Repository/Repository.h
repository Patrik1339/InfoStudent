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

    // Metode care citesc datele din baza de date si le adauga in vectori
    void loadDatabase();
    void incarcaStudenti();
    void incarcaProfesori();
    void incarcaMaterii();
    void incarcaNote();

    // Metode care actualizeaza baza de date dupa ce se fac modificari
    void updateDatabase() const;
    void updateStudenti() const;
    void updateProfesori() const;
    void updateMaterii() const;
    void updateNote() const;

public:
    // Constructor si destructor
    Repository();
    ~Repository() = default;

    // Getters
    std::vector<User*>& getUsers();
    std::vector<Nota>& getNote();
    std::vector<Materie>& getMaterii();
    std::vector<Student>& getStudenti();
    std::vector<Profesor>& getProfesori();

    // Metode care modifica datele
    void modificaStudent(const std::vector<Student>::iterator& it, const std::string& nume,
        const std::string& email, const std::string& password, int grupa) const;
    void modificaProfesor(const std::vector<Profesor>::iterator& it, const std::string& nume,
        const std::string& email, const std::string& password, const std::string& departament) const;
    void modificaMaterie(const std::vector<Materie>::iterator& it, const std::string& denumire, Profesor& profesor) const;
    void modificaNota(const std::vector<Nota>::iterator& it, int valoare) const;

    // Metode care adauga date
    void addStudent(Student& student);
    void addProfesor(Profesor& profesor);
    void addMaterie(const Materie& materie);
    void addNota(const Nota& nota);

    // Metode care sterg date
    void stergeStudent(const std::vector<Student>::iterator& it_s, const std::vector<User*>::iterator& it_u);
    void stergeProfesor(const std::vector<Profesor>::iterator& it_p, const std::vector<User*>::iterator& it_u);
    void stergeMaterie(const std::vector<Materie>::iterator& it_m);
    void stergeNota(const std::vector<Nota>::iterator& it_n);
};