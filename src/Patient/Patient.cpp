#include "Patient.hpp"

Patient::Patient(const std::string& patient_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(patient_id, "Patient", firstName, lastName,
           "", "", "", "", "", "", "", "") {}


// Patient Menu
void Patient::displayMenu() {
    int choice;
    std::string id;

    while (true) {

        std::cout << "\n=== Patient Menu ===" << std::endl;
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() <<std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. View Appointments" << std::endl;
        std::cout << "2. View Medications" << std::endl;
        std::cout << "3. View Records" << std::endl;
        //std::cout << "4. Book Appointment" << std::endl;
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

            default:
                std::cout << "Invalid Choice." << std::endl;
                break;

        }

    }
}


// Checks if the Login Details are correct.
void Patient::check_id_name(std::string id, std::string firstName, std::string lastName) {

    std::string path = "data/Patients/" + id + "/info.txt";
    std::ifstream file_in(path);
    std::vector<std::string> content;

    if (file_in) {
        std::string line;
        std::string fileFirstName, fileLastName;
        while (std::getline(file_in, line)) {
            if (line.starts_with("First Name:")) {
                fileFirstName = line.substr(11);  // all after "First Name:"
            } else if (line.starts_with("Last Name:")) {
                fileLastName = line.substr(10);    // all after "Last Name:"
            }
        }
        file_in.close();



        if (cleaned(fileFirstName) == cleaned(firstName) &&
            cleaned(fileLastName) == cleaned(lastName)) {
            std::cout << std::endl;
            std::cout << "Login successful.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            displayMenu();
            }
        else {
            std::cout << std::endl;
            std::cout << "Name does not match the ID.\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            return;
        }
    } else {
        std::cout << std::endl;
        std::cerr << "Failed to read file!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    displayMenu();
}


// Creates New Patient for Assistant
void Patient::createNewPatient() const{


    int patient_id = Patient_ID::get_patient_id(); // get new Patient ID
    std::filesystem::create_directories("data/Patients");
    std::string folderName = std::format("data/Patients/P{:08}", patient_id); // Style: P00000001
    std::filesystem::create_directories(folderName);


    // Full Patient ID = P00000001
    std::string patient_full_id = std::format("P{:08}", patient_id);


    // -----------------------------------------
    // File creation for Patient


    // Creating file with all the Infos from the Patient
    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out( folderName + "/info.txt");
        out << "PatientID: " << patient_full_id << "\n\n"; // PatientID P00000001
        out << "--- Personal Infos ---"  << "\n";
        out << "Full Name: " << firstName << " " << lastName << "\n";
        out << "First Name: " << firstName << "\n"; // First Name
        out << "Last Name: " << lastName << "\n"; // Last Name
        out << "Date of Birth: " << dateOfBirth << "\n";
        out << "Gender: " << gender << "\n";
        out << "Nationality: " << nationality << "\n";

        out << "\n" << "--- Contact Infos ---"  << "\n";
        out << "Address: " << address << "\n";
        out << "Phone Number: " << phoneNumber << "\n";
        out << "Email Address: " << email << "\n";

        out << "\n" << "--- Insurance Infos ---"  << "\n";
        out << "InsuranceID: " << insuranceID << "\n";
        out << "InsuranceType: " << insuranceType << "\n";

        out << "\n" << "--- Extra Infos ---"  << "\n";


        out.close();
    }

    // Creating file with a list of all the records from the Patient
    if (!std::filesystem::exists(folderName + "/records.txt")) {
        std::ofstream out( folderName + "/records.txt");
        out << "--- Records ---" << "\n"; // PatientID P00000001
        out.close();
    }

    // Creating file with a list of all appointments from the Patient
    if (!std::filesystem::exists(folderName + "/appointments.txt")) {
        std::ofstream out( folderName + "/appointments.txt");
        out << "--- Appointments ---" << "\n"; // PatientID P00000001
        out.close();
    }

    // Creating file with all the medications the Patient needs
    if (!std::filesystem::exists(folderName + "/medications.txt")) {
        std::ofstream out( folderName + "/medications.txt");
        out << "--- Medications ---" << "\n"; // PatientID P00000001
        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Patient ID for new Patient (+1)
    Patient_ID::update_patient_id(patient_id); // without P
    // -----------------------------------------


}


// Prints out all the Infos from info.txt
void Patient::get_patient_info(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/info.txt"; // To call: Patient::get_patient_info("P00000006");
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << "File Content:" << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Output: line
            content.push_back(line);                // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}


// Gets all the Infos for info.txt
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


// Add new Appointments to appointments.txt
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

    // Final format: [2025-06-13 14:00] - Dr. Meier (control)
    std::string appointmentLine = "[" + date + " " + time + "] - " + doctorName + " (" + reason + ")";

    std::string filePath = "data/Patients/" + patient_full_id + "/appointments.txt";
    std::ofstream out(filePath, std::ios::app);  // append mode
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


// Add new medications to medications.txt
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

    // Final format: Ibuprofen 400 mg - 3x daily - from 2025-06-08 to 2025-06-12
    std::string medicationLine = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;

    std::string filePath = "data/Patients/" + patient_full_id + "/medications.txt";
    std::ofstream out(filePath, std::ios::app);  // append mode

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


// Add new Records to records.txt
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

    // Final format: [2025-06-15] Dr. Schmitt: Control: blood pressure decreased, no medication necessary.
    std::string recordLine = "[" + date + "] " + doctor + ": " + type + ": " + content;

    std::string filePath = "data/Patients/" + patient_full_id + "/records.txt";
    std::ofstream out(filePath, std::ios::app);  // append mode

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


// Prints out all the appointments from the Patient
void Patient::get_patient_appointments(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/appointments.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Output: line
            content.push_back(line);                // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}


// Prints out all the Medications from the Patient
void Patient::get_patient_medications(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/medications.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Output: line
            content.push_back(line);                // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}


// Print out all the Records from the Patient
void Patient::get_patient_records(const std::string &patient_full_id) {
    const std::string path = "data/Patients/" + patient_full_id + "/records.txt";
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Output: line
            content.push_back(line);                // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
}




