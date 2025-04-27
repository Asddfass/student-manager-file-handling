#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
using namespace std;
// STUDENT STRUCT
struct Student 
{
    string name = "";
    string studentId = "";
    string course = "";
    int yearLevel = 0;
    float finalGrade = 0.0;
};

// STRUCT TO MANAGE EVERYTHING FROM FUNCTIONS TO ARRAYS
struct Manager
{
    Student students[100];
    int count = 0;
    // CONSTRUCTOR TO CREATE FILE IF IT DOES NOT EXIST YET
    Manager()
    {
        ofstream file("students.txt", ios::app);
        if (file.is_open())
        {
            file.close();
        }
        else
        {
            cout << "Error Opening File!!!" << '\n';
        }
    }
    //CHECKS FILE IF IT HAS DATA AND STORE IT IN THE ARRAY WHEN THE PROGRAM STARTS
    void checkFile()
    {
        ifstream file("students.txt", ios::in);
        if (file.is_open()) 
        {
            while (file >> this->students[count].name >> this->students[count].studentId >> this->students[count].course >> this->students[count].yearLevel >> this->students[count].finalGrade)
            {
                for (int i = 0; i < this->students[count].name.length(); ++i)
                {
                    if (this->students[count].name[i] == '_')
                    {
                        this->students[count].name[i] = ' ';
                    }
                }
                for (int i = 0; i < this->students[count].course.length(); ++i)
                {
                    if (this->students[count].course[i] == '_')
                    {
                        this->students[count].course[i] = ' ';
                    }
                }
                this->count++;
            }
        }
        else
        {
            cout << "Error Opening File!!!" << '\n';
        }
    }
    // OPTION 1 ADD STUDENT
    void addStudent()
    {
        cout << "\n\t-ADD STUDENT-" << "\n\n";

        cout << "Enter STUDENT Name: ";
        string name = "";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter STUDENT ID: ";
        string studentId;
        // CHECKS IF STUDENT ID ENTERED ALREADY EXIST IT WILL REPEAT ASK TO ENTER A NEW ID
        while (true)
        {
            cin >> studentId;
            if (checkID(studentId))
            {
                cout << "Enter a different ID: ";
            }
            else
            {
                break;
            }
        }
        
        cout << "Enter Student Course: ";
        string course = "";
        cin.ignore();
        getline(cin, course);
        
        cout << "Enter Student Year Level: ";
        int yearLevel = 0;
        cin >> yearLevel;

        cout << "Enter Student Final Grade: ";
        float finalGrade = 0.0;
        cin >> finalGrade;

        this->students[this->count].name = name;
        this->students[this->count].studentId = studentId;
        this->students[this->count].course = course;
        this->students[this->count].yearLevel = yearLevel;
        this->students[this->count].finalGrade = finalGrade;

        for (int i = 0; i < name.length(); ++i)
        {
            if (name[i] == ' ')
            {
                name[i] = '_';
            }
        }
        for (int i = 0; i < course.length(); ++i)
        {
            if (course[i] == ' ')
            {
                course[i] = '_';
            }
        }

        ofstream file("students.txt", ios::app);
        if (file.is_open())
        {
            file << name << ' ' << studentId << ' ' << course << ' ' << yearLevel << ' ' << finalGrade << '\n';
            this->count++;
            cout << "Student Successfully Added!!!" << '\n';
            file.close();
        }
        else
        {
            cout << "Error Opening File!!!" << '\n';
        }
        getchPrompt();
    }
    //OPTION 2 VIEW STUDENTS
    void viewAllStudents()
    {
        cout << "\n\t-VIEW STUDENT-" << "\n\n";
        if (this->count == 0)
        {
            cout << "STUDENT RECORD IS EMPTY!!!" << '\n';
            getchPrompt();
            return;
        }
        cout << "=======================================" << '\n';
        for (int i = 0; i < this->count; ++i)
        {
            cout << "Student #" << i + 1 << '\n';
            cout << "Name: " << this->students[i].name << '\n';
            cout << "Student ID: " << this->students[i].studentId << '\n';
            cout << "Course: " << this->students[i].course << '\n';
            cout << "Year Level: " << this->students[i].yearLevel << '\n';
            cout << "Final Grade: " << this->students[i].finalGrade << '\n';
            cout << "=======================================" << '\n';
        }
        getchPrompt();
    }
    // OPTION 3 SEARCH STUDENT
    void searchStudent()
    {
        cout << "\n\t-SEARCH STUDENT-" << "\n\n";
        if (this->count == 0)
        {
            std::cout << "STUDENT RECORD IS EMPTY!!!" << '\n';
            getchPrompt();
            return;
        }
        string studentId = "";
        cout << "ENTER STUDENT ID: ";
        cin >> studentId;
        bool found = false;
        int counter = 0;

        for (int i = 0; i < this->count; ++i)
        {
            if (this->students[i].studentId == studentId)
            {
                found = true;
                break;
            }
            counter++;
        }

        if (found)
        {
            cout << "=======================================" << '\n';
            cout << "Student #" << counter + 1 << '\n';
            cout << "Name: " << students[counter].name << '\n';
            cout << "Student ID: " << students[counter].studentId << '\n';
            cout << "Course: " << students[counter].course << '\n';
            cout << "Year Level: " << students[counter].yearLevel << '\n';
            cout << "Final Grade: " << students[counter].finalGrade << '\n';
            cout << "=======================================" << '\n';
        }
        else
        {
            cout << "ID: " << studentId << " does not exist!!!" << '\n';
        }
        getchPrompt();
    }
    // OPTION 4 UPDATE STUDENT
    void updateStudent()
    {
        cout << "\n\t-UPDATE STUDENT-" << "\n\n";
        if (this->count == 0)
        {
            cout << "STUDENT RECORD IS EMPTY!!!" << '\n';
            getchPrompt();
            return;
        }

        string studentId = "";
        cout << "ENTER STUDENT ID: ";
        cin >> studentId;
        cin.ignore();
        
        bool found = false;
        int i = 0;
        for (; i < this->count; ++i)
        {
            if (this->students[i].studentId == studentId)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << "ID: " << studentId << " does not exist!!!" << '\n';
            getchPrompt();
            return;
        }

        bool running = true;
        char opt = ' ';
        // TO MAKE A COPY FOR WHEN UPDATING A STUDENT
        string newName = this->students[i].name;
        string newStudentId = this->students[i].studentId;
        string newCourse = this->students[i].course;
        int newYearLevel = this->students[i].yearLevel;
        float newFinalGrade = this->students[i].finalGrade;
        bool updateOng = false;
        Student temp = this->students[i];

        while (running)
        {
            system("cls");
            displayUpdateStudent(i, updateOng, temp);
            displayUpdateMenu();
            std::cin >> opt;
            std::cin.ignore();

            switch (opt)
            {
            case '1':
            {
                system("cls");
                newName = updateName();
                temp.name = newName;
                updateOng = true;
                getch();
                break;
            }
            case '2':
            {
                system("cls");
                newStudentId = updateId();
                temp.studentId = newStudentId;
                updateOng = true;
                getch();
                break;
            }
            case '3':
            {
                system("cls");
                newCourse = updateCourse();
                temp.course = newCourse;
                updateOng = true;
                getch();
                break;
            }
            case '4':
            {
                system("cls");
                newYearLevel = updateYearLevel();
                temp.yearLevel = newYearLevel;
                updateOng = true;
                getch();
                break;
            }
            case '5':
            {
                system("cls");
                newFinalGrade = updateFinalGrade();
                temp.finalGrade = newFinalGrade;
                updateOng = true;
                getch();
                break;
            }
            case '6':
            {
                std::cout << "Exiting without updating..." << '\n';
                running = false;
                break;
            }
            case '7':
            {
                updateStudentRecord(newName, newStudentId, newCourse, newYearLevel, newFinalGrade, i);
                running = false;
                break;
            }
            default:
            {
                std::cout << "Invalid Input!!!" << '\n';
                break;
            }
            }
        }
        getchPrompt();
    }
    // OPTION 5 DELETE STUDENT
    void deleteStudent()
    {
        cout << "\n\t-DELETE STUDENT-" << "\n\n";
        // CHECKER IF RECORD IS EMPTY FUNCTION WILL RETURN NOTHING
        if (this->count == 0)
        {
            std::cout << "STUDENT RECORD IS EMPTY!!!" << '\n';
            getchPrompt();
            return;
        }
        cout << "Enter ID to delete: ";
        string studentId = "";
        cin >> studentId;
        bool found = false;
        int counter = 0;
        // FOR FINDING IF EMPLOYEE ID ENTERED EXIST
        for (int i = 0; i < this->count; ++i)
        {
            if (this->students[i].studentId == studentId)
            {
                found = true;
                break;
            }
            counter++;
        }
        if (found)
        {
            cout << "\n";
            cout << "=======================================" << '\n';
            cout << "Name: " << this->students[counter].name << '\n';
            cout << "ID: " << this->students[counter].studentId << '\n';
            cout << "Course: " << this->students[counter].course << '\n';
            cout << "Year Level: " << this->students[counter].yearLevel << '\n';
            cout << "Final Grade: " << this->students[counter].finalGrade << '\n';
            cout << "=======================================" << '\n';
            cout << "Enter (y/n) to delete or cancel: ";
            while (true)
            {
                char opt = ' ';
                cin >> opt;
                cin.ignore();
                if (tolower(opt) == 'y')
                {
                    for (int i = counter; i < this->count; ++i)
                    {
                        this->students[i] = this->students[i + 1];
                    }
                    // MAKES THE DELETED STUDENT TO DEFAULT AND REDUCES THE STUDENT COUNT BY 1
                    this->students[this->count] = Student();
                    this->count--;

                    ofstream file("students.txt", ios::out);
                    if (file.is_open())
                    {
                        for (int i = 0; i < this->count; ++i)
                        {
                            // THIS IS FOR SPACES TO SAVE IT AS "_" IN THE FILE
                            for (int i = 0; i < this->students[i].name.length(); ++i)
                            {
                                if (students[i].name[i] == ' ')
                                {
                                    students[i].name[i] = '_';
                                }
                            }
                            for (int i = 0; i < this->students[i].course.length(); ++i)
                            {
                                if (students[i].course[i] == ' ')
                                {
                                    students[i].course[i] = '_';
                                }
                            }
            
                            file << this->students[i].name << ' ' << this->students[i].studentId << ' ' << this->students[i].course << ' ' << this->students[i].yearLevel << ' ' << this->students[i].finalGrade << '\n';
                            // THIS TO UNDO THE "_" FOR THE ARRAY
                            for (int i = 0; i < this->students[i].name.length(); ++i)
                            {
                                if (this->students[i].name[i] == '_')
                                {
                                    this->students[i].name[i] = ' ';
                                }
                            }
                            for (int i = 0; i < students[i].course.length(); ++i)
                            {
                                if (this->students[i].course[i] == '_')
                                {
                                    this->students[i].course[i] = ' ';
                                }
                            }
                        }
                        file.close();
                        cout << "Student Successfully Deleted!!!" << '\n';
                    }
                    else
                    {
                        cout << "Error Opening File!!!" << '\n';
                    }

                    getchPrompt();
                    break;
                }
                else if (tolower(opt) == 'n')
                {
                    cout << "Student Deletion Canceled!!!" << '\n';
                    getchPrompt();
                    break;
                }
                else
                {
                    cout << "Invalid Input!!!" << '\n';
                    cout << "Try again. (y/n):";
                }
            }
        }
        else if (!found)
        {
            cout << "ID: " << studentId << " does not exist!!!" << '\n';
            getchPrompt();
        }
    }

    bool checkID(string studentId)
    {
        for (int i = 0; i < this->count; ++i)
        {
            if (this->students[i].studentId == studentId)
            {
                cout << "STUDENT ID ALREADY EXIST!!!" << '\n';
                return true;
            }
        }
        return false;
    }

    void displayUpdateStudent(int i, bool updateOng, Student temp)
    {
        cout << "\n\t-UPDATE STUDENT-" << "\n\n";

        cout << "==============-ORIGINAL-==============" << '\n';
        cout << "Name: " << this->students[i].name << '\n';
        cout << "Student ID: " << this->students[i].studentId << '\n';
        cout << "Course: " << this->students[i].course << '\n';
        cout << "Year Level: " << this->students[i].yearLevel << '\n';
        cout << "Final Grade: " << this->students[i].finalGrade << '\n';
        cout << "======================================" << '\n';

        if (updateOng)
        {
            cout << "===============-UPDATE-===============" << '\n';
            cout << "Name: " << temp.name << '\n';
            cout << "Student ID: " << temp.studentId << '\n';
            cout << "Course: " << temp.course << '\n';
            cout << "Year Level: " << temp.yearLevel << '\n';
            cout << "Final Grade: " << temp.finalGrade << '\n';
            cout << "======================================" << '\n';
        }
    }

    string updateName()
    {
        cout << "Enter new Name: ";
        string name = "";
        getline(cin, name);
        getchUpdatePrompt();
        return name;
    }

    string updateId()
    {
        cout << "Enter new ID: ";
        string studentId = "";
        while (true)
        {
            cin >> studentId;
            if (checkID(studentId))
            {
                cout << "Enter a different ID: ";
            }
            else
            {
                break;
            }
        }
        getchUpdatePrompt();
        return studentId;
    }

    string updateCourse()
    {
        cout << "Enter new Course: ";
        string course = "";
        getline(cin, course);
        getchUpdatePrompt();
        return course;
    }

    int updateYearLevel()
    {
        cout << "Enter new Year Level: ";
        int yearLevel = 0;
        cin >> yearLevel;
        getchUpdatePrompt();
        return yearLevel;
    }

    float updateFinalGrade()
    {
        cout << "Enter new Final Grade: ";
        float finalGrade = 0.0;
        cin >> finalGrade;
        getchUpdatePrompt();
        return finalGrade;
    }
    // FUNCTION WHEN EXIT & SAVE UPDATE OPTION IS CHOSEN
    void updateStudentRecord(string name, string studentId, string course, int yearLevel, float finalGrade, int i)
    {
        this->students[i].name = name;
        this->students[i].studentId = studentId;
        this->students[i].course = course;
        this->students[i].yearLevel = yearLevel;
        this->students[i].finalGrade = finalGrade;

        ofstream file("students.txt", ios::out);
        if (file.is_open())
        {
            for (int i = 0; i < this->count; ++i)
            {
                // THIS IS FOR SPACES TO SAVE IT AS "_" IN THE FILE
                for (int j = 0; j < this->students[i].name.length(); ++j)
                {
                    if (this->students[i].name[j] == ' ')
                    {
                        this->students[i].name[j] = '_';
                    }
                }
                for (int j = 0; j < this->students[i].course.length(); ++j)
                {
                    if (this->students[i].course[j] == ' ')
                    {
                        this->students[i].course[j] = '_';
                    }
                }

                file << this->students[i].name << ' ' << this->students[i].studentId << ' ' << this->students[i].course << ' ' << this->students[i].yearLevel << ' ' << this->students[i].finalGrade << '\n';
                // THIS TO UNDO THE "_" FOR THE ARRAY
                for (int j = 0; j < this->students[i].name.length(); ++j)
                {
                    if (this->students[i].name[j] == '_')
                    {
                        this->students[i].name[j] = ' ';
                    }
                }
                for (int j = 0; j < this->students[i].course.length(); ++j)
                {
                    if (this->students[i].course[j] == '_')
                    {
                        this->students[i].course[j] = ' ';
                    }
                }
            }
            cout << "Student Successfully Updated!!!" << '\n';
            file.close();
        }
        else
        {
            cout << "Error Opening File!!!" << '\n';
        }
    }
    // UPDATE MENU OPTION FOR WHEN UPDATING A STUDENT RECORD
    void displayUpdateMenu()
    {
        cout << "\n\t-UPDATE MENU-" << "\n\n";
        cout << "1. UPDATE NAME" << '\n';
        cout << "2. UPDATE ID" << '\n';
        cout << "3. UPDATE COURSE" << '\n';
        cout << "4. UPDATE YEAR LEVEL" << '\n';
        cout << "5. UPDATE FINAL GRADE" << '\n';
        cout << "6. EXIT WITHOUT SAVE" << '\n';
        cout << "7. EXIT & SAVE" << '\n';
        cout << "Enter Option: ";
    }

    // GETCH PROMPT AFTER EVERTY OPTION
    void getchUpdatePrompt()
    {
        cout << '\n' << "press any button to continue back to update menu..." << '\n';
    }
    void getchPrompt()
    {
        cout << '\n' << "press any button to continue back to main menu..." << '\n';
    }
};
// MENU PROMPT FUNCTION
void drawMenu()
{
    cout << "\n\tSTUDENT RECORD MANAGER" << '\n';
    cout << "1. Add a Student Record" << '\n';
    cout << "2. View All Records" << '\n';
    cout << "3. Search Student by ID" << '\n';
    cout << "4. Update a Record" << '\n';
    cout << "5. Delete a Record" << '\n';
    cout << "6. Exit" << '\n';
    cout << "Enter Option: ";
}
// FUNCTION TO RUN EVERYTHING
void run()
{
    Manager manager;
    manager.checkFile();

    bool running = true;
    while (running)
    {
        system("cls");
        drawMenu();
        char opt = ' ';
        cin >> opt;
        switch (opt)
        {
        case '1':
        {
            system("cls");
            manager.addStudent();
            getch();
            break;
        }
        case '2':
        {
            system("cls");
            manager.viewAllStudents();
            getch();
            break;
        }
        case '3':
        {
            system("cls");
            manager.searchStudent();
            getch();
            break;
        }
        case '4':
        {
            system("cls");
            manager.updateStudent();
            getch();
            break;
        }
        case '5':
        {
            system("cls");
            manager.deleteStudent();
            getch();
            break;
        }
        case '6':
        {
            cout << "\n\nPress any button to exit... :)";
            running = false;
            getch();
            break;
        }
        default:
        {
            cout << "\n\nINVALID INPUT!!!" << '\n';
            cout << "Press any button to try again...";
            getch();
            break;
        }
        }
    }
}

int main()
{
    run();
    return 0;
}