/*
 * File: Admin
 * Author: Kilian | ItwenzyI
 * Created: 10.06.2025
 * Description: 
 */
//

#include "Admin.hpp"

#include <thread>

Admin::Admin() = default;

Admin::~Admin() = default;



// Checks if any Folder of Patients, Assistants or Doctors is already created, if not then the System needs an Initialization
bool Admin::checkInitialSetup() {
    if (!std::filesystem::exists("data/Assistants") || !std::filesystem::exists("data/Doctors")) {

        std::ofstream out("data/admin_logging.txt");
        out << "EPR-System Setup from Admin: " << getDate() << " " << getTime() << "\n\n"; // Initial Value
        out.close();

        std::cout << "[!] System is not initialized yet.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (!std::filesystem::exists("data/Assistants") && !std::filesystem::exists("data/Doctors")) {
            std::cout << "[!] No Assistant and Doctor structure found.\n";
        }
        else if (!std::filesystem::exists("data/Assistants")) {
            std::cout << "[!] No Assistant structure found.\n";
        }
        else if (!std::filesystem::exists("data/Doctors")) {
            std::cout << "[!] No Doctor structure found.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "→ Entering admin setup mode...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        admin_setup();

        return false;

    }
    return true;
}


// Admin Menu with all the Options
void Admin::admin_setup() {
    int choice;
    std::string firstName, lastName;
    std::string id;


    do {
        std::cout << std::endl;
        std::cout << "=== Admin Logging | EPR SYSTEM ===\n";
        std::cout << "1. Create Patient\n";
        std::cout << "2. Info Patient\n";
        std::cout << "3. Create Doctor\n";
        std::cout << "4. Info Doctor\n";
        std::cout << "5. Create Assistant\n";
        std::cout << "6. Info Assistant\n";
        std::cout << "7. Update Field in File\n";
        std::cout << "8. Backup User Info\n";
        std::cout << "0. Exit\n";
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

    switch (choice) {
        case 1: {
            std::cout << std::endl;
            admin_getNames( firstName, lastName);
            Patient p("", firstName, lastName);
            p.fill_patient_info();
            p.createNewPatient();
            std::cout << std::endl;
            std::cout << "Patient: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 2: {
            std::cout << std::endl;
            std::cout << "Please enter the full Patient-ID: ";
            std::cin >> id;
            std::cout << std::endl;
            Patient::get_patient_info(id);
            break;
        }

        case 3: {
            std::cout << std::endl;
            admin_getNames(firstName, lastName);
            Doctor d("", firstName, lastName);
            d.fill_doctor_info();
            d.createNewDoctor();
            std::cout << std::endl;
            std::cout << "Doctor: [" << firstName << " " << lastName << "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 4: {
            std::cout << std::endl;
            std::cout << "Please enter the full Doctor-ID: ";
            std::cin >> id;
            Doctor::get_doctor_info(id);
            break;
        }

        case 5: {
            std::cout << std::endl;
            admin_getNames(firstName, lastName);
            Assistant a("", firstName, lastName);
            a.fill_assistant_info();
            a.createNewAssistant();
            std::cout << std::endl;
            std::cout << "Assistant: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 6: {
            std::cout << std::endl;
            std::cout << "Please enter the full Assistant-ID: ";
            std::cin >> id;
            Assistant::get_assistant_info(id);
            break;
        }

        case 7: {
            std::string field, newInput;
            std::cout << std::endl;
            std::cout << "Please enter the full ID: ";
            std::cin >> id;
            std::cout << "Please enter the field to change: ";
            std::cin >> field;
            std::cout << "Please enter the new input: ";
            std::cin >> newInput;
            User::update_field_in_file(id, field, newInput);
            break;
        }

        case 8: {
            std::cout << std::endl;
            std::cout << "Please enter the full ID to backup: ";
            std::cin >> id;
            exportUserData(id);
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return;

        default: {
                std::cout << "Invalid choice.\n";
                break;
            }
    }
    } while (choice != 0);


}


// Just a simple function to get the Names
void Admin::admin_getNames(std::string &firstName, std::string &lastName) {
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
}


void Admin::exportUserData(const std::string& id) {

    // Determine the correct file path based on the ID (Example: D0001 = Doctors/D0001/info.txt)
    std::string path = get_file_path_from_id(id);

    if (path.empty()) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::ifstream file_in(path);
    std::vector<std::string> content;

    if (file_in) {
        std::string line;
        while (std::getline(file_in, line)) {
            content.push_back(line);                // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }


    std::filesystem::create_directories("data/Exports");
    std::string folderName = std::format("data/Exports/{}", id); // Style: P00000001
    std::filesystem::create_directories(folderName);

    // Creating file with all the infos from the User
    if (!std::filesystem::exists(folderName + "/backup_info.txt")) {
        std::ofstream out( folderName + "/backup_info.txt");
        for (const auto & i : content) {
            out << i << "\n";
        }
        out.close();
    }

    std::cout << "Successfully created backup_info.txt file for: " << folderName << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));

}





