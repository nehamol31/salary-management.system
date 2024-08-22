#include <iostream.h>
#include <fstream.h>
#include <conio.h>

class Employee {
public:
    char name[50];
    int employeeId;
    float salary;
    char email[50];
    char departmentName[50];
    char jobName[50];
    int age;
    float hra;
    float ta;
    float taxes;
    float bonus;
    float pension;

    void input() {
    clrscr();
    cout << "Enter employee name: \n";
    cin >> name;
    cout << "Enter employee ID: \n";
    cin >> employeeId;
    cout << "Enter employee salary: \n";
    cin >> salary;
    cout << "Enter employee email: \n";
    cin >> email;
    cout << "Enter employee department name: \n";
    cin >> departmentName;
    cout << "Enter employee job name: \n";
    cin >> jobName;

    
    cout << "Enter employee age: \n";
    cin >> age;

    if (age >= 50) {
        pension = 0.03 * salary;
    } else if (age >= 60) {
        pension = 0.05 * salary;
    } else {
        pension = 0.08 * salary;
    }

    hra = 0.1 * salary;
    ta = 0.05 * salary;
    taxes = 0.2 * salary;
    bonus = 0.1 * salary;
}


    void display() {
        cout << "Employee ID: " << employeeId
             << "\nName: " << name
             << "\nSalary: Rs." << salary
             << "\nEmail: " << email
             << "\nDepartment: " << departmentName
             << "\nJob: " << jobName
             << "\nAge: " << age
             << "\nHRA: Rs." << hra
             << "\nTA: Rs." << ta
             << "\nTaxes: Rs." << taxes
             << "\nBonus: Rs." << bonus
             << "\nPension: Rs." << pension
             << "\nNet Salary: Rs." << (salary - taxes + hra + ta + bonus - pension)
             << endl;
    }
};

void addEmployee(Employee emp[], int &count) {
    emp[count].input();
    count++;
    cout << "Employee added successfully!\n";
    getch();
}

void displayAllEmployees(Employee emp[], int count) {
    clrscr();
    cout << "Employee Details:\n";
    for (int i = 0; i < count; i++) {
        cout << "Serial Number: " << i + 1 << endl;
        emp[i].display();
        cout << endl;
    }
    getch();
}

int searchEmployee(Employee emp[], int count, int empIdToSearch) {
    for (int i = 0; i < count; i++) {
        if (emp[i].employeeId == empIdToSearch) {
            return i;
        }
    }
    return -1;
}

void deleteEmployee(Employee emp[], int &count, int empIdToDelete) {
    for (int i = 0; i < count; i++) {
        if (emp[i].employeeId == empIdToDelete) {
            for (int j = i; j < count - 1; j++) {
                emp[j] = emp[j + 1];
            }
            count--;
            cout << "Employee with ID " << empIdToDelete << " deleted successfully.\n";
            getch();
            return;
        }
    }
    cout << "Employee with ID " << empIdToDelete << " not found.\n";
    getch();
}

void updateEmployeeSalary(Employee emp[], int count, int empIdToUpdate) {
    int index = searchEmployee(emp, count, empIdToUpdate);
    if (index != -1) {
        cout << "Enter new salary for employee with ID " << empIdToUpdate << ": Rs";
        cin >> emp[index].salary;
        cout << "Salary updated successfully!\n";
    } else {
        cout << "Employee not found.\n";
    }
    getch();
}

void saveToFile(Employee emp[], int count, const char *BIN) {
    ofstream outFile(BIN);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        outFile << emp[i].employeeId << ' ' << emp[i].name << ' ' << emp[i].salary << ' '
                << emp[i].email << ' ' << emp[i].departmentName << ' ' << emp[i].jobName << ' '<< emp[i].age << ' '
                << emp[i].hra << ' ' << emp[i].ta << ' ' << emp[i].taxes << ' ' << emp[i].bonus << endl;
    }

    cout << "Data saved to file successfully.\n";
    outFile.close();
    getch();
}

void loadFromFile(Employee emp[], int &count, const char *BIN) {
    ifstream inFile(BIN);
    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }

    count = 0;
    while (inFile >> emp[count].employeeId >> emp[count].name >> emp[count].salary
           >> emp[count].email >> emp[count].departmentName >> emp[count].jobName
           >> emp[count].age >> emp[count].hra >> emp[count].ta >> emp[count].taxes >> emp[count].bonus) {
        count++;
    }

    cout << "Data loaded from file successfully.\n";
    inFile.close();
    getch();
}

int main() {
    Employee employees[50];
    int employeeCount = 0;
    int choice;
    const char BIN[] = "SMS.txt";

    loadFromFile(employees, employeeCount, BIN);

    do {
        clrscr();
        cout << "------------------------------";
        cout << "\nSalary Management System\n";
        cout << "------------------------------\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Delete Employee\n";
        cout << "5. Update Employee Salary\n";
        cout << "6. Exit\n";
        cout << "------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(employees, employeeCount);
                break;
            case 2:
                displayAllEmployees(employees, employeeCount);
                break;
            case 3: {
                int empIdToSearch;
                cout << "Enter the employee ID to search: ";
                cin >> empIdToSearch;
                int searchResult = searchEmployee(employees, employeeCount, empIdToSearch);
                if (searchResult != -1) {
                    cout << "Employee found:\n";
                    employees[searchResult].display();
                } else {
                    cout << "Employee with ID " << empIdToSearch << " not found.\n";
                }
                getch();
                break;
            }
            case 4: {
                int empIdToDelete;
                cout << "Enter the employee ID to delete: ";
                cin >> empIdToDelete;
                deleteEmployee(employees, employeeCount, empIdToDelete);
                break;
            }
            case 5: {
                int empIdToUpdate;
                cout << "Enter the employee ID to update salary: ";
                cin >> empIdToUpdate;
                updateEmployeeSalary(employees, employeeCount, empIdToUpdate);
                break;
            }
            case 6:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                getch();
        }

    } while (choice != 6);

    saveToFile(employees, employeeCount, BIN);

    return 0;
}
