#pragma once

#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

class Patient
{
private:
    string name;
    string gender;
    string adress;
    string phone;
    int age;

public:
    // Constructor
    Patient(string n, int a, string g, string ad, string p)
    {
        name = n;
        gender = g;
        adress = ad;
        phone = p;
        age = a;
    }
    // Getter functions for private data members
    string getName()
    {
        return name;
    }

    string getGender()
    {
        return gender;
    }

    string getAdress()
    {
        return adress;
    }

    string getPhone()
    {
        return phone;
    }

    int getAge()
    {
        return age;
    }

    // Function that saves data in the patients file
    void saveToFile()
    {
        // Open the appointments file in append mode and write in it.
        ofstream file("patients.txt", ios::app);
        if (file.is_open())
        {
            file << name << ", " << age << ", " << gender << ", " << adress << ", " << phone << endl;
            file.close();
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }

    // Declaration of 2 functions not yet defined
    void viewPatientRecords();
    void registerPatient();
};

void registerPatient()
{
    string name, gender, adress, phone;
    int age;

    cout << "=== Register a New Patient ===" << endl;

    cout << "Enter patient name: ";
    getline(cin >> ws, name);

    cout << "Enter patient age: ";
    cin >> age;

    cout << "Enter patient gender(M/F): ";
    getline(cin >> ws, gender);

    cout << "Enter patient adress: ";
    getline(cin >> ws, adress);

    cout << "Enter patient phone number: ";
    getline(cin >> ws, phone);

    Patient patient(name, age, gender, adress, phone);
    patient.saveToFile(); // Could have done the same as the scheduleAppointment() function

    cout << "Patient registered succefully!" << endl;

    _getch();
}

void viewPatientRecords()
{

    // Open file patients for reading data
    ifstream file("patients.txt");
    if (file.is_open())
    {
        vector<Patient> patients; // Create a vector to store the patients
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

            if (tokens.size() == 5)
            {
                Patient patient(tokens[0], stoi(tokens[1]), tokens[2], tokens[3], tokens[4]);
                patients.push_back(patient);
            }
        }

        // If there are one or more patients, display their data.
        if (patients.size() > 0)
        {
            cout << "=== Patient Records ===" << endl;
            for (int i = 0; i < patients.size(); i++)
            {
                Patient patient = patients[i];
                cout << "Name: " << patient.getName() << endl;
                cout << "Age: " << patient.getAge() << endl;
                cout << "Gender: " << patient.getGender() << endl;
                cout << "Address: " << patient.getAdress() << endl;
                cout << "Phone: " << patient.getPhone() << endl;
                cout << endl;
            }
            // Await input before returning to the menu
            _getch();
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
}

void searchPatient()
{
    // Open file patients for reading
    ifstream file("patients.txt");

    cout << "Enter patient name: ";
    string patientName;
    getline(cin >> ws, patientName);

    if (file.is_open())
    {
        vector<Patient> patients; // Create a vectore to store the patients
        string line;

        while (getline(file, line)) // Read every line
        {
            size_t pos = 0;
            string token;
            vector<string> tokens;

            while ((pos = line.find(",")) != string::npos) // Search for commas
            {
                token = line.substr(0, pos);
                tokens.push_back(token);
                line.erase(0, pos + 1);
            }

            tokens.push_back(line);

            if (tokens.size() == 5)
            {
                Patient patient(tokens[0], stoi(tokens[1]), tokens[2], tokens[3], tokens[4]);
                patients.push_back(patient);
            }
        }

        if (patients.size() > 0)
        {
            bool found = false;

            for (int i = 0; i < patients.size(); i++)
            {
                Patient patient = patients[i];
                if (patient.getName() == patientName)
                {
                    found = true;

                    cout << "=== Patient Details ===" << endl;
                    cout << "Name: " << patient.getName() << endl;
                    cout << "Age: " << patient.getAge() << endl;
                    cout << "Gender: " << patient.getGender() << endl;
                    cout << "Address: " << patient.getAdress() << endl;
                    cout << "Phone: " << patient.getPhone() << endl;

                    break;
                }
            }

            if (!found)
            {
                cout << "Patient not found." << endl;
            }

            _getch();
        }
        else
        {
            cout << "No patients found." << endl;
            _getch();
        }

        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
        _getch();
    }
}

void generateStatistics()
{
    // Open file for reading
    ifstream file("patients.txt");
    if (file.is_open())
    {
        vector<Patient> patients;
        string line;

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

            if (tokens.size() == 5)
            {
                string name = tokens[0];
                int age = stoi(tokens[1]);
                string gender = tokens[2];
                string address = tokens[3];
                string phone = tokens[4];

                Patient patient(name, age, gender, address, phone);
                patients.push_back(patient);
            }
        }

        // If there exists any patient
        if (patients.size() > 0)
        {
            int numMale = 0, numFemale = 0;
            int totalAge = 0, numPatients = 0;

            // Check the gender of every patient
            for (int i = 0; i < patients.size(); i++)
            {
                Patient patient = patients[i];

                if (patient.getGender() == "M")
                {
                    numMale++;
                }
                else if (patient.getGender() == "F")
                {
                    numFemale++;
                }

                // Used to calculate the average age of the patients
                totalAge += patient.getAge();
                numPatients++;
            }

            cout << "=== Patient Statistics ===" << endl;
            cout << "Number of Male Patients: " << numMale << endl;
            cout << "Number of Female Patients: " << numFemale << endl;
            cout << "Average Age of Patients: " << (double)totalAge / numPatients << endl;

            _getch();
        }
        else
        {
            cout << "No patients found." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }
}
