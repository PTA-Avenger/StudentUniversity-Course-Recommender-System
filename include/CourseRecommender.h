// CourseRecommender.h
#pragma once
#include "Course.h"
#include <QString>
#include <QList>
#include <QStringList>

class CourseRecommender {
public:
    static QString recommend(const QList<Course> &courses,
                             const QStringList &interests,
                             int studentAPS);
};
