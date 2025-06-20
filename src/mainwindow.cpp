#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* ---------- build UI ---------- */
    auto *central = new QWidget(this);

    /* Left‑hand column: subject entry */
    subjectEdit = new QLineEdit;
    markEdit    = new QLineEdit;
    markEdit->setPlaceholderText("0–100");
    addSubjectBtn = new QPushButton("Add Subject");
    subjectList   = new QListWidget;

    auto *left = new QVBoxLayout;
    left->addWidget(new QLabel("<b>Subjects</b>"));
    left->addWidget(new QLabel("Name:"));
    left->addWidget(subjectEdit);
    left->addWidget(new QLabel("Mark:"));
    left->addWidget(markEdit);
    left->addWidget(addSubjectBtn);
    left->addWidget(subjectList);

    /* Right‑hand column: career interests + actions */
    careerList = new QListWidget;
    careerList->setSelectionMode(QAbstractItemView::MultiSelection);
    for (const auto &c : careerOptions) careerList->addItem(c);

    calcApsBtn   = new QPushButton("Calculate APS");
    recommendBtn = new QPushButton("Recommend Courses");
    outputBox    = new QTextEdit;
    outputBox->setReadOnly(true);

    auto *right = new QVBoxLayout;
    right->addWidget(new QLabel("<b>Career Interests</b> (select up to 3)"));
    right->addWidget(careerList);
    right->addWidget(calcApsBtn);
    right->addWidget(recommendBtn);
    right->addWidget(new QLabel("<b>Output</b>"));
    right->addWidget(outputBox);

    /* Overall layout */
    auto *top = new QHBoxLayout;
    top->addLayout(left,  1);
    top->addLayout(right, 1);
    central->setLayout(top);
    setCentralWidget(central);
    setWindowTitle("Student / University Course Recommender");

    /* Connections */
    connect(addSubjectBtn, &QPushButton::clicked, this, &MainWindow::addSubject);
    connect(calcApsBtn,    &QPushButton::clicked, this, &MainWindow::calculateAPS);
    connect(recommendBtn,  &QPushButton::clicked, this, &MainWindow::recommendCourses);

    /* Pre‑load course file */
    loadCoursesFile();
}

/* ---------- Button slots ---------- */

void MainWindow::addSubject()
{
    if (subjects.size() >= MAX_SUBJECTS) {
        QMessageBox::warning(this, "Limit reached",
                             "You’ve already added the maximum number of subjects.");
        return;
    }

    QString name = subjectEdit->text().trimmed();
    bool ok;
    int mark = markEdit->text().toInt(&ok);

    if (name.isEmpty() || !ok || mark < 0 || mark > 100) {
        QMessageBox::warning(this, "Input error",
                             "Please enter a subject name and a mark between 0 and 100.");
        return;
    }

    subjects.append({name, mark});
    subjectList->addItem(QString("%1: %2").arg(name).arg(mark));

    subjectEdit->clear();
    markEdit->clear();
}

void MainWindow::calculateAPS()
{
    if (subjects.isEmpty()) {
        QMessageBox::information(this, "No subjects",
                                 "Add at least one subject first.");
        return;
    }

    outputBox->setPlainText(breakdownAPS());
}

void MainWindow::recommendCourses()
{
    if (subjects.isEmpty()) {
        QMessageBox::information(this, "No subjects",
                                 "Add subjects and calculate APS first.");
        return;
    }

    auto selected = careerList->selectedItems();
    if (selected.isEmpty() || selected.size() > MAX_INTERESTS) {
        QMessageBox::information(this, "Select careers",
                                 "Select between 1 and 3 career interests.");
        return;
    }

    QStringList interests;
    for (auto *item : selected) interests << item->text();

    QString recs = recommendations(interests);
    outputBox->setPlainText(breakdownAPS() + "\n" + recs);
}

/* ---------- Logic helpers ---------- */

void MainWindow::loadCoursesFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "File error",
                              "Could not open " + filePath);
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        const QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        const QStringList parts = line.split(',');
        if (parts.size() != 4) continue;

        Course c;
        c.name        = parts[0].trimmed();
        c.university  = parts[1].trimmed();
        c.requiredAPS = parts[2].trimmed().toInt();
        c.field       = parts[3].trimmed();
        courses.append(c);
    }
    file.close();
}

int MainWindow::markToAPS(int mark)
{
    if (mark >= 80) return 7;
    if (mark >= 70) return 6;
    if (mark >= 60) return 5;
    if (mark >= 50) return 4;
    if (mark >= 40) return 3;
    if (mark >= 30) return 2;
    return 1;
}

int MainWindow::totalAPS() const
{
    int total = 0;
    for (auto &s : subjects) total += markToAPS(s.mark);
    return total;
}

QString MainWindow::breakdownAPS() const
{
    QString out("Subject‑wise APS breakdown:\n");
    for (auto &s : subjects)
        out += QString("%1: %2 → APS %3\n")
               .arg(s.name).arg(s.mark).arg(markToAPS(s.mark));
    out += "\nTotal APS: " + QString::number(totalAPS()) + "\n";
    return out;
}

QString MainWindow::recommendations(const QStringList &interests) const
{
    QString out("🔍 Recommended courses based on your APS and interests:\n");
    bool found = false;

    for (const Course &c : courses) {
        if (interests.contains(c.field) && totalAPS() >= c.requiredAPS) {
            out += QString("- %1 at %2 (Required APS: %3)\n")
                   .arg(c.name).arg(c.university).arg(c.requiredAPS);
            found = true;
        }
    }

    if (!found)
        out += "❌ No matching courses found. "
               "Try selecting another field or improving your APS.\n";

    return out;
}
