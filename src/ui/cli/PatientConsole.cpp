#include "domain/model/Patient/Patient.hpp"

#include <chrono>
#include <iostream>
#include <thread>

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
                get_patient_appointments(id);
                break;
            }
            case 2: {
                std::cout << std::endl;
                std::cout << "Medications\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                get_patient_medications(id);
                break;
            }
            case 3: {
                std::cout << std::endl;
                std::cout << "Records\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                get_patient_records(id);
                break;
            }
            case 4: {
                std::cout << std::endl;
                std::cout << "Book Appointment\n";
                std::cout << "Enter your full ID: ";
                std::cin >> id;
                request_appointment(id);
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
    std::string path = "data/Patients/" + id + "/info.txt";
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
void Patient::get_patient_info(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/info.txt";
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
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
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

// Add new appointments to appointments.txt.
void Patient::add_patient_appointment(const std::string &patient_full_id) {
    std::string date, time, doctorName, reason;

    std::cout << "Enter appointment date (YYYY-MM-DD): ";
    std::getline(std::cin >> std::ws, date);
    std::cout << std::endl;
    std::cout << "Enter appointment time (HH:MM): ";
    std::getline(std::cin, time);
    std::cout << std::endl;
    std::cout << "Enter doctor name: ";
    std::getline(std::cin, doctorName);
    std::cout << std::endl;
    std::cout << "Enter reason for appointment: ";
    std::getline(std::cin, reason);
    std::cout << std::endl;

    std::string appointmentLine = "[" + date + " " + time + "] - " + doctorName + " (" + reason + ")";
    std::string filePath = "data/Patients/" + patient_full_id + "/appointments.txt";

    std::ofstream out(filePath, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Could not open appointment file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    out << appointmentLine << '\n';
    out.close();

    std::cout << "Appointment added:\n" << appointmentLine << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Add new medications to medications.txt.
void Patient::add_patient_medication(const std::string &patient_full_id) {
    std::string nameAndDose, frequency, startDate, endDate;

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

    std::string medicationLine = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;
    std::string filePath = "data/Patients/" + patient_full_id + "/medications.txt";

    std::ofstream out(filePath, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Could not open medication file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    out << medicationLine << '\n';
    out.close();

    std::cout << "Medication added:\n" << medicationLine << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Add new records to records.txt.
void Patient::add_patient_record(const std::string &patient_full_id) {
    std::string date, doctor, type, content;

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

    std::string recordLine = "[" + date + "] " + doctor + ": " + type + ": " + content;
    std::string filePath = "data/Patients/" + patient_full_id + "/records.txt";

    std::ofstream out(filePath, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Could not open records file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    out << recordLine << '\n';
    out.close();

    std::cout << "Record added:\n" << recordLine << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Prints all appointments from patient file.
void Patient::get_patient_appointments(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/appointments.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;
            content.push_back(line);
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

// Prints all medications from patient file.
void Patient::get_patient_medications(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/medications.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;
            content.push_back(line);
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

// Prints all records from patient file.
void Patient::get_patient_records(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/records.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;
            content.push_back(line);
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}

void Patient::request_appointment(const std::string &patient_full_id) {
    std::string date, time, doctorName, reason;

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

    std::filesystem::create_directories("data/Appointments");
    std::string filePath = "data/Appointments/requests.txt";
    std::ofstream out(filePath, std::ios::app);

    if (!out.is_open()) {
        std::cerr << "Error: could not open " << filePath << "\n";
        return;
    }

    out << "[" << date << " " << time << "] - "
        << patient_full_id << " - Dr. " << doctorName;

    if (!reason.empty()) {
        out << " - Reason: " << reason;
    }

    out << " - Status: pending\n";
    out.close();

    std::cout << std::endl;
    std::cout << "Appointment request submitted. Waiting for confirmation.\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
}
