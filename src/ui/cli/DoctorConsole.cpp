#include "domain/model/Doctor/Doctor.hpp"

#include <chrono>
#include <iostream>
#include <thread>

// Doctor menu.
void Doctor::displayMenu() {
    int choice;
    std::string id;

    do {
        std::cout << "\n=== Doctor Menu ===" << std::endl;
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. Add Medications for Patient" << std::endl;
        std::cout << "2. Add Records for Patient" << std::endl;
        std::cout << "3. View Patient Info" << std::endl;
        std::cout << "4. View Patient Appointments" << std::endl;
        std::cout << "5. View Patient Medications" << std::endl;
        std::cout << "6. View Patient Records" << std::endl;
        std::cout << "7. Update Field in Info\n";
        std::cout << "8. Add Extra Info" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));
                return;
            case 1: {
                std::cout << std::endl;
                std::cout << "Add Medication\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::add_patient_medication(id);
                break;
            }
            case 2: {
                std::cout << std::endl;
                std::cout << "Add Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::add_patient_record(id);
                break;
            }
            case 3: {
                std::cout << std::endl;
                std::cout << "Patient Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_info(id);
                break;
            }
            case 4: {
                std::cout << std::endl;
                std::cout << "Patient Appointments\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_appointments(id);
                break;
            }
            case 5: {
                std::cout << std::endl;
                std::cout << "Patient Medications\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_medications(id);
                break;
            }
            case 6: {
                std::cout << std::endl;
                std::cout << "Patient Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_records(id);
                break;
            }
            case 7: {
                std::string field, newInput;
                std::cout << std::endl;
                std::cout << "Update Field in File\n";
                std::cout << "Enter full ID: ";
                std::cin >> id;
                std::cout << std::endl;
                std::cout << "Enter Field: ";
                std::cin >> field;
                std::cout << std::endl;
                std::cout << "Enter New Input: ";
                std::cin >> newInput;
                std::cout << std::endl;
                update_field_in_file(id, field, newInput);
                break;
            }
            case 8: {
                std::cout << std::endl;
                std::cout << "Add Extra Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                add_extra_info(id);
            }
            default:
                std::cout << "Invalid Choice." << std::endl;
                break;
        }
    } while (choice != 0);
}

// Checks if login details are correct.
void Doctor::check_id_name(std::string id, std::string firstName, std::string lastName) {
    std::string path = "data/Doctors/" + id + "/info.txt";
    std::ifstream file_in(path);
    std::vector<std::string> content;

    if (file_in) {
        std::string line;
        std::string fileFirstName, fileLastName;
        while (std::getline(file_in, line)) {
            if (line.starts_with("First Name:")) {
                fileFirstName = line.substr(11);
            } else if (line.starts_with("Last Name:")) {
                fileLastName = line.substr(10);
            }
        }
        file_in.close();

        if (cleaned(fileFirstName) == cleaned(firstName) &&
            cleaned(fileLastName) == cleaned(lastName)) {
            std::cout << std::endl;
            std::cout << "Login successful.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            displayMenu();
        } else {
            std::cout << std::endl;
            std::cout << "Name does not match the ID.\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    } else {
        std::cout << std::endl;
        std::cerr << "Failed to read file!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// Prints all info from info.txt.
void Doctor::get_doctor_info(const std::string &doctor_full_id) {
    const std::string path = "data/Doctors/" + doctor_full_id + "/info.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << "File Content:" << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;
            content.push_back(line);
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

// Gets all info for info.txt.
void Doctor::fill_doctor_info() {
    std::cout << "\nPlease provide all Infos from the Doctor!\n" << std::endl;
    std::cout << "Date of Birth: ";
    std::getline(std::cin >> std::ws, dateOfBirth);
    std::cout << "Gender: ";
    std::getline(std::cin, gender);
    std::cout << "Nationality: ";
    std::getline(std::cin, nationality);
    std::cout << "Address: ";
    std::getline(std::cin, address);
    std::cout << "Phone Number: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Email Address: ";
    std::getline(std::cin, email);
    std::cout << "Insurance ID: ";
    std::getline(std::cin, insuranceID);
    std::cout << "InsuranceType: ";
    std::getline(std::cin, insuranceType);
}
