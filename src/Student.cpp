// Student.cpp
#include "Student.h"

void Student::addSubject(const Subject &s) {
    subjects.append(s);
}

int Student::totalAPS() const {
    int total = 0;
    for (const Subject &s : subjects)
        total += s.toAPS();
    return total;
}

QString Student::apsBreakdown() const {
    QString result = "Subject-wise APS breakdown:\n";
    for (const Subject &s : subjects)
        result += QString("%1: %2 → APS %3\n")
                  .arg(s.name).arg(s.mark).arg(s.toAPS());
    result += "\nTotal APS: " + QString::number(totalAPS());
    return result;
}
