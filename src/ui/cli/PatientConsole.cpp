#include "domain/model/Patient/Patient.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/PatientWriteService.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/ConsoleIO.hpp"

#include <iostream>

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
        ConsoleIO::printHeader("=== Patient Menu ===");
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. View Appointments" << std::endl;
        std::cout << "2. View Medications" << std::endl;
        std::cout << "3. View Records" << std::endl;
        std::cout << "4. Book Appointment" << std::endl;
        std::cout << "0. Logout" << std::endl;
        choice = ConsoleIO::promptInt("Please enter your choice: ");

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
                ConsoleIO::pauseSeconds(3);
                return;
            case 1: {
                ConsoleIO::printHeader("Appointments");
                id = ConsoleIO::promptToken("Enter your full ID: ");
                {
                    const Result<std::vector<std::string>> appointmentsResult = patientRecordQueryService().getAppointments(id);
                    if (!appointmentsResult) {
                        std::cerr << appointmentsResult.errorMessage() << std::endl;
                        break;
                    }

                    std::cout << std::endl;
                    ConsoleIO::printLines(appointmentsResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 2: {
                ConsoleIO::printHeader("Medications");
                id = ConsoleIO::promptToken("Enter your full ID: ");
                {
                    const Result<std::vector<std::string>> medicationsResult = patientRecordQueryService().getMedications(id);
                    if (!medicationsResult) {
                        std::cerr << medicationsResult.errorMessage() << std::endl;
                        break;
                    }

                    std::cout << std::endl;
                    ConsoleIO::printLines(medicationsResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 3: {
                ConsoleIO::printHeader("Records");
                id = ConsoleIO::promptToken("Enter your full ID: ");
                {
                    const Result<std::vector<std::string>> recordsResult = patientRecordQueryService().getRecords(id);
                    if (!recordsResult) {
                        std::cerr << recordsResult.errorMessage() << std::endl;
                        break;
                    }

                    std::cout << std::endl;
                    ConsoleIO::printLines(recordsResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 4: {
                std::string date, time, doctorName, reason;
                ConsoleIO::printHeader("Book Appointment");
                id = ConsoleIO::promptToken("Enter your full ID: ");
                std::cout << "=== Appointment Request ===\n";
                date = ConsoleIO::promptToken("Enter date (YYYY-MM-DD): ");
                time = ConsoleIO::promptToken("Enter time (HH:MM): ");
                std::cin.ignore();
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                std::cout << "Enter reason (optional): ";
                std::getline(std::cin, reason);

                const Result<void> requestResult = patientWriteService().requestAppointment(id, date, time, doctorName, reason);
                if (!requestResult) {
                    std::cerr << requestResult.errorMessage() << '\n';
                    break;
                }

                std::cout << std::endl;
                std::cout << "Appointment request submitted. Waiting for confirmation.\n";
                ConsoleIO::pauseSeconds(3);
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
        ConsoleIO::pauseSeconds(2);
        return;
    }

    const std::string fileFirstName = extractField(info, "First Name:");
    const std::string fileLastName = extractField(info, "Last Name:");

    if (cleaned(fileFirstName) == cleaned(firstName) &&
        cleaned(fileLastName) == cleaned(lastName)) {
        std::cout << std::endl;
        std::cout << "Login successful.\n";
        ConsoleIO::pauseSeconds(2);
        displayMenu();
    } else {
        std::cout << std::endl;
        std::cout << "Name does not match the ID.\n";
        ConsoleIO::pauseSeconds(3);
    }
}

