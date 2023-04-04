#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "patient.hpp"
#include "appointment.hpp"
#include "password.hpp"

using namespace std;

void displayMenu()
{
    system("cls");

    cout << "=== Hospital Management System ===" << endl;
    cout << "1. Register a new patient" << endl;
    cout << "2. Search for a patient" << endl;
    cout << "3. View patient records" << endl;
    cout << "4. Schedule an appointment" << endl;
    cout << "5. Edit patient records" << endl;
    cout << "6. Generate statistics" << endl;
    cout << "7. Change password" << endl;
    cout << "8. Help" << endl;
    cout << "9. Exit" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice (1-9): ";
}

void help()
{
    cout << "=== Help ===" << endl;
    cout << "This program is a simple hospital management system." << endl;
    cout << "It allows you to add, view patient records, as well as schedule and view appointments." << endl;
    cout << "To use the program, select one of the 8 possible options." << endl;
    _getch(); // Awat press of a key
}

int main()
{
    if (verifyPassword() == 1)
    {

        int choice;

        do
        {
            displayMenu();
            cin >> choice;

            switch (choice)
            {
            case 1:
                registerPatient();
                break;
            case 2:
                searchPatient();
                break;
            case 3:
                viewPatientRecords();
                break;
            case 4:
                scheduleAppointment();
                break;
            case 5:
                viewAppointment();
                break;
            case 6:
                generateStatistics();
                break;
            case 7:
                changePassword();
                break;
            case 8:
                help();
                break;
            case 9:
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 8);
    }
    return 0;
}