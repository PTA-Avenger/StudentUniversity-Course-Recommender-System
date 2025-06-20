// CourseDatabase.h
#pragma once
#include "Course.h"
#include <QList>
#include <QString>

class CourseDatabase {
public:
    bool loadFromFile(const QString &path);
    QList<Course> getCourses() const;

private:
    QList<Course> courses;
};
