#include "Repository.h"
#include <QMessageBox>
#include "sqlite3.h"
#include "../Erori/RepositoryError.h"


void Repository::loadDatabase() {
    incarcaStudenti();
    incarcaProfesori();
    incarcaMaterii();
    incarcaNote();
}

void Repository::incarcaStudenti() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    sqlite3_open("../Repository/InfoStudent.db", &db);
    const char* sql = "SELECT id, nume, email, password, grupa FROM Studenti;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* nume = sqlite3_column_text(stmt, 1);
        const unsigned char* email = sqlite3_column_text(stmt, 2);
        const unsigned char* parola = sqlite3_column_text(stmt, 3);
        int grupa = sqlite3_column_int(stmt, 4);

        studenti.emplace_back(id, reinterpret_cast<const char*>(nume), reinterpret_cast<const char*>(email),
            reinterpret_cast<const char*>(parola), grupa);
        users.emplace_back(new Student(id, reinterpret_cast<const char*>(nume), reinterpret_cast<const char*>(email),
            reinterpret_cast<const char*>(parola), grupa));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Repository::incarcaProfesori() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    sqlite3_open("../Repository/InfoStudent.db", &db);
    const char* sql = "SELECT id, nume, email, password, departament FROM Profesori;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* nume = sqlite3_column_text(stmt, 1);
        const unsigned char* email = sqlite3_column_text(stmt, 2);
        const unsigned char* parola = sqlite3_column_text(stmt, 3);
        const unsigned char* departament = sqlite3_column_text(stmt, 4);

        profesori.emplace_back(id, reinterpret_cast<const char*>(nume), reinterpret_cast<const char*>(email),
            reinterpret_cast<const char*>(parola), reinterpret_cast<const char*>(departament));
        users.emplace_back(new Profesor(id, reinterpret_cast<const char*>(nume), reinterpret_cast<const char*>(email),
            reinterpret_cast<const char*>(parola), reinterpret_cast<const char*>(departament)));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Repository::incarcaMaterii() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    sqlite3_open("../Repository/InfoStudent.db", &db);
    const char* sql = "SELECT id, denumire, profesor_id FROM Materii;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* denumire = sqlite3_column_text(stmt, 1);
        int profesor_id = sqlite3_column_int(stmt, 2);

        auto it = std::ranges::find_if(profesori, [profesor_id](auto& profesor) {
            return profesor_id == profesor.getId();
        });
        materii.emplace_back(id, reinterpret_cast<const char*>(denumire), &*it);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Repository::incarcaNote() {
    sqlite3* db;
    sqlite3_stmt* stmt;

    sqlite3_open("../Repository/InfoStudent.db", &db);
    const char* sql = "SELECT id, valoare, student_id, materie_id FROM Note;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int valoarea = sqlite3_column_int(stmt, 1);
        int student_id = sqlite3_column_int(stmt, 2);
        int materie_id = sqlite3_column_int(stmt, 3);

        auto it_s = std::ranges::find_if(studenti, [student_id](auto& student) {
            return student_id == student.getId();
        });
        auto it_m = std::ranges::find_if(materii, [materie_id](auto& materie) {
            return materie_id == materie.getId();
        });
        note.emplace_back(id, valoarea, &*it_s, &*it_m);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void Repository::updateDatabase() const {
    sqlite3* db;
    sqlite3_open("../Repository/../Repository/InfoStudent.db", &db);

    char* errMsg = nullptr;
    const char* sqlDelete =
        "DELETE FROM Note;"
        "DELETE FROM Materii;"
        "DELETE FROM Profesori;"
        "DELETE FROM Studenti;";
    sqlite3_exec(db, sqlDelete, nullptr, nullptr, &errMsg);
    sqlite3_close(db);

    updateStudenti();
    updateProfesori();
    updateMaterii();
    updateNote();
}

void Repository::updateStudenti() const {
    sqlite3* db;
    sqlite3_open("../Repository/../Repository/InfoStudent.db", &db);

    const char* sqlInsertStudent = "INSERT INTO Studenti (id, nume, email, password, grupa) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmtStudent;
    sqlite3_prepare_v2(db, sqlInsertStudent, -1, &stmtStudent, nullptr);
    for(const auto& s : studenti) {
        sqlite3_bind_int(stmtStudent, 1, s.getId());
        sqlite3_bind_text(stmtStudent, 2, s.getNume().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtStudent, 3, s.getEmail().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtStudent, 4, s.getPassword().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtStudent, 5, s.getGrupa());

        sqlite3_step(stmtStudent);
        sqlite3_reset(stmtStudent);
    }
    sqlite3_finalize(stmtStudent);
    sqlite3_close(db);
}

void Repository::updateProfesori() const {
    sqlite3* db;
    sqlite3_open("../Repository/../Repository/InfoStudent.db", &db);

    const char* sqlInsertProfesor = "INSERT INTO Profesori (id, nume, email, password, departament) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmtProfesor;
    sqlite3_prepare_v2(db, sqlInsertProfesor, -1, &stmtProfesor, nullptr);
    for(const auto& p : profesori) {
        sqlite3_bind_int(stmtProfesor, 1, p.getId());
        sqlite3_bind_text(stmtProfesor, 2, p.getNume().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtProfesor, 3, p.getEmail().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtProfesor, 4, p.getPassword().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtProfesor, 5, p.getDepartament().c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_step(stmtProfesor);
        sqlite3_reset(stmtProfesor);
    }
    sqlite3_finalize(stmtProfesor);
    sqlite3_close(db);
}

void Repository::updateMaterii() const {
    sqlite3* db;
    sqlite3_open("../Repository/../Repository/InfoStudent.db", &db);

    const char* sqlInsertMaterie = "INSERT INTO Materii (id, denumire, profesor_id) VALUES (?, ?, ?);";
    sqlite3_stmt* stmtMaterie;
    sqlite3_prepare_v2(db, sqlInsertMaterie, -1, &stmtMaterie, nullptr);
    for(const auto& m : materii) {
        sqlite3_bind_int(stmtMaterie, 1, m.getId());
        sqlite3_bind_text(stmtMaterie, 2, m.getDenumire().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtMaterie, 3, m.getProfesor().getId());

        sqlite3_step(stmtMaterie);
        sqlite3_reset(stmtMaterie);
    }
    sqlite3_finalize(stmtMaterie);
    sqlite3_close(db);
}

void Repository::updateNote() const {
    sqlite3* db;
    sqlite3_open("../Repository/../Repository/InfoStudent.db", &db);

    const char* sqlInsertNota = "INSERT INTO Note (id, valoare, student_id, materie_id) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmtNota;
    sqlite3_prepare_v2(db, sqlInsertNota, -1, &stmtNota, nullptr);
    for(const auto& n : note) {
        sqlite3_bind_int(stmtNota, 1, n.getId());
        sqlite3_bind_int(stmtNota, 2, n.getValoare());
        sqlite3_bind_int(stmtNota, 3, n.getStudent().getId());
        sqlite3_bind_int(stmtNota, 4, n.getMaterie().getId());

        sqlite3_step(stmtNota);
        sqlite3_reset(stmtNota);
    }
    sqlite3_finalize(stmtNota);
    sqlite3_close(db);
}

Repository::Repository() {
    loadDatabase();
}

std::vector<User*>& Repository::getUsers() {
    return users;
}

std::vector<Nota>& Repository::getNote() {
    return note;
}

std::vector<Materie>& Repository::getMaterii() {
    return materii;
}

std::vector<Student>& Repository::getStudenti() {
    return studenti;
}

std::vector<Profesor>& Repository::getProfesori() {
    return profesori;
}

void Repository::modificaStudent(const std::vector<Student>::iterator& it, const std::string& nume,
    const std::string& email, const std::string& password, const int grupa) const {
    it->setAtributes(nume, email, password, grupa);
    updateDatabase();
}

void Repository::modificaProfesor(const std::vector<Profesor>::iterator &it, const std::string &nume,
    const std::string &email, const std::string &password, const std::string &departament) const {
    it->setAtributes(nume, email, password, departament);
    updateDatabase();
}

void Repository::modificaMaterie(const std::vector<Materie>::iterator &it, const std::string& denumire,
    Profesor& profesor) const {
    it->setAtributes(denumire, &profesor);
    updateDatabase();
}

void Repository::modificaNota(const std::vector<Nota>::iterator& it, const int valoare) const {
    it->setValoare(valoare);
    updateDatabase();
}

void Repository::addStudent(Student& student) {
    studenti.push_back(student);
    users.push_back(&student);
    updateDatabase();
}

void Repository::addProfesor(Profesor& profesor) {
    profesori.push_back(profesor);
    users.push_back(&profesor);
    updateDatabase();
}

void Repository::addMaterie(const Materie& materie) {
    materii.push_back(materie);
    updateDatabase();
}

void Repository::addNota(const Nota& nota) {
    note.push_back(nota);
    updateDatabase();
}