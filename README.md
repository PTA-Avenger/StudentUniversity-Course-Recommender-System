# 🎓 Student/University Course Recommender System

This C++ Qt-based application helps high school students in South Africa discover suitable university courses based on their **subject marks**, **APS score**, and **career interests**.

---

## 🚀 Features

- ✅ Enter subjects and marks (validated between 0–100)
- ✅ Calculate APS (Admission Point Score) automatically
- ✅ Select up to 3 career interests (e.g., IT, Engineering, Law)
- ✅ Match courses from a database (`university_courses.txt`) based on APS + interest
- ✅ Clean, interactive Qt GUI
- ✅ Easy to extend with new fields or university courses

---

## 🛠️ Technologies Used

- **C++**
- **Qt 6+**
- VS Code or Qt Creator

---

## 📂 Project Structure

StudentUniversity-Course-Recommender-System/
├── include/ # Header files (Subject, Course, Student, etc.)
├── src/ # Logic implementation
├── main.cpp # App entry point
├── university_courses.txt# Course database (CSV format)
├── MainWindow.ui # Qt Designer UI (if used)
├── README.md
├── .gitignore
└── CMakeLists.txt


---

## 📥 How to Run

### 1. 📦 Requirements

- Qt 6.x with MSVC or MinGW installed  
- Qt Creator **OR** VS Code with C++ and Qt extensions  
- Git

### 2. 🧪 Build & Run

Option A – **Using Qt Creator**:
- Open `project.pro`
- Click **Build** → **Run**

Option B – **Using VS Code**:
- Make sure `qmake` or `CMake` is installed and in your PATH
- Open folder → Configure tasks for build/run

---

## 📁 Sample `university_courses.txt` Format

```csv
Computer Science,University of Pretoria,30,Information Technology
Civil Engineering,Wits University,35,Engineering
LLB Law,University of Cape Town,33,Law

Each line:
Course Name, University, Required APS, Career Field

| Mark (%) | APS |
| -------- | --- |
| 80–100   | 7   |
| 70–79    | 6   |
| 60–69    | 5   |
| 50–59    | 4   |
| 40–49    | 3   |
| 30–39    | 2   |
| 0–29     | 1   |

🙋‍♂️ Author
Thato Mabena
GitHub Profile »

📜 License
This project is open-source under the MIT License.


---

## ✅ How to Use It

1. Create a file named `README.md` in your project root folder.
2. Paste the content above.
3. Stage & commit it:

```bash
git add README.md
git commit -m "Add README with project overview"
git push


