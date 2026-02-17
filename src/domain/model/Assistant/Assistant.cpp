#include "Assistant.hpp"

Assistant::Assistant(const std::string& assistant_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(assistant_id, UserRole::Assistant, firstName, lastName,
           "", "", "", "", "", "", "", "") {}

// Assistant::createNewAssistant();
void Assistant::createNewAssistant() const {


    int assistant_id = Assistant_ID::get_assistant_id(); // get new Assistant ID
    std::filesystem::create_directories("data/Assistants");
    std::string folderName = std::format("data/Assistants/A{:04}", assistant_id); // Style: A0001
    std::filesystem::create_directories(folderName);


    // Full Assistant ID = A0001
    std::string assistant_full_id = std::format("A{:04}", assistant_id); // Style: A0001


    // -----------------------------------------
    // File creation for Assistant


    // Creating file with all the Infos from the Assistant
    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out( folderName + "/info.txt");
        out << "--- Personal Infos ---"  << "\n";
        out << "Full Name: " << firstName << " " << lastName << "\n";
        out << "First Name: " << firstName << "\n"; // First Name
        out << "Last Name: " << lastName << "\n"; // Last Name
        out << "Date of Birth: " << dateOfBirth << "\n";
        out << "Gender: " << gender << "\n";
        out << "Nationality: " << nationality << "\n";

        out << "\n" << "--- Contact Infos ---"  << "\n";
        out << "Address: " << address << "\n";
        out << "Phone Number: " << phoneNumber << "\n";
        out << "Email Address: " << email << "\n";

        out << "\n" << "--- Insurance Infos ---"  << "\n";
        out << "InsuranceID: " << insuranceID << "\n";
        out << "InsuranceType: " << insuranceType << "\n";

        out << "\n" << "--- Extra Infos ---"  << "\n";


        out.close();
    }

    // Creating file with all the Actions from the Assistant (Currently not available)
    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out( folderName + "/actions.txt");

        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";


        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Assistant ID for new Assistant (+1)
    Assistant_ID::update_assistant_id(assistant_id); // without A
    // -----------------------------------------

}




