//
// Created by User on 04.06.2025.
//

#include "Patient.hpp"
#include <iostream>

Patient::Patient(const std::string& firstName, const std::string& lastName)
    : User(firstName, lastName, "Patient") {

}

Patient::~Patient() = default;

void Patient::displayMenu() {
    int choice;

    do {
        std::cout << "\n=== Patient Menu ===" << std::endl;
        std::cout << "1. View Medical Record" << std::endl;
        std::cout << "2. View Documents" << std::endl;
        std::cout << "3. Book Appointment" << std::endl;
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
