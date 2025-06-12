/*
 * File: Admin
 * Author: Kilian | ItwenzyI
 * Created: 10.06.2025
 * Description: 
 */
//

#include "Admin.hpp"

Admin::Admin() = default;

Admin::~Admin() = default;



void Admin::checkInitialSetup() {
    if (!std::filesystem::exists("data/Patients") && !std::filesystem::exists("data/Assistants") && !std::filesystem::exists("data/Doctors")) {

        std::ofstream out("data/admin_logging.txt");
        out << "Admin Logging at: " << getDate() << " " << getTime() << "\n\n"; // Initialvalue
        out.close();

        std::cout << "[!] System is not initialized yet.\n";
        std::cout << "[!] No user structure found.\n";
        std::cout << "→ Entering admin setup mode...\n";
        admin_setup();

    } else {

    }
}

void Admin::admin_setup() {

    std::cout << "=== Admin Logging | EPR SYSTEM ===\n";
    std::cout << "1. Create Patient\n";
    std::cout << "2. Delete Patient\n";
    std::cout << "3. Create Doctor\n";
    std::cout << "4. Delete Doctor\n";
    std::cout << "5. Create Assistant\n";
    std::cout << "6. Delete Assistant\n";
    std::cout << "0. Exit\n";
    std::cout << "Please enter your choice: ";

    int choice;
    std::cin >> choice;
}

