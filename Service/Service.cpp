#include "Service.h"
#include <algorithm>
#include <fstream>
#include <ranges>
#include "../Erori/RepositoryError.h"


Service::Service(Repository& repository): repository(repository) {}

User* Service::login(const std::string& email, const std::string& password) const {
    const auto it = std::ranges::find_if(repository.getUsers(), [email, password](auto* user_ptr) {
        return user_ptr->getEmail() == email && user_ptr->getPassword() == password;
    });
    if(it == repository.getUsers().end()) {
        throw RepositoryError("Email sau parola incorecta!\n");
    }
    return *it;
}

std::vector<Nota> Service::getNote(const User& user) const {
    int id = user.getId();
    std::vector<Nota> note_student;
    std::vector<Nota> note = repository.getNote();
    std::ranges::copy_if(note, std::back_inserter(note_student), [id](const Nota& n) {
        return id == n.getStudent().getId();
    });
    return note_student;
}

std::vector<Materie> Service::getMaterii(const User &user) const {
    int id = user.getId();
    std::vector<Materie> materii_profesor;
    std::vector<Materie> materii = repository.getMaterii();
    std::ranges::copy_if(materii, std::back_inserter(materii_profesor), [id](const Materie& m) {
        return id == m.getProfesor().getId();
    });
    return materii_profesor;
}

const std::vector<Student>& Service::getAllStudenti() const {
    return repository.getStudenti();
}

const std::vector<Profesor>& Service::getAllProfesori() const {
    return repository.getProfesori();
}

const std::vector<Materie>& Service::getAllMaterii() const {
    return repository.getMaterii();
}

const std::vector<Nota>& Service::getAllNote() const {
    return repository.getNote();
}

void Service::modificaStudent(int id, const std::string& nume, const std::string& email, const std::string& password, const int grupa) const {
    const auto it = std::ranges::find_if(repository.getStudenti(), [id](auto& student) {
        return id == student.getId();
    });
    if(it == repository.getStudenti().end()) throw RepositoryError("Nu exista student cu acest id!\n");
    repository.modificaStudent(it, nume, email, password, grupa);
}

void Service::modificaProfesor(int id, const std::string &nume, const std::string &email, const std::string &password,
    const std::string &departament) const {
    const auto it = std::ranges::find_if(repository.getProfesori(), [id](auto& profesor) {
        return id == profesor.getId();
    });
    if(it == repository.getProfesori().end()) throw RepositoryError("Nu exista profesor cu acest id!\n");
    repository.modificaProfesor(it, nume, email, password, departament);
}

void Service::modificaMaterie(int id, const std::string &denumire, int id_profesor) const {
    const auto it = std::ranges::find_if(repository.getMaterii(), [id](auto& materie) {
        return id == materie.getId();
    });
    if(it == repository.getMaterii().end()) throw RepositoryError("Nu exista materie cu acest id!\n");

    auto it_p = std::ranges::find_if(repository.getProfesori(), [id_profesor](auto& profesor) {
        return id_profesor == profesor.getId();
    });
    if(it_p == repository.getProfesori().end()) throw RepositoryError("Nu exista profesor cu acest id!\n");

    repository.modificaMaterie(it, denumire, *it_p);
}

void Service::modificaNota(const std::string& nume_student, const std::string& materie, const int valoare_nota_noua) const {
    std::vector<Student>& studenti = repository.getStudenti();
    const auto it_s = std::ranges::find_if(studenti, [nume_student](auto& student) {
        return nume_student == student.getNume();
    });
    if(it_s == studenti.end()) throw RepositoryError("Nu exista student cu numele introdus!\n");
    int id_student = it_s->getId();

    const auto it_m = std::ranges::find_if(repository.getMaterii(), [materie](auto& m) {
        return materie == m.getDenumire();
    });
    if(it_m == repository.getMaterii().end()) throw RepositoryError("Nu exista materie cu denumirea introdusa!\n");
    int id_materie = it_m->getId();

    const auto it_n = std::ranges::find_if(repository.getNote(), [id_student, id_materie](auto& nota) {
        return id_student == nota.getStudent().getId() && id_materie == nota.getMaterie().getId();
    });
    if(it_n == repository.getNote().end()) throw RepositoryError("Nu exista nota pentru acest student la aceasta materie!\n");

    repository.modificaNota(it_n, valoare_nota_noua);
}


void Service::modificaNota(const int id_student, const int id_materie, const int valoare_nota_noua) const {
    const auto it_n = std::ranges::find_if(repository.getNote(), [id_student, id_materie](auto& nota) {
        return id_student == nota.getStudent().getId() && id_materie == nota.getMaterie().getId();
    });
    if(it_n == repository.getNote().end()) throw RepositoryError("Nu exista nota!\n");
    repository.modificaNota(it_n, valoare_nota_noua);
}
