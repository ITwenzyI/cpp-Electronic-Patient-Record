#include <iostream>
#include <memory>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>

#include <windows.h>
#include <io.h>


#include "src/Admin/Admin.hpp"
#include "src/User/User.hpp"
#include "src/Patient/Patient.hpp"
#include "src/Doctor/Doctor.hpp"
#include "src/Assistant/Assistant.hpp"
#include "src/IDs/IDs.hpp"
#include "src/Utils/Utils.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Booting up System.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    std::cout << "Booting up System..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    std::cout << "Booting up System...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    std::filesystem::create_directories("data");
    if (!std::filesystem::exists("data/patient_id.txt")) {
        std::ofstream out("data/patient_id.txt");
        out << "1"; // Initialvalue
        out.close();
    }
    if (!std::filesystem::exists("data/assistant_id.txt")) {
        std::ofstream out("data/assistant_id.txt");
        out << "1"; // Initialvalue
        out.close();
    }
    if (!std::filesystem::exists("data/doctor_id.txt")) {
        std::ofstream out("data/doctor_id.txt");
        out << "1"; // Initialvalue
        out.close();
    }

    //Patient::createNewPatient("FirstName", "LastName");
    //Patient::get_patient_info("P00000001");

    //Assistant::createNewAssistant("FirstName", "Lastname");
    //Assistant::get_assistant_info("A0001");

    //Doctor::createNewDoctor("FirstName", "LastName");
    //Doctor::get_doctor_info("D0001");

    while (Admin::checkInitialSetup()) {


        std::cout << "Welcome to the Electronic Patient Record System.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        std::cout << "Please choice your role:\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(900));



        std::cout << "=== ELECTRONIC PATIENT RECORD SYSTEM ===\n";
        std::cout << "1. Patient\n";
        std::cout << "2. Doctor\n";
        std::cout << "3. Assistant\n";
        std::cout << "0. Exit\n";
        std::cout << "Please enter your choice: ";

        int choice;
        std::cin >> choice;

        std::string firstName, lastName, id;

        if (choice == 0) {
            break;
        }

        std::cout << "Enter First Name: " << std::endl;
        std::cin >> firstName;
        std::cout << "Enter Last Name: " << std::endl;
        std::cin >> lastName;
        std::cout << "Enter ID: " << std::endl;
        std::cin >> id;

        switch (choice) {
                case 1: {
                const std::unique_ptr<User> patient = std::make_unique<Patient>(id, firstName, lastName);
                patient->displayMenu();
                break;
            }
                case 2: {
                const std::unique_ptr<User> doctor = std::make_unique<Doctor>(id, firstName, lastName);
                doctor->displayMenu();
                break;
            }
                case 3: {
                const std::unique_ptr<User> assistant = std::make_unique<Assistant>(id, firstName, lastName);
                assistant->displayMenu();
                break;
            }
                default: {
                std::cout << "Invalid Choice\n";
                break;
            }
        }
    }


    std::cout << "Program Exit.\n" << std::endl;
    return 0;
}