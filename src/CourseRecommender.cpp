// CourseRecommender.cpp
#include "CourseRecommender.h"

QString CourseRecommender::recommend(const QList<Course> &courses,
                                     const QStringList &interests,
                                     int studentAPS) {
    QString output("🔍 Recommended Courses:\n");
    bool found = false;

    for (const Course &c : courses) {
        if (interests.contains(c.field) && studentAPS >= c.requiredAPS) {
            output += QString("- %1 at %2 (Required APS: %3)\n")
                      .arg(c.name).arg(c.university).arg(c.requiredAPS);
            found = true;
        }
    }

    if (!found)
        output += "❌ No matches found.\n";

    return output;
}
