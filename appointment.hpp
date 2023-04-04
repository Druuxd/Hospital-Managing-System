#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;

class Appointment
{
private:
    string patientName;
    string doctorName;
    string date;
    string time;

public:
    // Constructor
    Appointment(string p, string d, string dt, string t)
    {
        patientName = p;
        doctorName = d;
        date = dt;
        time = t;
    }

    // Getter functions for the private data memebers
    string getPatientName()
    {
        return patientName;
    }

    string getDoctorName()
    {
        return doctorName;
    }

    string getDate()
    {
        return date;
    }

    string getTime()
    {
        return time;
    }
};

// This function allows the user to schedule an appointment by entering patient name, doctor name, date, and time
void scheduleAppointment()
{
    string patientName, doctorName, date, time;

    cout << "=== Schedule an Appointment ===" << endl;

    cout << "Enter patient name: ";
    getline(cin >> ws, patientName); // Get a line of input with whitespace characters.

    cout << "Enter doctor name: ";
    getline(cin >> ws, doctorName);

    cout << "Enter date (dd/mm/yyyy): ";
    getline(cin >> ws, date);

    cout << "Enter time (hh:mm): ";
    getline(cin >> ws, time);

    // Create instance
    Appointment appointment(patientName, doctorName, date, time);

    // Open the appointments file in append mode and write in it.
    ofstream file("appointments.txt", ios::app);

    if (file.is_open())
    {
        file << appointment.getPatientName() << ", " << appointment.getDoctorName() << ", " << appointment.getDate() << ", " << appointment.getTime() << endl; // Write the data
        file.close();

        cout << "Appointment scheduled successfully." << endl;
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}

// This function allows the user to view appointments for a given patient name.
void viewAppointment()
{
    // Open the appointments file for reading
    ifstream file("appointments.txt");
    if (file.is_open())
    {
        vector<Appointment> appointments; // Create a vector to store the appointments
        string line;

        cout << "Enter patient name: ";
        string patientName;
        getline(cin >> ws, patientName);

        while (getline(file, line)) // Read each line of the file and extract the data
        {
            size_t pos = 0;
            string token;
            vector<string> tokens;

            while ((pos = line.find(",")) != string::npos) // Search for commas in the line
            {
                // Take the token before the comma
                token = line.substr(0, pos);
                // Add token to the list of tokens
                tokens.push_back(token);
                // Remove comma and token
                line.erase(0, pos + 1);
            }
            // Add the remaning part to the list
            tokens.push_back(line);

            if (tokens.size() == 4 && tokens[0] == patientName) // If there are four tokens (patient name, doctor name, date, and time), and the patient name matches the input, add the appointment to the vector
            {
                Appointment appointment(tokens[0], tokens[1], tokens[2], tokens[3]);
                appointments.push_back(appointment);
            }
        }

        // If there exist any appointments for the given patient, display them
        if (appointments.size() > 0)
        {
            cout << "=== Appointments for " << patientName << " ===" << endl;
            for (int i = 0; i < appointments.size(); i++)
            {
                Appointment appointment = appointments[i];
                cout << "Patient: " << appointment.getPatientName() << ", Doctor: " << appointment.getDoctorName() << ", Date: " << appointment.getDate() << ", Time: " << appointment.getTime() << endl;
            }
            _getch();
        }
        else
        {
            cout << "No appointments found for " << patientName << "." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}
