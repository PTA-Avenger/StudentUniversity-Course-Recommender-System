// Subject.h
#pragma once
#include <QString>

class Subject {
public:
    Subject(QString name, int mark);

    QString name;
    int mark;

    int toAPS() const;
};
