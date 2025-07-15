#include "Repository.h"
#include <QMessageBox>
#include "sqlite3.h"
#include "../Erori/RepositoryError.h"


void Repository::loadDatabase() {
    sqlite3* db;
    int rc = sqlite3_open("../Repository/InfoStudent.db", &db);
    if(rc) {
        throw RepositoryError(sqlite3_errmsg(db));
    }

    const char* sql = "SELECT id, nume, email, password, grupa FROM Studenti;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if(rc != SQLITE_OK) {
        throw RepositoryError(sqlite3_errmsg(db));
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int grupa = sqlite3_column_int(stmt, 4);
        studenti.emplace_back(id, nume, email, password, grupa);
    }
    sqlite3_finalize(stmt);

    sql = "SELECT id, nume, email, password, departament from Profesori;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if(rc != SQLITE_OK) {
        throw RepositoryError(sqlite3_errmsg(db));
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string nume = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        std::string departament = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        profesori.emplace_back(id, nume, email, password, departament);
    }
    sqlite3_finalize(stmt);

    sql = "SELECT id, denumire, profesor_id from Materii;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if(rc != SQLITE_OK) {
        throw RepositoryError(sqlite3_errmsg(db));
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string denumire = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        int profesor_id = sqlite3_column_int(stmt, 2);
        auto it = std::ranges::find_if(profesori, [profesor_id](const auto& p) {
            return profesor_id == p.getId();
        });
        if(it == profesori.end()) {
            throw RepositoryError(sqlite3_errmsg(db));
        }
        Profesor* profesor_ptr = &(*it);
        materii.emplace_back(id, denumire, profesor_ptr);
    }
    sqlite3_finalize(stmt);

    sql = "SELECT id, valoare, student_id, materie_id from Note;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if(rc != SQLITE_OK) {
        throw RepositoryError(sqlite3_errmsg(db));
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        int valoare = sqlite3_column_int(stmt, 1);
        int student_id = sqlite3_column_int(stmt, 2);
        int materie_id = sqlite3_column_int(stmt, 3);
        auto it_s = std::ranges::find_if(studenti, [student_id](const auto& s) {
            return student_id == s.getId();
        });
        if(it_s == studenti.end()) {
            throw RepositoryError(sqlite3_errmsg(db));
        }
        Student* student_ptr = &(*it_s);
        auto it_m = std::ranges::find_if(materii, [materie_id](const auto& m) {
            return materie_id == m.getId();
        });
        if(it_m == materii.end()) {
            throw RepositoryError(sqlite3_errmsg(db));
        }
        Materie* materie_ptr = &(*it_m);
        note.emplace_back(id, valoare, student_ptr, materie_ptr);
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    for(Student& student: studenti) {
        users.push_back(&student);
    }
    for(Profesor& profesor: profesori) {
        users.push_back(&profesor);
    }
}

void Repository::updateDatabase() const {
    sqlite3* db;
    int rc = sqlite3_open("../Repository/InfoStudent.db", &db);
    if(rc) {
        throw RepositoryError(sqlite3_errmsg(db));
    }

    char* errMsg = nullptr;

    const char* sqlDelete =
        "DELETE FROM Note;"
        "DELETE FROM Materii;"
        "DELETE FROM Profesori;"
        "DELETE FROM Studenti;";
    rc = sqlite3_exec(db, sqlDelete, nullptr, nullptr, &errMsg);
    if(rc != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Eroare la ștergere tabele";
        sqlite3_free(errMsg);
        sqlite3_close(db);
        throw RepositoryError(error);
    }

    const char* sqlInsertStudent = "INSERT INTO Studenti (id, nume, email, password, grupa) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmtStudent;
    rc = sqlite3_prepare_v2(db, sqlInsertStudent, -1, &stmtStudent, nullptr);
    if(rc != SQLITE_OK) {
        sqlite3_close(db);
        throw RepositoryError(sqlite3_errmsg(db));
    }
    for(const auto& s : studenti) {
        sqlite3_bind_int(stmtStudent, 1, s.getId());
        sqlite3_bind_text(stmtStudent, 2, s.getNume().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtStudent, 3, s.getEmail().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtStudent, 4, s.getPassword().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtStudent, 5, s.getGrupa());

        rc = sqlite3_step(stmtStudent);
        if(rc != SQLITE_DONE) {
            sqlite3_finalize(stmtStudent);
            sqlite3_close(db);
            throw RepositoryError(sqlite3_errmsg(db));
        }
        sqlite3_reset(stmtStudent);
    }
    sqlite3_finalize(stmtStudent);

    const char* sqlInsertProfesor = "INSERT INTO Profesori (id, nume, email, password, departament) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmtProfesor;
    rc = sqlite3_prepare_v2(db, sqlInsertProfesor, -1, &stmtProfesor, nullptr);
    if(rc != SQLITE_OK) {
        sqlite3_close(db);
        throw RepositoryError(sqlite3_errmsg(db));
    }
    for(const auto& p : profesori) {
        sqlite3_bind_int(stmtProfesor, 1, p.getId());
        sqlite3_bind_text(stmtProfesor, 2, p.getNume().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtProfesor, 3, p.getEmail().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtProfesor, 4, p.getPassword().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmtProfesor, 5, p.getDepartament().c_str(), -1, SQLITE_TRANSIENT);

        rc = sqlite3_step(stmtProfesor);
        if(rc != SQLITE_DONE) {
            sqlite3_finalize(stmtProfesor);
            sqlite3_close(db);
            throw RepositoryError(sqlite3_errmsg(db));
        }
        sqlite3_reset(stmtProfesor);
    }
    sqlite3_finalize(stmtProfesor);

    const char* sqlInsertMaterie = "INSERT INTO Materii (id, denumire, profesor_id) VALUES (?, ?, ?);";
    sqlite3_stmt* stmtMaterie;
    rc = sqlite3_prepare_v2(db, sqlInsertMaterie, -1, &stmtMaterie, nullptr);
    if(rc != SQLITE_OK) {
        sqlite3_close(db);
        throw RepositoryError(sqlite3_errmsg(db));
    }
    for(const auto& m : materii) {
        sqlite3_bind_int(stmtMaterie, 1, m.getId());
        sqlite3_bind_text(stmtMaterie, 2, m.getDenumire().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtMaterie, 3, m.getProfesor().getId());

        rc = sqlite3_step(stmtMaterie);
        if(rc != SQLITE_DONE) {
            sqlite3_finalize(stmtMaterie);
            sqlite3_close(db);
            throw RepositoryError(sqlite3_errmsg(db));
        }
        sqlite3_reset(stmtMaterie);
    }
    sqlite3_finalize(stmtMaterie);

    const char* sqlInsertNota = "INSERT INTO Note (id, valoare, student_id, materie_id) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmtNota;
    rc = sqlite3_prepare_v2(db, sqlInsertNota, -1, &stmtNota, nullptr);
    if(rc != SQLITE_OK) {
        sqlite3_close(db);
        throw RepositoryError(sqlite3_errmsg(db));
    }
    for(const auto& n : note) {
        sqlite3_bind_int(stmtNota, 1, n.getId());
        sqlite3_bind_int(stmtNota, 2, n.getValoare());
        sqlite3_bind_int(stmtNota, 3, n.getStudent().getId());
        sqlite3_bind_int(stmtNota, 4, n.getMaterie().getId());

        rc = sqlite3_step(stmtNota);
        if(rc != SQLITE_DONE) {
            sqlite3_finalize(stmtNota);
            sqlite3_close(db);
            throw RepositoryError(sqlite3_errmsg(db));
        }
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
    const std::string& email, const std::string& password, int grupa) {
    it->setAtributes(nume, email, password, grupa);
    updateDatabase();
}

void Repository::modificaProfesor(const std::vector<Profesor>::iterator &it, const std::string &nume,
    const std::string &email, const std::string &password, const std::string &departament) {
    it->setAtributes(nume, email, password, departament);
    updateDatabase();
}

void Repository::modificaMaterie(const std::vector<Materie>::iterator &it, const std::string &denumire, Profesor& profesor) {
    it->setAtributes(denumire, &profesor);
    updateDatabase();
}

void Repository::modificaNota(const std::vector<Nota>::iterator& it, const int valoare) const {
    it->setValoare(valoare);
    updateDatabase();
}
