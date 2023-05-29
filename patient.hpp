#pragma once

#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Patient
{
private:
    string name;
    string gender;
    string adress;
    string phone;
    string CNP;
    int age;

public:
    // Constructor
    Patient(string n, string id, int a, string g, string ad, string p)
    {
        name = n;
        CNP = id;
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

    string getCNP()
    {
        return CNP;
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
            file << name << "," << CNP << "," << age << "," << gender << "," << adress << "," << phone << endl;
            file.close();
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
};

void registerPatient()
{
    string name, CNP, gender, adress, phone;
    int age;

    cout << "=== Register a New Patient ===" << endl;

    cout << "Enter patient name: ";
    getline(cin >> ws, name);

    cout << "Enter patient CNP: ";
    getline(cin >> ws, CNP);

    cout << "Enter patient age: ";
    cin >> age;

    cout << "Enter patient gender(M/F): ";
    getline(cin >> ws, gender);

    cout << "Enter patient adress: ";
    getline(cin >> ws, adress);

    cout << "Enter patient phone number: ";
    getline(cin >> ws, phone);

    Patient patient(name, CNP, age, gender, adress, phone);
    patient.saveToFile(); // Could have done the same as the scheduleAppointment() function

    cout << "Patient registered succefully!" << endl;

    system("pause");
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

            if (tokens.size() == 6)
            {
                Patient patient(tokens[0], tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
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
                cout << "CNP: " << patient.getCNP() << endl;
                cout << "Age: " << patient.getAge() << endl;
                cout << "Gender: " << patient.getGender() << endl;
                cout << "Address: " << patient.getAdress() << endl;
                cout << "Phone: " << patient.getPhone() << endl;
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
    system("pause");
}

void searchPatient()
{
    // Open file patients for reading
    ifstream file("patients.txt");
    if (file.is_open())
    {
        vector<Patient> patients; // Create a vector to store the patients
        string line;

        cout << "Enter patient name: ";
        string patientName;
        getline(cin >> ws, patientName);

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

            if (tokens.size() == 6)
            {
                Patient patient(tokens[0], tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
                patients.push_back(patient);
            }
        }

        if (patients.size() > 0)
        {
            vector<Patient> matchingPatients;

            for (int i = 0; i < patients.size(); i++)
            {
                Patient patient = patients[i];
                if (patient.getName() == patientName)
                {
                    matchingPatients.push_back(patient);
                }
            }

            if (matchingPatients.size() == 0)
            {
                cout << "Patient not found." << endl;
            }
            else if (matchingPatients.size() == 1)
            {
                cout << "=== Patient Details ===" << endl;
                cout << "Name: " << matchingPatients[0].getName() << endl;
                cout << "CNP: " << matchingPatients[0].getCNP() << endl;
                cout << "Age: " << matchingPatients[0].getAge() << endl;
                cout << "Gender: " << matchingPatients[0].getGender() << endl;
                cout << "Address: " << matchingPatients[0].getAdress() << endl;
                cout << "Phone: " << matchingPatients[0].getPhone() << endl;
            }
            else
            {
                cout << "Multiple patients found with name '" << patientName << "'. \nPlease enter the patient CNP:" << endl;
                string patientCNP;
                getline(cin >> ws, patientCNP);

                for (int i = 0; i < matchingPatients.size(); i++)
                {
                    Patient patient = matchingPatients[i];
                    if (patient.getCNP() == patientCNP)
                    {
                        cout << "=== Patient Details ===" << endl;
                        cout << "Name: " << matchingPatients[i].getName() << endl;
                        cout << "CNP: " << matchingPatients[i].getCNP() << endl;
                        cout << "Age: " << matchingPatients[i].getAge() << endl;
                        cout << "Gender: " << matchingPatients[i].getGender() << endl;
                        cout << "Address: " << matchingPatients[i].getAdress() << endl;
                        cout << "Phone: " << matchingPatients[i].getPhone() << endl;
                    }
                }
            }
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
    system("pause");
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

            if (tokens.size() == 6)
            {
                string name = tokens[0];
                string CNP = tokens[1];
                int age = stoi(tokens[2]);
                string gender = tokens[3];
                string address = tokens[4];
                string phone = tokens[5];

                Patient patient(name, CNP, age, gender, address, phone);
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
    system("pause");
}

void editPatientDetails()
{
    string name, CNP, gender, address, phone, line;
    int age;

    cout << "Enter the name of the patient to edit: ";
    getline(cin >> ws, name);

    ifstream file("patients.txt");
    if (file.is_open())
    {
        vector<Patient> patients;
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

            if (tokens.size() == 6)
            {
                Patient patient(tokens[0], tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
                patients.push_back(patient);
            }
        }

        file.close();

        bool patientFound = false;
        for (int i = 0; i < patients.size(); i++)
        {
            Patient patient = patients[i];
            if (patient.getName() == name)
            {
                if (!patientFound)
                {
                    patientFound = true;
                    cout << "Enter the patient CNP: ";
                    getline(cin >> ws, CNP);
                }

                if (patient.getCNP() == CNP)
                {
                    cout << "=== Patient Details ===" << endl;
                    cout << "Name: " << patient.getName() << endl;
                    cout << "CNP: " << patient.getCNP() << endl;
                    cout << "Age: " << patient.getAge() << endl;
                    cout << "Gender: " << patient.getGender() << endl;
                    cout << "Address: " << patient.getAdress() << endl;
                    cout << "Phone: " << patient.getPhone() << endl;

                    cout << "Enter the patient's new CNP: ";
                    getline(cin >> ws, CNP);

                    cout << "Enter the patient's new age: ";
                    cin >> age;

                    cout << "Enter the patient's new gender(M/F): ";
                    getline(cin >> ws, gender);

                    cout << "Enter the patient's new address: ";
                    getline(cin >> ws, address);

                    cout << "Enter the patient's new phone number: ";
                    getline(cin >> ws, phone);

                    // Update the patient's details
                    patient = Patient(name, CNP, age, gender, address, phone);
                    patients[i] = patient;

                    cout << "Patient details updated successfully!" << endl;
                    break;
                }
            }
        }

        if (!patientFound)
        {
            cout << "Patient not found." << endl;
        }

        // Update the patients file with the modified data
        ofstream outputFile("patients.txt");
        if (outputFile.is_open())
        {
            for (int i = 0; i < patients.size(); i++)
            {
                Patient patient = patients[i];
                outputFile << patient.getName() << ",";
                outputFile << patient.getCNP() << ",";
                outputFile << patient.getAge() << ",";
                outputFile << patient.getGender() << ",";
                outputFile << patient.getAdress() << ",";
                outputFile << patient.getPhone() << endl;
            }

            outputFile.close();
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
    else
    {
        cout << "Error opening file." << endl;
    }

    system("pause");
}

void deletePatient()
{
    string name, CNP, line;

    cout << "Enter the name of the patient to delete: ";
    getline(cin >> ws, name);

    ifstream file("patients.txt");
    if (file.is_open())
    {
        vector<Patient> patients;
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

            if (tokens.size() == 6)
            {
                Patient patient(tokens[0], tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
                patients.push_back(patient);
            }
        }

        file.close();

        bool patientFound = false;
        for (int i = 0; i < patients.size(); i++)
        {
            Patient patient = patients[i];
            if (patient.getName() == name)
            {
                if (!patientFound)
                {
                    patientFound = true;
                    cout << "Enter the patient CNP: ";
                    getline(cin >> ws, CNP);
                }

                if (patient.getCNP() == CNP)
                {
                    patients.erase(patients.begin() + i);
                    cout << "Patient deleted successfully!" << endl;
                    break;
                }
            }
        }

        if (!patientFound)
        {
            cout << "Patient not found." << endl;
        }

        // Update the patients file with the modified data
        ofstream outputFile("patients.txt");
        if (outputFile.is_open())
        {
            for (int i = 0; i < patients.size(); i++)
            {
                Patient patient = patients[i];
                outputFile << patient.getName() << ",";
                outputFile << patient.getCNP() << ",";
                outputFile << patient.getAge() << ",";
                outputFile << patient.getGender() << ",";
                outputFile << patient.getAdress() << ",";
                outputFile << patient.getPhone() << endl;
            }

            outputFile.close();
        }
        else
        {
            cout << "Error opening file." << endl;
        }
    }
    else
    {
        cout << "Error opening file." << endl;
    }
    system("pause");
}
