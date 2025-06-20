// Student.h
#pragma once
#include "Subject.h"
#include <QList>

class Student {
public:
    void addSubject(const Subject &s);
    int totalAPS() const;
    QString apsBreakdown() const;

private:
    QList<Subject> subjects;
};
