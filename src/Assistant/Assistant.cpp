

#include "Assistant.hpp"
#include "../Patient/Patient.hpp"

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

