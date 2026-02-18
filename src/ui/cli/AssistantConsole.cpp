#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/PatientWriteService.hpp"
#include "application/usecase/AppointmentReviewService.hpp"
#include "application/usecase/UserRecordService.hpp"
#include "application/usecase/UserProvisioningService.hpp"
#include "ui/cli/UserProvisioningInputCli.hpp"
#include "ui/cli/ConsoleIO.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserProvisioningRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/Admin/Admin.hpp"

#include <iostream>
#include <limits>

namespace {
IUserRepository& userRepository() {
    static FileUserRepository repository;
    return repository;
}

UserRecordService& userRecordService() {
    static UserRecordService service(userRepository());
    return service;
}

IPatientRepository& patientRepository() {
    static FilePatientRepository repository;
    return repository;
}

PatientRecordQueryService& patientRecordQueryService() {
    static PatientRecordQueryService service(userRepository(), patientRepository());
    return service;
}

UserProvisioningService& userProvisioningService() {
    static FileUserProvisioningRepository repository;
    static UserProvisioningService service(repository);
    return service;
}

PatientWriteService& patientWriteService() {
    static PatientWriteService service(patientRepository());
    return service;
}

AppointmentReviewService& appointmentReviewService() {
    static AppointmentReviewService service(patientRepository());
    return service;
}

void runAppointmentReviewCli() {
    Result<std::vector<std::string>> requestsResult = appointmentReviewService().loadRequests();
    if (!requestsResult.ok()) {
        std::cerr << requestsResult.error().message << '\n';
        return;
    }
    std::vector<std::string> lines = requestsResult.value();

    bool changed = false;

    for (size_t i = 0; i < lines.size(); ++i) {
        std::string& entry = lines[i];

        if (AppointmentReviewService::isPending(entry)) {
            std::cout << "\n=== Appointment Request " << i + 1 << " ===\n";
            std::cout << entry << "\n";
            std::cout << "Accept (A), Reject (R), Skip (S)? ";
            char choice;
            std::cin >> choice;

            AppointmentDecision decision = AppointmentDecision::Skip;
            if (choice == 'A' || choice == 'a') {
                decision = AppointmentDecision::Accept;
            } else if (choice == 'R' || choice == 'r') {
                decision = AppointmentDecision::Reject;
            }

            const Result<AppointmentDecisionOutcome> decisionResult = appointmentReviewService().applyDecision(entry, decision);
            if (!decisionResult.ok()) {
                std::cerr << decisionResult.error().message << '\n';
                return;
            }

            if (decisionResult.value().hasError) {
                std::cerr << decisionResult.value().message << '\n';
                continue;
            }

            changed = changed || decisionResult.value().changed;
            std::cout << decisionResult.value().message << '\n';
            ConsoleIO::pauseSeconds(2);
        }
    }

    if (changed) {
        const Result<void> saveResult = appointmentReviewService().saveRequests(lines);
        if (!saveResult.ok()) {
            std::cerr << saveResult.error().message << '\n';
            return;
        }
        std::cout << "\nAppointment file updated.\n";
    } else {
        std::cout << "\nNo changes made.\n";
    }
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

// Assistant menu.
void Assistant::displayMenu() {
    int choice;
    std::string id;

    do {
        ConsoleIO::printHeader("=== Assistant Menu ===");
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName()
                  << "\nID: " << getID() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. Create New Patient" << std::endl;
        std::cout << "2. Update Field in Info\n";
        std::cout << "3. Review Appointments" << std::endl;
        std::cout << "4. Add Medications for Patient" << std::endl;
        std::cout << "5. Add Records for Patient" << std::endl;
        std::cout << "6. View Patient Info" << std::endl;
        std::cout << "7. View Patient Appointments" << std::endl;
        std::cout << "8. View Patient Medications" << std::endl;
        std::cout << "9. View Patient Records" << std::endl;
        std::cout << "10. Add Extra Info" << std::endl;
        std::cout << "0. Logout" << std::endl;
        choice = ConsoleIO::promptInt("Please enter your choice: ");

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
                ConsoleIO::pauseSeconds(1);
                return;
            case 1: {
                ConsoleIO::printHeader("Create New Patient");
                Admin::admin_getNames(firstName, lastName);
                UserProvisioningData data = UserProvisioningInputCli::promptPatientInput();
                data.firstName = firstName;
                data.lastName = lastName;
                const Result<void> createPatientResult = userProvisioningService().createPatient(data);
                if (!createPatientResult.ok()) {
                    std::cerr << createPatientResult.error().message << '\n';
                    ConsoleIO::pauseSeconds(2);
                    break;
                }
                std::cout << std::endl;
                std::cout << "Patient: [" << firstName << " " << lastName
                          << "] successfully created!" << "\n";
                ConsoleIO::pauseSeconds(2);
                break;
            }
            case 2: {
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
            case 3: {
                ConsoleIO::printHeader("Review Appointments");
                std::cout << std::endl;
                runAppointmentReviewCli();
                break;
            }
            case 4: {
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

                const Result<void> medicationResult = patientWriteService().addMedication(id, nameAndDose, frequency, startDate, endDate);
                if (!medicationResult.ok()) {
                    std::cerr << medicationResult.error().message << '\n';
                    ConsoleIO::pauseSeconds(2);
                    break;
                }

                const std::string medicationLine = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;
                std::cout << "Medication added:\n" << medicationLine << '\n';
                ConsoleIO::pauseSeconds(2);
                break;
            }
            case 5: {
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

                const Result<void> recordResult = patientWriteService().addRecord(id, date, doctor, type, content);
                if (!recordResult.ok()) {
                    std::cerr << recordResult.error().message << '\n';
                    ConsoleIO::pauseSeconds(2);
                    break;
                }

                const std::string recordLine = "[" + date + "] " + doctor + ": " + type + ": " + content;
                std::cout << "Record added:\n" << recordLine << '\n';
                ConsoleIO::pauseSeconds(2);
                break;
            }
            case 6: {
                ConsoleIO::printHeader("Patient Info");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const Result<std::vector<std::string>> infoResult = patientRecordQueryService().getPatientInfo(id);
                    if (!infoResult.ok()) {
                        std::cerr << infoResult.error().message << std::endl;
                        break;
                    }
                    std::cout << "File Content:" << std::endl;
                    ConsoleIO::printLines(infoResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 7: {
                ConsoleIO::printHeader("Patient Appointments");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const Result<std::vector<std::string>> appointmentsResult = patientRecordQueryService().getAppointments(id);
                    if (!appointmentsResult.ok()) {
                        std::cerr << appointmentsResult.error().message << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    ConsoleIO::printLines(appointmentsResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 8: {
                ConsoleIO::printHeader("Patient Medications");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const Result<std::vector<std::string>> medicationsResult = patientRecordQueryService().getMedications(id);
                    if (!medicationsResult.ok()) {
                        std::cerr << medicationsResult.error().message << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    ConsoleIO::printLines(medicationsResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 9: {
                ConsoleIO::printHeader("Patient Records");
                id = ConsoleIO::promptToken("Enter the full ID of the Patient: ");
                {
                    const Result<std::vector<std::string>> recordsResult = patientRecordQueryService().getRecords(id);
                    if (!recordsResult.ok()) {
                        std::cerr << recordsResult.error().message << std::endl;
                        break;
                    }
                    std::cout << std::endl;
                    ConsoleIO::printLines(recordsResult.value());
                    ConsoleIO::pauseSeconds(3);
                }
                break;
            }
            case 10: {
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
void Assistant::check_id_name(std::string id, std::string firstName, std::string lastName) {
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

