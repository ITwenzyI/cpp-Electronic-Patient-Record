

#include "Assistant.hpp"

#include <chrono>

#include "../Utils/Utils.hpp"
#include "../IDs/IDs.hpp"


#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <format>  // Nur in C++20

Assistant::Assistant(const std::string& patient_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(patient_id, "patient", firstName, lastName,
           "", "", "", "", "", "", "", "") {}

Assistant::~Assistant() = default;

void Assistant::displayMenu() {
    int choice;

    do {
        std::cout << "\n=== Assistant Menu ===" << std::endl;
        std::cout << "1. View Medical Records" << std::endl;
        std::cout << "2. View Documents" << std::endl;
        std::cout << "3. View open Doctors" << std::endl;
        std::cout << "4. Create Patient" << std::endl;
        std::cout << "5. Book Appointment" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                std::cout << "Invalid Choice." << std::endl;
                break;

        }



    } while (choice != 0);
}


void Assistant::createNewPatient(const std::string& firstName, const std::string& lastName) {


    int patient_id = Patient_ID::get_patient_id(); // get new Patient ID
    std::filesystem::create_directories("data/Patients");
    std::string folderName = "data/Patients/P" + std::string(8 - std::to_string(patient_id).length(), '0') + std::to_string(patient_id); // Style: P00000001
    //std::string folderName = std::format("data/P{:08}", patient_id); // If you have C++20
    std::filesystem::create_directories(folderName);


    // Full Patient ID = P00000001
    std::string patient_full_id = "P" + std::string(8 - std::to_string(patient_id).length(), '0') + std::to_string(patient_id);


    // -----------------------------------------
    // File creation for Patient


    // Creating file with all the Infos from the Patient
    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out( folderName + "/info.txt");
        out << "PatientID: " << patient_full_id << "\n\n"; // PatientID
        out << "--- Personal Infos ---"  << "\n";
        out << "Full Name: " << firstName << " " << lastName << "\n";
        out << "First Name: " << firstName << "\n"; // First Name
        out << "Last Name: " << lastName << "\n"; // Last Name
        out << "Date of Birth: " << lastName << "\n";
        out << "Gender: " << lastName << "\n";
        out << "Nationality: " << lastName << "\n";

        out << "\n" << "--- Contact Infos ---"  << "\n";
        out << "Adress: " << lastName << "\n";
        out << "Phone Number: " << lastName << "\n";
        out << "Email Adress: " << lastName << "\n";

        out << "\n" << "--- Insurance Infos ---"  << "\n";
        out << "InsuranceID: " << lastName << "\n";
        out << "InsuranceType: " << lastName << "\n";

        out << "\n" << "--- Extra Infos ---"  << "\n";


        out.close();
    }

    // Creating file with a list of all the records from the Patient
    if (!std::filesystem::exists(folderName + "/records.txt")) {
        std::ofstream out( folderName + "/records.txt");
        out << "--- Example ---" << patient_full_id << "\n"; // PatientID
        out << "[2025-06-08] Dr. Schmitt: Blood pressure too high, recommended: Exercise & diet." << "\n"; // Example
        out << "[2025-06-15] Dr. Schmitt: Control: blood pressure decreased, no medication necessary." << "\n"; // Example
        out.close();
    }

    // Creating fike with a list of all appointments from the Patient
    if (!std::filesystem::exists(folderName + "/appointments.txt")) {
        std::ofstream out( folderName + "/appointments.txt");
        out << "--- Example ---" << patient_full_id << "\n"; // PatientID
        out << "[2025-06-12] [09:30] – Dr. Schmitt" << "\n"; // Example
        out << "[2025-06-13] [14:00] - Dr. Meier (control)" << "\n"; // Example
        out.close();
    }

    // Creating file with all the medications the Patient needs
    if (!std::filesystem::exists(folderName + "/medications.txt")) {
        std::ofstream out( folderName + "/medication.txt");
        out << "--- Example ---" << patient_full_id << "\n"; // PatientID
        out << "Ibuprofen 400 mg - 3x daily - from 2025-06-08 to 2025-06-12" << "\n"; // Example
        out << "Ramipril 5 mg – 1x daily in the morning - permanently" << "\n"; // Example
        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Patient ID for new Patient (+1)
    Patient_ID::update_patient_id(patient_id);
    // -----------------------------------------



}
