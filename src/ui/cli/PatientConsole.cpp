#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/PatientWriteService.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/ConsoleIO.hpp"
#include "ui/cli/PatientMenuController.hpp"

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
} // namespace

void runPatientMenu(Patient& patient) {
    int choice;
    std::string id;

    do {
        ConsoleIO::printHeader("=== Patient Menu ===");
        std::cout << patient.getRole() << ": " << patient.getFirstName() << " "
                  << patient.getLastName() << "\nID: " << patient.getID() << std::endl;
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
                    const Result<std::vector<std::string>> appointmentsResult =
                        patientRecordQueryService().getAppointments(id);
                    if (!appointmentsResult) {
                        ConsoleIO::printError(appointmentsResult.error());
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
                    const Result<std::vector<std::string>> medicationsResult =
                        patientRecordQueryService().getMedications(id);
                    if (!medicationsResult) {
                        ConsoleIO::printError(medicationsResult.error());
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
                    const Result<std::vector<std::string>> recordsResult =
                        patientRecordQueryService().getRecords(id);
                    if (!recordsResult) {
                        ConsoleIO::printError(recordsResult.error());
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

                const Result<void> requestResult =
                    patientWriteService().requestAppointment(id, date, time, doctorName, reason);
                if (!requestResult) {
                    ConsoleIO::printError(requestResult.error());
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
