#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "patient.hpp"
#include "appointment.hpp"

using namespace std;

bool verifyPassword()
{
    int tries = 0;
    char password[20], my_password[20] = "Parola123";
    int i;
    char ch;

    system("cls"); // Clear console

    cout << "PASSWORD: ";

    i = 0;

    do
    {
        ch = getch(); // Get character from console
        password[i] = ch;

        if (ch != 27 && ch != 13) // Check if the character is "Esc" or "Enter"
            putch('*');           // Display asterisk to mask the entered character
        else
            break; // If "Esc" or "Enter" is pressed exit loop
        i++;

    } while (i < 19);
    password[i] = '\0'; // Adds a null terminator to the end of the password array

    if (strcmp(password, my_password) != 0) // Checks if the user input matches the password
    {
        tries++;
        cout << "\n\nIncorrect password !!!\n";
        _getch();
        return false; // Return false if the password is incorrect
    }
    cout << "\n\nThe password is correct so the profram is exectued !";
    return true;
    _getch();
}

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
    cout << "7. Help" << endl;
    cout << "8. Exit" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice (1-8): ";
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
                help();
                break;
            case 8:

                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 8);
    }
    return 0;
}