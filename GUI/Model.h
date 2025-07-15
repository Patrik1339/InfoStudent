#pragma once
#include <QAbstractTableModel>
#include <qbrush.h>
#include "../Domeniu/Nota.h"


class Model final: public QAbstractTableModel {
private:
    std::vector<Nota> note;

public:
    explicit Model(const std::vector<Nota>& note): note(note) {}

    int rowCount(const QModelIndex &parent) const override {
        return note.size();
    }

    int columnCount(const QModelIndex &parent) const override {
        return 3;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if(orientation != Qt::Horizontal || role != Qt::DisplayRole) return QVariant();

        switch(section) {
            case 0: return QString("Materie");
            case 1: return QString("Nota");
            case 2: return QString("Profesor");
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if(!index.isValid() || index.row() < 0 || index.row() >= note.size()) return QVariant();

        const Nota& nota = note[index.row()];

        if(role == Qt::DisplayRole) {
            switch(index.column()) {
                case 0: return QString::fromStdString(nota.getMaterie().getDenumire());
                case 1: return QString::number(nota.getValoare());
                case 2: return QString::fromStdString(nota.getMaterie().getProfesor().getNume());
                default: return QVariant();
            }
        }

        if(role == Qt::ForegroundRole) {
            if(nota.getValoare() <= 4) return QBrush(Qt::red);
            return QVariant();
        }

        return QVariant();
    }

    void setNote(const std::vector<Nota>& note) {
        beginResetModel();
        this->note = note;
        endResetModel();
    }
};
