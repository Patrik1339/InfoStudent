#pragma once
#include <QAbstractTableModel>
#include "../Domeniu/Student.h"
#include "../Domeniu/Profesor.h"
#include "../Domeniu/Materie.h"
#include "../Domeniu/Nota.h"


Q_DECLARE_METATYPE(Student)
Q_DECLARE_METATYPE(Profesor)
Q_DECLARE_METATYPE(Materie)
Q_DECLARE_METATYPE(Nota)

class ModelTabelGeneral final: public QAbstractTableModel {
private:
    std::string tip;
    std::vector<Student> studenti;
    std::vector<Profesor> profesori;
    std::vector<Materie> materii;
    std::vector<Nota> note;
    std::unordered_map<std::string, int> tipuri = {{"studenti", 0}, {"profesori", 1}, {"materii", 2}, {"note", 3}};

public:
    ModelTabelGeneral(const std::string& tip, const std::vector<Student>& studenti, const std::vector<Profesor>& profesori,
        const std::vector<Materie>& materii, const std::vector<Nota>& note): tip(tip), studenti(studenti),
        profesori(profesori), materii(materii), note(note) {}

    int rowCount(const QModelIndex&) const override {
        switch(tipuri.at(tip)) {
            case 0: return studenti.size();
            case 1: return profesori.size();
            case 2: return materii.size();
            case 3: return note.size();
            default: return 0;
        }
    }

    int columnCount(const QModelIndex&) const override {
        switch(tipuri.at(tip)) {
            case 0: return 5;
            case 1: return 5;
            case 2: return 3;
            case 3: return 4;
            default: return 0;
        }
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if(orientation != Qt::Horizontal || role != Qt::DisplayRole) return QVariant();

        const std::string str_id = "Id " + tip;
        if(section == 0) return QString::fromStdString(str_id);

        switch(tipuri.at(tip)) {
            case 0: {
                switch(section) {
                case 1: return QString::fromStdString("Nume student");
                case 2: return QString::fromStdString("Email");
                case 3: return QString::fromStdString("Parola");
                case 4: return QString::fromStdString("Grupa");
                default: return QVariant();
                }
            }
            case 1: {
                switch(section) {
                    case 1: return QString::fromStdString("Nume profesor");
                    case 2: return QString::fromStdString("Email");
                    case 3: return QString::fromStdString("Parola");
                    case 4: return QString::fromStdString("Departament");
                    default: return QVariant();
                }
            }
            case 2: {
                switch(section) {
                    case 1: return QString::fromStdString("Denumire");
                    case 2: return QString::fromStdString("Nume profesor");
                    default: return QVariant();
                }
            }
            case 3: {
                switch(section) {
                    case 1: return QString::fromStdString("Nume student");
                    case 2: return QString::fromStdString("Materie");
                    case 3: return QString::fromStdString("Nota");
                    default: return QVariant();
                }
            }
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex& index, int role) const override {
        if(role == Qt::DisplayRole) {
            switch(tipuri.at(tip)) {
            case 0: {
                const auto& s = studenti[index.row()];
                switch(index.column()) {
                case 0: return QString::number(s.getId());
                case 1: return QString::fromStdString(s.getNume());
                case 2: return QString::fromStdString(s.getEmail());
                case 3: return QString::fromStdString(s.getPassword());
                case 4: return s.getGrupa();
                default: return QVariant();
                }
            }
            case 1: {
                const auto& p = profesori[index.row()];
                switch(index.column()) {
                case 0: return QString::number(p.getId());
                case 1: return QString::fromStdString(p.getNume());
                case 2: return QString::fromStdString(p.getEmail());
                case 3: return QString::fromStdString(p.getPassword());
                case 4: return QString::fromStdString(p.getDepartament());
                default: return QVariant();
                }
            }
            case 2: {
                const auto& m = materii[index.row()];
                switch(index.column()) {
                case 0: return QString::number(m.getId());
                case 1: return QString::fromStdString(m.getDenumire());
                case 2: return QString::fromStdString(m.getProfesor().getNume());
                default: return QVariant();
                }
            }
            case 3: {
                const auto& n = note[index.row()];
                switch(index.column()) {
                case 0: return QString::number(n.getId());
                case 1: return QString::fromStdString(n.getStudent().getNume());
                case 2: return QString::fromStdString(n.getMaterie().getDenumire());
                case 3: return QString::number(n.getValoare());
                default: return QVariant();
                }
            }
            default: return QVariant();
            }
        }

        if(role == Qt::UserRole) {
            switch(tipuri.at(tip)) {
                case 0: return QString::number(studenti[index.row()].getId());
                case 1: return QString::number(profesori[index.row()].getId());
                case 2: return QString::number(materii[index.row()].getId());
                case 3: return QString::number(note[index.row()].getId());
                default: return QVariant();
            }
        }

        return QVariant();
    }

    void setStudenti(const std::vector<Student>& studenti) {
        beginResetModel();
        this->studenti = studenti;
        endResetModel();
    }

    void setProfesori(const std::vector<Profesor>& profesori) {
        beginResetModel();
        this->profesori = profesori;
        endResetModel();
    }

    void setMaterii(const std::vector<Materie>& materii) {
        beginResetModel();
        this->materii = materii;
        endResetModel();
    }

    void setNote(const std::vector<Nota>& note) {
        beginResetModel();
        this->note = note;
        endResetModel();
    }

    void setTip(const std::string& tip) {
        beginResetModel();
        this->tip = tip;
        endResetModel();
    }
};