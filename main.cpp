#include "src/Admin/Admin.hpp"
#include "src/Patient/Patient.hpp"
#include "src/Doctor/Doctor.hpp"
#include "src/Assistant/Assistant.hpp"
#include "src/Utils/Utils.hpp"

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>

#include <windows.h>
#include <io.h>

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
        out << "1"; // Initial Value
        out.close();
    }
    if (!std::filesystem::exists("data/assistant_id.txt")) {
        std::ofstream out("data/assistant_id.txt");
        out << "1"; // Initial Value
        out.close();
    }
    if (!std::filesystem::exists("data/doctor_id.txt")) {
        std::ofstream out("data/doctor_id.txt");
        out << "1"; // Initial Value
        out.close();
    }

    // Checks if any Folder of Patients or Doctors or Assistant is already created.
    Admin::checkInitialSetup();


    while (true) {


        std::cout << "Welcome to the Electronic Patient Record System.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        std::cout << "Please choice your role:\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(900));



        std::string input;
        std::cout << std::endl;
        std::cout << "=== ELECTRONIC PATIENT RECORD SYSTEM ===\n";
        std::cout << "1. Patient\n";
        std::cout << "2. Doctor\n";
        std::cout << "3. Assistant\n";
        std::cout << "0. Exit\n";
        std::cout << "Please enter your choice (or #admin): ";
        std::cin >> input;

        if (input == "#admin") {
            Admin::admin_setup();
        } else {
            int choice;
            try {
                choice = std::stoi(input);  // string to int
            } catch (...) {
                std::cout << "Invalid input.\n";
                return 0;
            }

            std::string ID;
            std::cout << "Please enter your ID: ";
            std::cin >> ID;
            std::string firstName, lastName;
            std::cout << "Please enter your first name: ";
            std::cin >> firstName;
            std::cout << "Please enter your last name: ";
            std::cin >> lastName;

            switch (choice) {
                case 1: {
                    Patient p(ID, firstName, lastName);
                    p.check_id_name(ID, firstName, lastName);
                    break;
                }
                case 2: {
                    Doctor d(ID, firstName, lastName);
                    d.check_id_name(ID, firstName, lastName);
                    break;
                }
                case 3: {
                    Assistant a(ID, firstName, lastName);
                    a.check_id_name(ID, firstName, lastName);
                    break;
                }
                case 0:
                    std::cout << "Exiting...\n";
                    return 0;
                default:
                    std::cout << "Invalid selection.\n";
                    break;
            }
        }
    }
}