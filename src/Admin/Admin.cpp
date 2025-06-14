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



void Admin::checkInitialSetup() {
    if (!std::filesystem::exists("data/Patients") && !std::filesystem::exists("data/Assistants") && !std::filesystem::exists("data/Doctors")) {

        std::ofstream out("data/admin_logging.txt");
        out << "EPR-System Setup from Admin: " << getDate() << " " << getTime() << "\n\n"; // Initial Value
        out.close();

        std::cout << "[!] System is not initialized yet.\n";
        std::cout << "[!] No user structure found.\n";
        std::cout << "→ Entering admin setup mode...\n";
        admin_setup();

    }
}

void Admin::admin_setup() {
    int choice;
    std::string firstName, lastName;
    std::string id;

        std::cout << "=== Admin Logging | EPR SYSTEM ===\n";
        std::cout << "1. Create Patient\n";
        std::cout << "2. Info Patient\n";
        std::cout << "3. Create Doctor\n";
        std::cout << "4. Info Doctor\n";
        std::cout << "5. Create Assistant\n";
        std::cout << "6. Info Assistant\n";
        std::cout << "0. Exit\n";
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

    switch (choice) {
        case 1: {
            admin_getNames( firstName, lastName);
            Patient p("", firstName, lastName);
            p.createNewPatient();
            std::cout << "Patient: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 2: {
            std::cout << "Please enter the full Patient-ID: ";
            std::cin >> id;
            Patient::get_patient_info(id);
            break;
        }

        case 3: {
            admin_getNames(firstName, lastName);
            Doctor d("", firstName, lastName);
            d.fill_doctor_info();
            d.createNewDoctor();
            std::cout << "Doctor: [" << firstName << " " << lastName << "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 4: {
            std::cout << "Please enter the full Doctor-ID: ";
            std::cin >> id;
            Doctor::get_doctor_info(id);
            break;
        }

        case 5: {
            admin_getNames(firstName, lastName);
            const Assistant a("", firstName, lastName);
            a.createNewAssistant();
            std::cout << "Assistant: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 6: {
            std::cout << "Please enter the full Assistant-ID: ";
            std::cin >> id;
            Assistant::get_assistant_info(id);
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            return;

        default: {
                std::cout << "Invalid choice.\n";
                break;
            }
    }
}

void Admin::admin_getNames(std::string &firstName, std::string &lastName) {
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
}




