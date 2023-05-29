#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "doctor.hpp"

using namespace std;

class Appointment
{
private:
    string patientName;
    string patientCNP;
    string doctorName;
    string date;
    string time;

public:
    // Constructor
    Appointment(string p, string pc, string d, string dt, string t)
    {
        patientName = p;
        patientCNP = pc;
        doctorName = d;
        date = dt;
        time = t;
    }

    // Getter functions for the private data members
    string getPatientName() const
    {
        return patientName;
    }

    string getPatientCNP() const
    {
        return patientCNP;
    }

    string getDoctorName() const
    {
        return doctorName;
    }

    string getDate() const
    {
        return date;
    }

    string getTime() const
    {
        return time;
    }
};

// Map to keep track of the number of appointments for each doctor
map<string, int> doctorAppointments;

// Maximum number of appointments for each doctor in a day
const int MAX_APPOINTMENTS_PER_DAY = 3;

void scheduleAppointment()
{
    string patientName, patientCNP, doctorName, date, time;

    cout << "=== Schedule an Appointment ===" << endl;

    cout << "Enter patient name: ";
    getline(cin >> ws, patientName);

    cout << "Enter patient CNP: ";
    getline(cin >> ws, patientCNP);

    // Print the names of the available doctors
    viewDoctors();

    cout << "Enter doctor name: ";
    getline(cin >> ws, doctorName);

    // Check if the doctor already has the maximum number of appointments for the day
    if (doctorAppointments[doctorName] >= MAX_APPOINTMENTS_PER_DAY)
    {
        cout << "Doctor " << doctorName << " already has the maximum number of appointments for the day." << endl;
        return;
    }

    cout << "Enter date (dd/mm/yyyy): ";
    getline(cin >> ws, date);

    cout << "Enter time (hh:mm): ";
    getline(cin >> ws, time);

    // Create instance
    Appointment appointment(patientName, patientCNP, doctorName, date, time);

    // Open the appointments file in append mode and write to it
    ofstream file("appointments.txt", ios::app);

    if (file.is_open())
    {
        file << appointment.getPatientName() << "," << appointment.getPatientCNP() << "," << appointment.getDoctorName() << "," << appointment.getDate() << "," << appointment.getTime() << endl;
        file.close();

        // Increment the number of appointments for the doctor
        doctorAppointments[doctorName]++;

        cout << "Appointment scheduled successfully." << endl;
    }
    else
    {
        cout << "Error opening file." << endl;
    }
    system("pause");
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
                // Take the string before the comma
                token = line.substr(0, pos);
                // Add the string to the list of tokens
                tokens.push_back(token);
                // Remove comma and token
                line.erase(0, pos + 1);
            }
            // Add the remaining part to the list
            tokens.push_back(line);

            if (tokens.size() == 5 && tokens[0] == patientName) // If there are four tokens (patient name, doctor name, date, and time), and the patient name matches the input, add the appointment to the vector
            {
                Appointment appointment(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
                appointments.push_back(appointment);
            }
        }

        if (appointments.size() > 0)
        {
            vector<Appointment> matchingAppointments;

            for (int i = 0; i < appointments.size(); i++)
            {
                Appointment appointment = appointments[i];
                if (appointment.getPatientName() == patientName)
                {
                    matchingAppointments.push_back(appointment);
                }
            }

            if (matchingAppointments.size() == 0)
            {
                cout << "No appointments found for patient '" << patientName << "'." << endl;
            }
            else if (matchingAppointments.size() == 1)
            {
                cout << "=== Appointment Details ===" << endl;
                cout << "Patient: " << matchingAppointments[0].getPatientName() << endl;
                cout << "Doctor: " << matchingAppointments[0].getDoctorName() << endl;
                cout << "Date: " << matchingAppointments[0].getDate() << endl;
                cout << "Time: " << matchingAppointments[0].getTime() << endl;
            }
            else
            {
                cout << "Multiple appointments found for patient '" << patientName << "'. Please enter the patient CNP:" << endl;
                string patientCNP;
                getline(cin >> ws, patientCNP);

                bool found = false;

                for (int i = 0; i < matchingAppointments.size(); i++)
                {
                    Appointment appointment = matchingAppointments[i];
                    if (appointment.getPatientCNP() == patientCNP)
                    {
                        cout << "=== Appointment Details ===" << endl;
                        cout << "Patient: " << appointment.getPatientName() << endl;
                        cout << "Doctor: " << appointment.getDoctorName() << endl;
                        cout << "Date: " << appointment.getDate() << endl;
                        cout << "Time: " << appointment.getTime() << endl;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Invalid CNP. Appointment details not found." << endl;
                }
            }
        }
        else
        {
            cout << "No appointments found for patient '" << patientName << "'." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }
    system("pause");
}
