#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/PatientWriteService.hpp"
#include "application/usecase/UserRecordService.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/ConsoleIO.hpp"

#include <iostream>
#include <limits>

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

UserRecordService& userRecordService() {
    static UserRecordService service(userRepository());
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

// Doctor menu.
void Doctor::displayMenu() {
    int choice;
    std::string id;

    do {
        ConsoleIO::printHeader("=== Doctor Menu ===");
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName()
                  << "\nID: " << getID() << std::endl;
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
        choice = ConsoleIO::promptInt("Please enter your choice: ");

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
                ConsoleIO::pauseSeconds(3);
                return;
            case 1: {
                std::string nameAndDose, frequency, startDate, endDate;
                ConsoleIO::printHeader("Add Medication");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                std::cout << "Enter medication name and dosage (Example: Ibuprofen 400 mg): ";
                std::getline(std::cin >> std::ws, nameAndDose);
                std::cout << std::endl;
                std::cout << "Enter intake frequency (Example: 3x daily): ";
                std::getline(std::cin, frequency);
                std::cout << std::endl;
                std::cout << "Enter start date (YYYY-MM-DD): ";
                std::getline(std::cin, startDate);
                std::cout << std::endl;
                std::cout << "Enter end date (YYYY-MM-DD): ";
                std::getline(std::cin, endDate);
                std::cout << std::endl;

                if (!patientWriteService().addMedication(id, nameAndDose, frequency, startDate, endDate)) {
                    std::cerr << "Could not open medication file for writing.\n";
                    ConsoleIO::pauseSeconds(2);
                    break;
                }

                const std::string medicationLine = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;
                std::cout << "Medication added:\n" << medicationLine << '\n';
                ConsoleIO::pauseSeconds(2);
                break;
            }
            case 2: {
                std::string date, doctor, type, content;
                ConsoleIO::printHeader("Add Records");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                std::cout << "Enter date of record (YYYY-MM-DD): ";
                std::getline(std::cin >> std::ws, date);
                std::cout << std::endl;
                std::cout << "Enter doctor name: ";
                std::getline(std::cin, doctor);
                std::cout << std::endl;
                std::cout << "Enter type of record: ";
                std::getline(std::cin, type);
                std::cout << std::endl;
                std::cout << "Enter record details/notes: ";
                std::getline(std::cin, content);
                std::cout << std::endl;

                if (!patientWriteService().addRecord(id, date, doctor, type, content)) {
                    std::cerr << "Could not open records file for writing.\n";
                    ConsoleIO::pauseSeconds(2);
                    break;
                }

                const std::string recordLine = "[" + date + "] " + doctor + ": " + type + ": " + content;
                std::cout << "Record added:\n" << recordLine << '\n';
                ConsoleIO::pauseSeconds(2);
                break;
            }
            case 3: {
                ConsoleIO::printHeader("Patient Info");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const std::vector<std::string> info = patientRecordQueryService().getPatientInfo(id);
                    if (info.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }
                    std::cout << "File Content:" << std::endl;
                    ConsoleIO::printLines(info);
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 4: {
                ConsoleIO::printHeader("Patient Appointments");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const std::vector<std::string> appointments = patientRecordQueryService().getAppointments(id);
                    if (appointments.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    ConsoleIO::printLines(appointments);
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 5: {
                ConsoleIO::printHeader("Patient Medications");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const std::vector<std::string> medications = patientRecordQueryService().getMedications(id);
                    if (medications.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    ConsoleIO::printLines(medications);
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 6: {
                ConsoleIO::printHeader("Patient Records");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const std::vector<std::string> records = patientRecordQueryService().getRecords(id);
                    if (records.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    ConsoleIO::printLines(records);
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 7: {
                std::string field, newInput;
                ConsoleIO::printHeader("Update Field in File");
                id = ConsoleIO::promptToken("Enter full ID: ");
                std::cout << std::endl;
                field = ConsoleIO::promptToken("Enter Field: ");
                std::cout << std::endl;
                newInput = ConsoleIO::promptToken("Enter New Input: ");
                std::cout << std::endl;
                const Result<void> updateResult = userRecordService().updateFieldInFile(id, field, newInput);
                if (!updateResult.ok()) {
                    std::cerr << updateResult.error().message << '\n';
                    ConsoleIO::pauseSeconds(2);
                    break;
                }
                std::cout << field << " successfully updated.\n";
                ConsoleIO::pauseSeconds(2);
                break;
            }
            case 8: {
                std::string extraInfo;
                ConsoleIO::printHeader("Add Extra Info");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                std::cout << "ID: " << id << std::endl;
                std::cout << "Enter the Extra Info: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, extraInfo);
                std::cout << std::endl;

                const Result<void> extraInfoResult = userRecordService().addExtraInfo(id, extraInfo);
                if (!extraInfoResult.ok()) {
                    std::cerr << extraInfoResult.error().message << '\n';
                    ConsoleIO::pauseSeconds(2);
                    break;
                }

                const std::string newLine = "[" + getDate() + "] " + extraInfo + "\n";
                std::cout << "Extra Info added:\n" << newLine << '\n';
                ConsoleIO::pauseSeconds(2);
                break;
            }
            default:
                std::cout << "Invalid Choice." << std::endl;
                break;
        }
    } while (choice != 0);
}

// Checks if login details are correct.
void Doctor::check_id_name(std::string id, std::string firstName, std::string lastName) {
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

