

#include "Assistant.hpp"
#include "../Utils/Utils.hpp"


#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <format>  // Nur in C++20

Assistant::Assistant(const std::string& firstName, const std::string& lastName) 
    : User(firstName, lastName, "Assistant") {

};

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


    int patient_id = get_patient_id(); // get old ID
    std::string folderName = "data/P" + std::string(8 - std::to_string(patient_id).length(), '0') + std::to_string(patient_id); // P00000001
    //std::string folderName = std::format("data/P{:08}", patient_id); // If you have C++20
    std::filesystem::create_directories(folderName);





    update_patient_id(patient_id); // update ID



}
