#pragma once
#include "QAbstractTableModel"
#include "../Domeniu/Nota.h"


class ModelTabelMaterii final: public QAbstractTableModel {
private:
    std::vector<Nota> note;

public:
    ModelTabelMaterii() = default;
    explicit ModelTabelMaterii(const std::vector<Nota>& note): note(note) {}

    int rowCount(const QModelIndex &parent) const override {
        return note.size();
    }

    int columnCount(const QModelIndex &parent) const override {
        return 2;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
        if(orientation != Qt::Horizontal || role != Qt::DisplayRole) return QVariant();

        switch(section) {
            case 0: return QString("Nume Student");
            case 1: return QString("Nota");
            case 2: return QString("Nota restanta/marire");
            default: return QVariant();
        }
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if(!index.isValid() || index.row() < 0 || index.row() >= note.size() || role != Qt::DisplayRole) return QVariant();

        const Nota& nota = note[index.row()];

        switch(index.column()) {
            case 0: return QString::fromStdString(nota.getStudent().getNume());
            case 1: return QString::number(nota.getValoare());
            default: return QVariant();
        }
    }

    void setNote(const std::vector<Nota>& note) {
        beginResetModel();
        this->note = note;
        endResetModel();
    }
};
