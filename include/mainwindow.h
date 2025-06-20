#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void addSubject();
    void calculateAPS();
    void recommendCourses();

private:
    /* ---------- GUI widgets ---------- */
    QLineEdit   *subjectEdit;
    QLineEdit   *markEdit;
    QPushButton *addSubjectBtn;
    QListWidget *subjectList;

    QListWidget *careerList;         /* multi‑select career interests  */
    QPushButton *calcApsBtn;
    QPushButton *recommendBtn;
    QTextEdit   *outputBox;          /* shows APS breakdown & matches  */

    /* ---------- data models ---------- */
    struct Subject {
        QString name;
        int     mark;
    };
    struct Course {
        QString name;
        QString university;
        int     requiredAPS;
        QString field;
    };

    QList<Subject> subjects;
    QList<Course>  courses;          /* loaded once from txt file      */

    /* ---------- helper functions ---------- */
    void loadCoursesFile(const QString &filePath = "university_courses.txt");
    static int  markToAPS(int mark);
    int         totalAPS() const;
    QString     breakdownAPS() const;
    QString     recommendations(const QStringList &interests) const;

    /* ---------- constants ---------- */
    inline static const int MAX_SUBJECTS  = 7;
    inline static const int MAX_INTERESTS = 3;
    inline static const QStringList careerOptions = {
        "Engineering", "Health Sciences", "Information Technology",
        "Law", "Education", "Commerce", "Humanities"
    };
};

#endif // MAINWINDOW_H
