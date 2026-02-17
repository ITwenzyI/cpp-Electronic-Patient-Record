#include "domain/model/Patient/Patient.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/PatientWriteService.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace {
IUserRepository& userRepository() {
    static FileUserRepository repository;
    return repository;
}

IPatientRepository& patientRepository() {
    static FilePatientRepository repository;
    return repository;
}

PatientRecordQueryService& patientRecordQueryService() {
    static PatientRecordQueryService service(userRepository(), patientRepository());
    return service;
}

PatientWriteService& patientWriteService() {
    static PatientWriteService service(patientRepository());
    return service;
}

std::string extractField(const std::vector<std::string>& lines, const std::string& keyPrefix) {
    for (const auto& line : lines) {
        if (line.starts_with(keyPrefix)) {
            return line.substr(keyPrefix.size());
        }
    }
    return "";
}
}

// Patient menu.
void Patient::displayMenu() {
    int choice;
    std::string id;

    do {
        std::cout << "\n=== Patient Menu ===" << std::endl;
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. View Appointments" << std::endl;
        std::cout << "2. View Medications" << std::endl;
        std::cout << "3. View Records" << std::endl;
        std::cout << "4. Book Appointment" << std::endl;
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
                std::cout << "Appointments\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                {
                    const std::vector<std::string> appointments = patientRecordQueryService().getAppointments(id);
                    if (appointments.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }

                    std::cout << std::endl;
                    for (const auto& line : appointments) {
                        std::cout << line << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
                break;
            }
            case 2: {
                std::cout << std::endl;
                std::cout << "Medications\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                {
                    const std::vector<std::string> medications = patientRecordQueryService().getMedications(id);
                    if (medications.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }

                    std::cout << std::endl;
                    for (const auto& line : medications) {
                        std::cout << line << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
                break;
            }
            case 3: {
                std::cout << std::endl;
                std::cout << "Records\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                {
                    const std::vector<std::string> records = patientRecordQueryService().getRecords(id);
                    if (records.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }

                    std::cout << std::endl;
                    for (const auto& line : records) {
                        std::cout << line << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
                break;
            }
            case 4: {
                std::string date, time, doctorName, reason;
                std::cout << std::endl;
                std::cout << "Book Appointment\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                std::cout << "=== Appointment Request ===\n";
                std::cout << "Enter date (YYYY-MM-DD): ";
                std::cin >> date;
                std::cout << "Enter time (HH:MM): ";
                std::cin >> time;
                std::cin.ignore();
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                std::cout << "Enter reason (optional): ";
                std::getline(std::cin, reason);

                if (!patientWriteService().requestAppointment(id, date, time, doctorName, reason)) {
                    std::cerr << "Error: could not open data/Appointments/requests.txt\n";
                    break;
                }

                std::cout << std::endl;
                std::cout << "Appointment request submitted. Waiting for confirmation.\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                break;
            }
            default:
                std::cout << "Invalid Choice." << std::endl;
                break;
        }
    } while (choice != 0);
}

// Checks if login details are correct.
void Patient::check_id_name(std::string id, std::string firstName, std::string lastName) {
    const std::vector<std::string> info = userRepository().readInfo(id);
    if (!userRepository().exists(id)) {
        std::cout << std::endl;
        std::cerr << "Failed to read file!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    const std::string fileFirstName = extractField(info, "First Name:");
    const std::string fileLastName = extractField(info, "Last Name:");

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
}

// Gets all info for info.txt.
void Patient::fill_patient_info() {
    std::cout << "\nPlease provide all Infos from the Patient!\n" << std::endl;
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

