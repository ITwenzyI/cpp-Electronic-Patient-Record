

#include "Assistant.hpp"
#include "../Patient/Patient.hpp"

#include <chrono>

#include "../Utils/Utils.hpp"
#include "../IDs/IDs.hpp"


#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

Assistant::Assistant(const std::string& assistant_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(assistant_id, "Assistant", firstName, lastName,
           "", "", "", "", "", "", "", "") {}

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
                Patient::get_patient_info("P00000001");
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

void Assistant::createNewAssistant(const std::string& firstName, const std::string& lastName) {


    int assistant_id = Assistant_ID::get_assistant_id(); // get new Assistant ID
    std::filesystem::create_directories("data/Assistants");
    std::string folderName = "data/Assistants/A" + std::string(4 - std::to_string(assistant_id).length(), '0') + std::to_string(assistant_id); // Style: A0001
    std::filesystem::create_directories(folderName);


    // Full Assistant ID = A0001
    std::string assistant_full_id = "A" + std::string(4 - std::to_string(assistant_id).length(), '0') + std::to_string(assistant_id);


    // -----------------------------------------
    // File creation for Assistant


    // Creating file with all the Infos from the Assistant
    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out( folderName + "/info.txt");
        out << "PatientID: " << assistant_full_id << "\n\n"; // AssistantID
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

    // Creating file with all the Actions from the Assistant
    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out( folderName + "/actions.txt");
        out << "AssistantID: " << assistant_full_id << "\n\n"; // AssistantID

        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";


        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Assistant ID for new Assistant (+1)
    Assistant_ID::update_assistant_id(assistant_id);
    // -----------------------------------------


}

void Assistant::get_assistant_info(const std::string &assistant_full_id) {
    std::string path = "data/Assistants/" + assistant_full_id + "/info.txt";  // To call Assistant::get_assistant_info("A0001")
    std::ifstream file_in(path);
    std::string line;
    std::vector<std::string> content;

    if (file_in) {
        std::cout << "File Content:" << std::endl; // Ausgabe: Dateiinhalt:
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Ausgabe: Zeile n
            content.push_back(line);                // Zeile speichern
        }
        file_in.close();
    } else {
        std::cerr << "Faild to read file!" << std::endl;
    }
}

