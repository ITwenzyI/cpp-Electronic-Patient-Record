#include "Assistant.hpp"

Assistant::Assistant(const std::string& assistant_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(assistant_id, "Assistant", firstName, lastName,
           "", "", "", "", "", "", "", "") {}

void Assistant::displayMenu() {
    int choice;
    std::string patientId;

    do {
        std::cout << "\n=== Assistant Menu ===" << std::endl;
        std::cout << "1. View Medical Records" << std::endl;
        std::cout << "2. View Documents" << std::endl;
        std::cout << "3. View open Doctors" << std::endl;
        std::cout << "4. Create Patient" << std::endl;
        std::cout << "5. Book Appointment for Patient" << std::endl;
        std::cout << "7. Update Field in File\n";
        std::cout << "0. Logout" << std::endl;
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;

                break;
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;

            case 5: {
                std::cout << "Enter the full Patient ID: ";
                std::cin >> patientId;
                Patient::add_patient_appointment(patientId);
            }
            default:
                std::cout << "Invalid Choice." << std::endl;
                break;

        }



    } while (choice != 0);
}

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
        out << "PatientID: " << assistant_full_id << "\n\n"; // AssistantID A0001
        out << "--- Personal Infos ---"  << "\n";
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

    // Creating file with all the Actions from the Assistant
    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out( folderName + "/actions.txt");
        out << "AssistantID: " << assistant_full_id << "\n\n"; // AssistantID A0001

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

void Assistant::check_id_name(std::string id, std::string firstName, std::string lastName) {

    std::string path = "data/Assistants/" + id + "/info.txt";
    std::ifstream file_in(path);
    std::vector<std::string> content;

    if (file_in) {
        std::string line;
        std::string fileFirstName, fileLastName;
        while (std::getline(file_in, line)) {
            if (line.starts_with("First Name:")) {
                fileFirstName = line.substr(11);  // all after "First Name:"
            } else if (line.starts_with("Last Name:")) {
                fileLastName = line.substr(10);    // all after "Last Name:"
            }
        }
        file_in.close();



        if (cleaned(fileFirstName) == cleaned(firstName) &&
            cleaned(fileLastName) == cleaned(lastName)) {
            std::cout << std::endl;
            std::cout << "Login successful.\n";
            displayMenu();
            }
        else {
            std::cout << std::endl;
            std::cout << "Name does not match the ID.\n";
        }
    } else {
        std::cout << std::endl;
        std::cerr << "Failed to read file!" << std::endl;
    }
    displayMenu();
}

void Assistant::get_assistant_info(const std::string &assistant_full_id) {
    const std::string path = "data/Assistants/" + assistant_full_id + "/info.txt";  // To call Assistant::get_assistant_info("A0001")
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << "File Content:" << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;       // Output: line
            content.push_back(line);                // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
    }
}

void Assistant::fill_assistant_info() {
    std::cout << "\nPlease provide all Infos from the Assistant!\n" << std::endl;
    std::cout << "Date of Birth: ";
    std::getline(std::cin >> std::ws, dateOfBirth);
    std::cout << "Gender: ";
    std::getline(std::cin, gender);
    std::cout << "Nationality: ";
    std::getline(std::cin, nationality);
    std::cout << "Address: ";
    std::getline(std::cin, address);
    std::cout << "Phone Number: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Email Address: ";
    std::getline(std::cin, email);
    std::cout << "Insurance ID: ";
    std::getline(std::cin, insuranceID);
    std::cout << "InsuranceType: ";
    std::getline(std::cin, insuranceType);
}


