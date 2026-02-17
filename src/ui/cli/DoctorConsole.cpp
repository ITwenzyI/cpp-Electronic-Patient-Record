#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/UserRecordService.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"

#include <chrono>
#include <iostream>
#include <limits>
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

UserRecordService& userRecordService() {
    static UserRecordService service(userRepository());
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
        std::cout << "\n=== Doctor Menu ===" << std::endl;
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
            case 4: {
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
            case 5: {
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
            case 6: {
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
                if (!userRecordService().updateFieldInFile(id, field, newInput)) {
                    std::cerr << "Could not update field in file.\n";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                std::cout << field << " successfully updated.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            case 8: {
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
void Doctor::check_id_name(std::string id, std::string firstName, std::string lastName) {
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

// Prints all info from info.txt.
void Doctor::get_doctor_info(const std::string& doctor_full_id) {
    const std::vector<std::string> info = userRepository().readInfo(doctor_full_id);
    if (info.empty()) {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }

    std::cout << "File Content:" << std::endl;
    for (const auto& line : info) {
        std::cout << line << std::endl;
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
