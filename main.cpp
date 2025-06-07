#include <iostream>
#include <memory>
#include <string>



#include "src/User/User.hpp"
#include "src/Patient/Patient.hpp"
#include "src/Doctor/Doctor.hpp"
#include "src/Assistant/Assistant.hpp"

int main() {
    Patient p = Patient("Kilian1", "Second");
    User *k = new Patient("Kilian2", "König");
    std::cout << p.getFirstName() << std::endl;
    std::cout << k->getFirstName() << std::endl;
    std::cout << p.getRole() << std::endl;

    delete k;

    while (true) {
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
                std::unique_ptr<User> patient = std::make_unique<Patient>(firstName, lastName);
                patient->displayMenu();
                break;
            }
                case 2: {
                std::unique_ptr<User> doctor = std::make_unique<Doctor>(firstName, lastName);
                doctor->displayMenu();
                break;
            }
                case 3: {
                std::unique_ptr<User> assistant = std::make_unique<Assistant>(firstName, lastName);
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