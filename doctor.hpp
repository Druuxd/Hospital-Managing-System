#pragma once

#include "appointment.hpp"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "patient.hpp"

using namespace std;

class Doctor
{
private:
    string name;
    string specialization;
    string patients;
    string program;

public:
    // Constructor
    Doctor(string n, string spec, string pat, string pr)
    {
        name = n;
        specialization = spec;
        patients = pat;
        program = pr;
    }
    // Getter functions for private data members
    string getName()
    {
        return name;
    }

    string getSpecialization()
    {
        return specialization;
    }
    string getProgram()
    {
        return program;
    }
};

void viewDoctors()
{
    // Open file patients for reading data
    ifstream file("doctors.txt");
    if (file.is_open())
    {
        vector<Doctor> doctors; // Create a vector to store the patients
        string line;

        // Same as viewAppointment()
        while (getline(file, line))
        {
            size_t pos = 0;
            string token;
            vector<string> tokens;

            while ((pos = line.find(",")) != string::npos)
            {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }

            tokens.push_back(line);

            if (tokens.size() == 4)
            {
                Doctor patient(tokens[0], tokens[1], tokens[2], tokens[3]);
                doctors.push_back(patient);
            }
        }

        // If there are one or more patients, display their data.
        if (doctors.size() > 0)
        {
            cout << "=== Patient Records ===" << endl;
            for (int i = 0; i < doctors.size(); i++)
            {
                Doctor doctor = doctors[i];
                cout << "Name: " << doctor.getName() << endl;
                cout << "Specialization: " << doctor.getSpecialization() << endl;
                cout << "Program: " << doctor.getProgram() << endl;
                cout << endl;
            }
        }
        else
        {
            cout << "No patient records found." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }
    _getch();
}
