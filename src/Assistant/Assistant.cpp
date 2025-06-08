

#include "Assistant.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>

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

    std::ifstream file_in("data/patient_id.txt");
    int id;
    if (file_in.is_open()) {
        file_in >> id;
        file_in.close();
    } else {
        std::cerr << "Faild to open!\n";
    }

    std::ofstream file_out("data/patient_id.txt");
    if (file_out.is_open()) {
        file_out << id + 1;
        file_out.close();
    } else {
        std::cerr << "Faild to open!\n";
    }



}
