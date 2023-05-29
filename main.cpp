#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "patient.hpp"
#include "appointment.hpp"
#include "password.hpp"
#include "doctor.hpp"

using namespace std;

void displayMenu()
{
    system("cls");

    cout << "=== Hospital Management System ===" << endl;
    cout << "1. Register a new patient" << endl;
    cout << "2. Search for a patient" << endl;
    cout << "3. View patient records" << endl;
    cout << "4. Schedule an appointment" << endl;
    cout << "5. View appointments" << endl;
    cout << "6. Edit patient records" << endl;
    cout << "7. Delete patient records" << endl;
    cout << "8. Generate statistics" << endl;
    cout << "9. Change password" << endl;
    cout << "10. View doctors" << endl;
    cout << "11. Help" << endl;
    cout << "12. Exit" << endl;
    // cout << "13. Exit" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice (1-12): ";
}

void help()
{
    cout << "=== Help ===" << endl;
    cout << "This program is a simple hospital management system." << endl;
    cout << "It allows you to add, view patient records, as well as schedule and view appointments." << endl;
    cout << "To use the program, select one of the 12 possible options." << endl;
    _getch(); // Await press of a key
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
                editPatientDetails();
                break;
            case 7:
                deletePatient();
                break;
            case 8:
                generateStatistics();
                break;
            case 9:
                changePassword();
                break;
            case 10:
                viewDoctors();
                break;
            case 11:
                help();
                break;
            case 12:
                exit(0);
                break;
            case 13:
                // doctorPatients();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 13);
    }
    return 0;
}