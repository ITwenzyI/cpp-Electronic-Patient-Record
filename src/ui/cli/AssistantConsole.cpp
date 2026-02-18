#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/PatientWriteService.hpp"
#include "application/usecase/UserRecordService.hpp"
#include "application/usecase/UserProvisioningService.hpp"
#include "ui/cli/UserProvisioningInputCli.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserProvisioningRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/Admin/Admin.hpp"

#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

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
        std::cout << "\n=== Assistant Menu ===" << std::endl;
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
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            case 1: {
                std::cout << std::endl;
                std::cout << "Create New Patient\n";
                Admin::admin_getNames(firstName, lastName);
                UserProvisioningData data = UserProvisioningInputCli::promptPatientInput();
                data.firstName = firstName;
                data.lastName = lastName;
                userProvisioningService().createPatient(data);
                std::cout << std::endl;
                std::cout << "Patient: [" << firstName << " " << lastName
                          << "] successfully created!" << "\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            case 2: {
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
                if (!userRecordService().updateFieldInFile(id, field, newInput)) {
                    std::cerr << "Could not update field in file.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                std::cout << field << " successfully updated.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            case 3: {
                std::cout << std::endl;
                std::cout << "Review Appointments\n";
                std::cout << std::endl;
                review_appointments();
                break;
            }
            case 4: {
                std::string nameAndDose, frequency, startDate, endDate;
                std::cout << std::endl;
                std::cout << "Add Medication\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
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
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }

                const std::string medicationLine = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;
                std::cout << "Medication added:\n" << medicationLine << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            case 5: {
                std::string date, doctor, type, content;
                std::cout << std::endl;
                std::cout << "Add Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
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
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }

                const std::string recordLine = "[" + date + "] " + doctor + ": " + type + ": " + content;
                std::cout << "Record added:\n" << recordLine << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            case 6: {
                std::cout << std::endl;
                std::cout << "Patient Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                {
                    const std::vector<std::string> info = patientRecordQueryService().getPatientInfo(id);
                    if (info.empty()) {
                        std::cerr << "Failed to read file!" << std::endl;
                        break;
                    }
                    std::cout << "File Content:" << std::endl;
                    for (const auto& line : info) {
                        std::cout << line << std::endl;
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
                break;
            }
            case 7: {
                std::cout << std::endl;
                std::cout << "Patient Appointments\n";
                std::cout << "Enter the full ID of the Patient: ";
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
            case 8: {
                std::cout << std::endl;
                std::cout << "Patient Medications\n";
                std::cout << "Enter the full ID of the Patient: ";
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
            case 9: {
                std::cout << std::endl;
                std::cout << "Patient Records\n";
                std::cout << "Enter the full ID of the Patient: ";
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
            case 10: {
                std::string extraInfo;
                std::cout << std::endl;
                std::cout << "Add Extra Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                std::cout << "ID: " << id << std::endl;
                std::cout << "Enter the Extra Info: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, extraInfo);
                std::cout << std::endl;

                if (!userRecordService().addExtraInfo(id, extraInfo)) {
                    std::cerr << "Could not open file for writing.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }

                const std::string newLine = "[" + getDate() + "] " + extraInfo + "\n";
                std::cout << "Extra Info added:\n" << newLine << '\n';
                std::this_thread::sleep_for(std::chrono::seconds(2));
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

void Assistant::review_appointments() {
    std::vector<std::string> lines = patientRepository().readAppointmentRequests();
    if (!patientRepository().appointmentRequestsExists()) {
        std::cerr << "Error: Could not open data/Appointments/requests.txt\n";
        return;
    }

    bool changed = false;

    for (size_t i = 0; i < lines.size(); ++i) {
        std::string& entry = lines[i];

        if (entry.find("Status: pending") != std::string::npos) {
            std::cout << "\n=== Appointment Request " << i + 1 << " ===\n";
            std::cout << entry << "\n";
            std::cout << "Accept (A), Reject (R), Skip (S)? ";
            char choice;
            std::cin >> choice;

            if (choice == 'A' || choice == 'a') {
                size_t idStart = entry.find("P");
                std::string patientID = entry.substr(idStart, 9);

                size_t bracketStart = entry.find('[');
                size_t bracketEnd = entry.find(']');
                std::string dateTime = entry.substr(bracketStart, bracketEnd - bracketStart + 1);

                size_t drStart = entry.find("Dr. ");
                if (drStart == std::string::npos) {
                    std::cerr << "Doctor name not found.\n";
                    return;
                }

                size_t nameEnd = entry.find(" -", drStart);
                std::string doctor = entry.substr(drStart + 4, nameEnd - (drStart + 4));

                if (!patientRepository().ensurePatientDirectory(patientID) ||
                    !patientRepository().appendAppointment(patientID, dateTime + " - Dr. " + doctor + " (confirmed)")) {
                    std::cerr << "Error writing to data/Patients/" << patientID << "/appointments.txt\n";
                    continue;
                }

                entry.replace(entry.find("pending"), 7, "confirmed");
                changed = true;

                std::cout << "Appointment confirmed and added to patient file.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
            } else if (choice == 'R' || choice == 'r') {
                entry.replace(entry.find("pending"), 7, "rejected");
                changed = true;
                std::cout << "Appointment rejected.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
            } else {
                std::cout << "Skipped.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    }

    if (changed) {
        if (!patientRepository().writeAppointmentRequests(lines)) {
            std::cerr << "\nFailed to update appointment file.\n";
            return;
        }
        std::cout << "\nAppointment file updated.\n";
    } else {
        std::cout << "\nNo changes made.\n";
    }
}
