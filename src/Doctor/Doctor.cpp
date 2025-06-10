
#include "Doctor.hpp"
#include <iostream>

Doctor::Doctor(const std::string& patient_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(patient_id, "patient", firstName, lastName,
           "", "", "", "", "", "", "", "") {}

Doctor::~Doctor() = default;


void Doctor::displayMenu() {
    int choice;

    do {
        std::cout << "\n=== Doctor Menu ===" << std::endl;
        std::cout << "1. View Medical Records" << std::endl;
        std::cout << "2. View Documents" << std::endl;
        std::cout << "3. View open Appointments" << std::endl;
        std::cout << "4. View Calender" << std::endl;
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
