#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

bool verifyPassword()
{
    int tries = 0;
    int maxTries = 3;
    char password[20], my_password[20] = "Parola123";
    int i;
    char ch;

    system("cls"); // Clear console

    do
    {
        cout << "PASSWORD (tries left: " << maxTries - tries << "): ";
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

        // Open password file and read the stored password
        ifstream file("password.txt");
        if (!file.is_open())
        {
            cerr << "Error opening password file." << endl;
            return false;
        }

        string storedPassword;
        getline(file, storedPassword);

        file.close();

        if (strcmp(password, storedPassword.c_str()) != 0) // Checks if the user input matches the password
        {
            tries++;
            cout << "\n\nIncorrect password !!!\n";
            _getch();
            system("cls"); // Clear console
        }
        else
        {
            cout << "\n\nThe password is correct so the program is executed!";
            _getch();
            return true;
        }
    } while (tries < maxTries);

    cout << "\n\nToo many incorrect attempts. The program will now close.\n";
    _getch();
    system("cls");
    exit(0);
}

void changePassword()
{
    char currentPassword[20], newPassword[20], confirmPassword[20];
    int i;
    char ch;

    system("cls"); // Clear console

    cout << "CHANGE PASSWORD" << endl;

    // Get current password
    cout << "Enter your current password: ";
    i = 0;
    do
    {
        ch = getch(); // Get character from console
        currentPassword[i] = ch;

        if (ch != 27 && ch != 13) // Check if the character is "Esc" or "Enter"
            putch('*');           // Display asterisk to mask the entered character
        else
            break; // If "Esc" or "Enter" is pressed exit loop
        i++;

    } while (i < 19);
    currentPassword[i] = '\0'; // Adds a null terminator to the end of the currentPassword array

    // Open password file and read the stored password
    ifstream file("password.txt");
    if (!file.is_open())
    {
        cerr << "Error opening password file." << endl;
        _getch();
        return;
    }

    string storedPassword;
    getline(file, storedPassword);

    file.close();

    if (strcmp(currentPassword, storedPassword.c_str()) != 0) // Checks if the user input matches the current password
    {
        cout << "\n\nIncorrect password !!!\n";
        _getch();
        return;
    }

    // Get new password
    cout << "\n\nEnter your new password: ";
    i = 0;
    do
    {
        ch = getch(); // Get character from console
        newPassword[i] = ch;

        if (ch != 27 && ch != 13) // Check if the character is "Esc" or "Enter"
            putch('*');           // Display asterisk to mask the entered character
        else
            break; // If "Esc" or "Enter" is pressed exit loop
        i++;

    } while (i < 19);
    newPassword[i] = '\0'; // Adds a null terminator to the end of the newPassword array

    // Confirm new password
    cout << "\n\nConfirm your new password: ";
    i = 0;
    do
    {
        ch = getch(); // Get character from console
        confirmPassword[i] = ch;

        if (ch != 27 && ch != 13) // Check if the character is "Esc" or "Enter"
            putch('*');           // Display asterisk to mask the entered character
        else
            break; // If "Esc" or "Enter" is pressed exit loop
        i++;

    } while (i < 19);
    confirmPassword[i] = '\0'; // Adds a null terminator to the end of the confirmPassword array

    if (strcmp(newPassword, confirmPassword) != 0) // Check if the new password matches the confirmed password
    {
        cout << "\n\nThe new password and the confirmed password do not match.\n";
        _getch();
        return;
    }

    // Write the new password to the file
    ofstream passwordFile("password.txt");
    if (!passwordFile.is_open())
    {
        cerr << "Error opening password file." << endl;
        _getch();
        return;
    }
    passwordFile << newPassword;
    passwordFile.close();

    cout << "\n\nPassword successfully changed!\n";
    _getch();
}