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



#include "src/User/User.hpp"
#include "src/Patient/Patient.hpp"
#include "src/Doctor/Doctor.hpp"
#include "src/Assistant/Assistant.hpp"
#include "src/Utils/Utils.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    //Patient p = Patient("Kilian1", "Second");
    //User *k = new Patient("Kilian2", "König");
    //std::cout << p.getFirstName() << std::endl;
    //std::cout << k->getFirstName() << std::endl;
    //std::cout << p.getRole() << std::endl;

    while (true) {

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

        Assistant::createNewPatient("test1", "test2");
        //User::get_patient_info("P00000006");


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

        std::string firstName, lastName;

        if (choice == 0) {
            break;
        }

        std::cout << "Enter First Name: " << std::endl;
        std::cin >> firstName;
        std::cout << "Enter Last Name: " << std::endl;
        std::cin >> lastName;

        switch (choice) {
                case 1: {
                const std::unique_ptr<User> patient = std::make_unique<Patient>(firstName, lastName);
                patient->displayMenu();
                break;
            }
                case 2: {
                const std::unique_ptr<User> doctor = std::make_unique<Doctor>(firstName, lastName);
                doctor->displayMenu();
                break;
            }
                case 3: {
                const std::unique_ptr<User> assistant = std::make_unique<Assistant>(firstName, lastName);
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