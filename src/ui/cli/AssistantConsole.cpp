#include "domain/model/Assistant/Assistant.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/Admin/Admin.hpp"

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
                Patient p("", firstName, lastName);
                p.fill_patient_info();
                p.createNewPatient();
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
                update_field_in_file(id, field, newInput);
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
                std::cout << std::endl;
                std::cout << "Add Medication\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::add_patient_medication(id);
                break;
            }
            case 5: {
                std::cout << std::endl;
                std::cout << "Add Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::add_patient_record(id);
                break;
            }
            case 6: {
                std::cout << std::endl;
                std::cout << "Patient Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_info(id);
                break;
            }
            case 7: {
                std::cout << std::endl;
                std::cout << "Patient Appointments\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_appointments(id);
                break;
            }
            case 8: {
                std::cout << std::endl;
                std::cout << "Patient Medications\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_medications(id);
                break;
            }
            case 9: {
                std::cout << std::endl;
                std::cout << "Patient Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                Patient::get_patient_records(id);
                break;
            }
            case 10: {
                std::cout << std::endl;
                std::cout << "Add Extra Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                std::cin >> id;
                add_extra_info(id);
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

// Prints all infos from info.txt.
void Assistant::get_assistant_info(const std::string& assistant_full_id) {
    const std::vector<std::string> info = userRepository().readInfo(assistant_full_id);
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

// Gets all infos for info.txt.
void Assistant::fill_assistant_info() {
    std::cout << "\nPlease provide all the Infos from the Assistant!\n" << std::endl;
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
