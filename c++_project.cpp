#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

// ============================================================
// STUDENT CLASS
// Stores student ID, name, branch, year and contact details
// ============================================================

class Student
{
private:
    int studentID;
    string name;
    string branch;
    int year;
    string contact;

public:

    Student()
    {
        studentID = 0;
        year = 0;
    }

    Student(int id, string n, string b, int y, string c)
    {
        studentID = id;
        name = n;
        branch = b;
        year = y;
        contact = c;
    }

    // Encapsulation - Getter functions

    int getID() const
    {
        return studentID;
    }

    string getName() const
    {
        return name;
    }

    string getBranch() const
    {
        return branch;
    }

    int getYear() const
    {
        return year;
    }

    string getContact() const
    {
        return contact;
    }

    void setName(string n)
    {
        name = n;
    }

    void setBranch(string b)
    {
        branch = b;
    }

    void setYear(int y)
    {
        year = y;
    }

    void setContact(string c)
    {
        contact = c;
    }

    void display() const
    {
        cout << left
             << setw(10) << studentID
             << setw(20) << name
             << setw(15) << branch
             << setw(8) << year
             << setw(15) << contact
             << endl;
    }
};


// ============================================================
// MARKS CLASS
// Stores subject-wise marks and academic performance
// ============================================================

class Marks
{
private:
    int studentID;
    float cppMarks;
    float dsaMarks;
    float dbmsMarks;
    float mathsMarks;

public:

    Marks()
    {
        studentID = 0;
        cppMarks = dsaMarks = dbmsMarks = mathsMarks = 0;
    }

    Marks(int id, float cpp, float dsa,
          float dbms, float maths)
    {
        studentID = id;
        cppMarks = cpp;
        dsaMarks = dsa;
        dbmsMarks = dbms;
        mathsMarks = maths;
    }

    int getStudentID() const
    {
        return studentID;
    }

    float getCPP() const
    {
        return cppMarks;
    }

    float getDSA() const
    {
        return dsaMarks;
    }

    float getDBMS() const
    {
        return dbmsMarks;
    }

    float getMaths() const
    {
        return mathsMarks;
    }

    float total() const
    {
        return cppMarks + dsaMarks +
               dbmsMarks + mathsMarks;
    }

    float average() const
    {
        return total() / 4;
    }

    void updateMarks(float cpp, float dsa,
                     float dbms, float maths)
    {
        cppMarks = cpp;
        dsaMarks = dsa;
        dbmsMarks = dbms;
        mathsMarks = maths;
    }

    void display() const
    {
        cout << "\nStudent ID : " << studentID;
        cout << "\nC++        : " << cppMarks;
        cout << "\nDSA        : " << dsaMarks;
        cout << "\nDBMS       : " << dbmsMarks;
        cout << "\nMaths      : " << mathsMarks;
        cout << "\nTotal      : " << total();
        cout << "\nAverage    : " << average();
        cout << endl;
    }
};


// ============================================================
// FILE HANDLER CLASS
// Saves and retrieves student and marks records
// ============================================================

class FileHandler
{
public:

    // Save student records
    static void saveStudents(const vector<Student>& students)
    {
        ofstream file("students.txt");

        for (const Student& s : students)
        {
            file << s.getID() << "|"
                 << s.getName() << "|"
                 << s.getBranch() << "|"
                 << s.getYear() << "|"
                 << s.getContact() << endl;
        }

        file.close();
    }


    // Load student records
    static vector<Student> loadStudents()
    {
        vector<Student> students;

        ifstream file("students.txt");

        if (!file)
            return students;

        string id, name, branch, year, contact;

        while (getline(file, id, '|') &&
               getline(file, name, '|') &&
               getline(file, branch, '|') &&
               getline(file, year, '|') &&
               getline(file, contact))
        {
            students.push_back(
                Student(
                    stoi(id),
                    name,
                    branch,
                    stoi(year),
                    contact
                )
            );
        }

        file.close();

        return students;
    }


    // Save marks records
    static void saveMarks(const vector<Marks>& marks)
    {
        ofstream file("marks.txt");

        for (const Marks& m : marks)
        {
            file << m.getStudentID() << "|"
                 << m.getCPP() << "|"
                 << m.getDSA() << "|"
                 << m.getDBMS() << "|"
                 << m.getMaths() << endl;
        }

        file.close();
    }


    // Load marks records
    static vector<Marks> loadMarks()
    {
        vector<Marks> marks;

        ifstream file("marks.txt");

        if (!file)
            return marks;

        string id, cpp, dsa, dbms, maths;

        while (getline(file, id, '|') &&
               getline(file, cpp, '|') &&
               getline(file, dsa, '|') &&
               getline(file, dbms, '|') &&
               getline(file, maths))
        {
            marks.push_back(
                Marks(
                    stoi(id),
                    stof(cpp),
                    stof(dsa),
                    stof(dbms),
                    stof(maths)
                )
            );
        }

        file.close();

        return marks;
    }
};


// ============================================================
// SEARCH MANAGER
// Searches by ID, name or branch
// ============================================================

class SearchManager
{
public:

    static void searchByID(
        const vector<Student>& students,
        int id)
    {
        bool found = false;

        for (const Student& s : students)
        {
            if (s.getID() == id)
            {
                cout << "\nStudent Found:\n\n";

                cout << left
                     << setw(10) << "ID"
                     << setw(20) << "Name"
                     << setw(15) << "Branch"
                     << setw(8) << "Year"
                     << setw(15) << "Contact"
                     << endl;

                s.display();

                found = true;
            }
        }

        if (!found)
            cout << "\nStudent not found.\n";
    }


    static void searchByName(
        const vector<Student>& students,
        string name)
    {
        bool found = false;

        for (const Student& s : students)
        {
            if (s.getName() == name)
            {
                s.display();
                found = true;
            }
        }

        if (!found)
            cout << "\nStudent not found.\n";
    }


    static void searchByBranch(
        const vector<Student>& students,
        string branch)
    {
        bool found = false;

        for (const Student& s : students)
        {
            if (s.getBranch() == branch)
            {
                s.display();
                found = true;
            }
        }

        if (!found)
            cout << "\nNo students found in this branch.\n";
    }
};


// ============================================================
// REPORT CLASS
// Generates student performance summaries
// ============================================================

class Report
{
public:

    static void generateReport(
        const vector<Student>& students,
        const vector<Marks>& marks)
    {
        if (students.empty())
        {
            cout << "\nNo student records available.\n";
            return;
        }

        cout << "\n============================================\n";
        cout << "       STUDENT PERFORMANCE REPORT\n";
        cout << "============================================\n";

        for (const Student& s : students)
        {
            cout << "\nStudent ID : " << s.getID();
            cout << "\nName       : " << s.getName();
            cout << "\nBranch     : " << s.getBranch();
            cout << "\nYear       : " << s.getYear();

            bool found = false;

            for (const Marks& m : marks)
            {
                if (m.getStudentID() == s.getID())
                {
                    cout << "\nAverage    : "
                         << fixed << setprecision(2)
                         << m.average();

                    if (m.average() >= 75)
                        cout << "\nPerformance : Excellent";
                    else if (m.average() >= 60)
                        cout << "\nPerformance : Good";
                    else if (m.average() >= 40)
                        cout << "\nPerformance : Average";
                    else
                        cout << "\nPerformance : Needs Improvement";

                    found = true;
                }
            }

            if (!found)
                cout << "\nMarks       : Not Available";

            cout << "\n--------------------------------------------\n";
        }
    }
};


// ============================================================
// RECORD MANAGER
// Handles adding, updating, deleting and displaying records
// ============================================================

class RecordManager
{
private:
    vector<Student> students;
    vector<Marks> marks;

public:

    RecordManager()
    {
        students = FileHandler::loadStudents();
        marks = FileHandler::loadMarks();
    }


    // ---------------- ADD STUDENT ----------------

    void addStudent()
    {
        int id, year;
        string name, branch, contact;

        cout << "\nEnter Student ID: ";
        cin >> id;

        if (findStudent(id) != nullptr)
        {
            cout << "\nStudent ID already exists.\n";
            return;
        }

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Branch: ";
        getline(cin, branch);

        cout << "Enter Year: ";
        cin >> year;

        cin.ignore();

        cout << "Enter Contact: ";
        getline(cin, contact);

        students.push_back(
            Student(id, name, branch, year, contact)
        );

        FileHandler::saveStudents(students);

        cout << "\nStudent added successfully.\n";
    }


    // ---------------- DISPLAY STUDENTS ----------------

    void displayStudents() const
    {
        if (students.empty())
        {
            cout << "\nNo student records available.\n";
            return;
        }

        cout << "\n==========================================================\n";
        cout << "                  STUDENT RECORDS\n";
        cout << "==========================================================\n";

        cout << left
             << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(15) << "Branch"
             << setw(8) << "Year"
             << setw(15) << "Contact"
             << endl;

        cout << "----------------------------------------------------------\n";

        for (const Student& s : students)
            s.display();
    }


    // ---------------- UPDATE STUDENT ----------------

    void updateStudent()
    {
        int id;

        cout << "\nEnter Student ID to update: ";
        cin >> id;

        Student* s = findStudent(id);

        if (s == nullptr)
        {
            cout << "\nStudent not found.\n";
            return;
        }

        string name, branch, contact;
        int year;

        cin.ignore();

        cout << "Enter New Name: ";
        getline(cin, name);

        cout << "Enter New Branch: ";
        getline(cin, branch);

        cout << "Enter New Year: ";
        cin >> year;

        cin.ignore();

        cout << "Enter New Contact: ";
        getline(cin, contact);

        s->setName(name);
        s->setBranch(branch);
        s->setYear(year);
        s->setContact(contact);

        FileHandler::saveStudents(students);

        cout << "\nStudent record updated successfully.\n";
    }


    // ---------------- DELETE STUDENT ----------------

    void deleteStudent()
    {
        int id;

        cout << "\nEnter Student ID to delete: ";
        cin >> id;

        auto studentIt = remove_if(
            students.begin(),
            students.end(),
            [id](const Student& s)
            {
                return s.getID() == id;
            }
        );

        if (studentIt == students.end())
        {
            cout << "\nStudent not found.\n";
            return;
        }

        students.erase(studentIt, students.end());

        // Also delete corresponding marks
        auto marksIt = remove_if(
            marks.begin(),
            marks.end(),
            [id](const Marks& m)
            {
                return m.getStudentID() == id;
            }
        );

        marks.erase(marksIt, marks.end());

        FileHandler::saveStudents(students);
        FileHandler::saveMarks(marks);

        cout << "\nStudent deleted successfully.\n";
    }


    // ---------------- ADD / UPDATE MARKS ----------------

    void addOrUpdateMarks()
    {
        int id;

        cout << "\nEnter Student ID: ";
        cin >> id;

        if (findStudent(id) == nullptr)
        {
            cout << "\nStudent not found.\n";
            return;
        }

        float cpp, dsa, dbms, maths;

        cout << "Enter C++ Marks: ";
        cin >> cpp;

        cout << "Enter DSA Marks: ";
        cin >> dsa;

        cout << "Enter DBMS Marks: ";
        cin >> dbms;

        cout << "Enter Maths Marks: ";
        cin >> maths;

        for (Marks& m : marks)
        {
            if (m.getStudentID() == id)
            {
                m.updateMarks(cpp, dsa, dbms, maths);

                FileHandler::saveMarks(marks);

                cout << "\nMarks updated successfully.\n";
                return;
            }
        }

        marks.push_back(
            Marks(id, cpp, dsa, dbms, maths)
        );

        FileHandler::saveMarks(marks);

        cout << "\nMarks added successfully.\n";
    }


    // ---------------- DISPLAY MARKS ----------------

    void displayMarks()
    {
        int id;

        cout << "\nEnter Student ID: ";
        cin >> id;

        for (const Marks& m : marks)
        {
            if (m.getStudentID() == id)
            {
                m.display();
                return;
            }
        }

        cout << "\nMarks not available.\n";
    }


    // ---------------- SEARCH ----------------

    void searchStudent()
    {
        int choice;

        cout << "\n================================\n";
        cout << "          SEARCH MENU\n";
        cout << "================================\n";
        cout << "1. Search by ID\n";
        cout << "2. Search by Name\n";
        cout << "3. Search by Branch\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;

            cout << "Enter Student ID: ";
            cin >> id;

            SearchManager::searchByID(
                students, id
            );
        }
        else if (choice == 2)
        {
            string name;

            cin.ignore();

            cout << "Enter Student Name: ";
            getline(cin, name);

            SearchManager::searchByName(
                students, name
            );
        }
        else if (choice == 3)
        {
            string branch;

            cin.ignore();

            cout << "Enter Branch: ";
            getline(cin, branch);

            SearchManager::searchByBranch(
                students, branch
            );
        }
        else
        {
            cout << "\nInvalid choice.\n";
        }
    }


    // ---------------- REPORT ----------------

    void generateReport()
    {
        Report::generateReport(
            students, marks
        );
    }


    // ---------------- FILE SAVE ----------------

    void saveAll()
    {
        FileHandler::saveStudents(students);
        FileHandler::saveMarks(marks);
    }


private:

    Student* findStudent(int id)
    {
        for (Student& s : students)
        {
            if (s.getID() == id)
                return &s;
        }

        return nullptr;
    }
};


// ============================================================
// ABSTRACTION
// ABSTRACT USER CLASS
// ============================================================

class User
{
protected:
    string username;

public:

    User(string name)
    {
        username = name;
    }

    virtual void showMenu(RecordManager& manager) = 0;

    virtual ~User() {}
};


// ============================================================
// INHERITANCE + POLYMORPHISM
// ADMINISTRATOR
// ============================================================

class Administrator : public User
{
public:

    Administrator(string name)
        : User(name)
    {
    }

    void showMenu(RecordManager& manager) override
    {
        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "       ADMINISTRATOR MENU\n";
            cout << "============================================\n";
            cout << "1. Add Student\n";
            cout << "2. Update Student\n";
            cout << "3. Delete Student\n";
            cout << "4. Display Students\n";
            cout << "5. Search Student\n";
            cout << "6. Add / Update Marks\n";
            cout << "7. View Marks\n";
            cout << "8. Generate Report\n";
            cout << "9. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    manager.addStudent();
                    break;

                case 2:
                    manager.updateStudent();
                    break;

                case 3:
                    manager.deleteStudent();
                    break;

                case 4:
                    manager.displayStudents();
                    break;

                case 5:
                    manager.searchStudent();
                    break;

                case 6:
                    manager.addOrUpdateMarks();
                    break;

                case 7:
                    manager.displayMarks();
                    break;

                case 8:
                    manager.generateReport();
                    break;

                case 9:
                    cout << "\nAdministrator logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 9);
    }
};


// ============================================================
// FACULTY
// ============================================================

class Faculty : public User
{
public:

    Faculty(string name)
        : User(name)
    {
    }

    void showMenu(RecordManager& manager) override
    {
        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "             FACULTY MENU\n";
            cout << "============================================\n";
            cout << "1. View Students\n";
            cout << "2. Search Student\n";
            cout << "3. Add / Update Marks\n";
            cout << "4. View Marks\n";
            cout << "5. Generate Report\n";
            cout << "6. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    manager.displayStudents();
                    break;

                case 2:
                    manager.searchStudent();
                    break;

                case 3:
                    manager.addOrUpdateMarks();
                    break;

                case 4:
                    manager.displayMarks();
                    break;

                case 5:
                    manager.generateReport();
                    break;

                case 6:
                    cout << "\nFaculty logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 6);
    }
};


// ============================================================
// STUDENT USER
// ============================================================

class StudentUser : public User
{
private:
    int studentID;

public:

    StudentUser(string name, int id)
        : User(name)
    {
        studentID = id;
    }

    void showMenu(RecordManager& manager) override
    {
        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "             STUDENT MENU\n";
            cout << "============================================\n";
            cout << "1. View My Record\n";
            cout << "2. View My Marks\n";
            cout << "3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                {
                    // Search using student's own ID
                    SearchManager::searchByID(
                        FileHandler::loadStudents(),
                        studentID
                    );

                    break;
                }

                case 2:
                {
                    vector<Marks> marks =
                        FileHandler::loadMarks();

                    bool found = false;

                    for (const Marks& m : marks)
                    {
                        if (m.getStudentID() == studentID)
                        {
                            m.display();
                            found = true;
                        }
                    }

                    if (!found)
                        cout << "\nMarks not available.\n";

                    break;
                }

                case 3:
                    cout << "\nStudent logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 3);
    }
};


// ============================================================
// SYSTEM OPERATOR
// ============================================================

class SystemOperator : public User
{
public:

    SystemOperator(string name)
        : User(name)
    {
    }

    void showMenu(RecordManager& manager) override
    {
        int choice;

        do
        {
            cout << "\n============================================\n";
            cout << "         SYSTEM OPERATOR MENU\n";
            cout << "============================================\n";
            cout << "1. Display Stored Records\n";
            cout << "2. Search Records\n";
            cout << "3. Save Records\n";
            cout << "4. Generate Report\n";
            cout << "5. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
                case 1:
                    manager.displayStudents();
                    break;

                case 2:
                    manager.searchStudent();
                    break;

                case 3:
                    manager.saveAll();
                    cout << "\nRecords saved successfully.\n";
                    break;

                case 4:
                    manager.generateReport();
                    break;

                case 5:
                    cout << "\nSystem Operator logged out.\n";
                    break;

                default:
                    cout << "\nInvalid choice.\n";
            }

        } while (choice != 5);
    }
};


// ============================================================
// MAIN FUNCTION
// ============================================================

int main()
{
    RecordManager manager;

    int choice;

    cout << "\n================================================\n";
    cout << "          STUDENT RECORD MANAGER\n";
    cout << "================================================\n";

    cout << "\nSystem initialized successfully.\n";

    do
    {
        cout << "\n============================================\n";
        cout << "              USER LOGIN\n";
        cout << "============================================\n";

        cout << "1. Administrator\n";
        cout << "2. Faculty\n";
        cout << "3. Student\n";
        cout << "4. System Operator\n";
        cout << "5. Exit\n";

        cout << "\nEnter user type: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                Administrator admin("Administrator");

                // Polymorphism
                User* user = &admin;

                user->showMenu(manager);

                break;
            }

            case 2:
            {
                Faculty faculty("Faculty");

                // Polymorphism
                User* user = &faculty;

                user->showMenu(manager);

                break;
            }

            case 3:
            {
                int id;

                cout << "\nEnter your Student ID: ";
                cin >> id;

                StudentUser student(
                    "Student",
                    id
                );

                // Polymorphism
                User* user = &student;

                user->showMenu(manager);

                break;
            }

            case 4:
            {
                SystemOperator operatorUser(
                    "System Operator"
                );

                // Polymorphism
                User* user = &operatorUser;

                user->showMenu(manager);

                break;
            }

            case 5:
                cout << "\nThank you for using Student Record Manager!\n";
                break;

            default:
                cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
