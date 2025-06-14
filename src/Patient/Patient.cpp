#include "Patient.hpp"

Patient::Patient(const std::string& patient_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(patient_id, "Patient", firstName, lastName,
           "", "", "", "", "", "", "", "") {}


void Patient::displayMenu() {
    int choice;

    do {
        std::cout << "\n=== Patient Menu ===" << std::endl;
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() <<std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. View Medical Record" << std::endl;
        std::cout << "2. View Documents" << std::endl;
        std::cout << "3. Book Appointment" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cin >> choice;

        switch (choice) {
                case 0:
                std::cout << "Logging out..." << std::endl;
                case 1:
                break;
                case 2:
                break;
                case 3:
                break;
                default:
                std::cout << "Invalid Choice." << std::endl;
                break;

        }



    } while (choice != 0);
}

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
            displayMenu();
            }
        else {
            std::cout << std::endl;
            std::cout << "Name does not match the ID.\n";
        }
    } else {
        std::cout << std::endl;
        std::cerr << "Failed to read file!" << std::endl;
    }
    displayMenu();
}

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
        out << "--- Example ---" << patient_full_id << "\n"; // PatientID P00000001
        out << "[2025-06-08] Dr. Schmitt: Blood pressure too high, recommended: Exercise & diet." << "\n"; // Example
        out << "[2025-06-15] Dr. Schmitt: Control: blood pressure decreased, no medication necessary." << "\n"; // Example
        out.close();
    }

    // Creating file with a list of all appointments from the Patient
    if (!std::filesystem::exists(folderName + "/appointments.txt")) {
        std::ofstream out( folderName + "/appointments.txt");
        out << "--- Example ---" << patient_full_id << "\n"; // PatientID P00000001
        out << "[2025-06-12 09:30] – Dr. Schmitt" << "\n"; // Example
        out << "[2025-06-13 14:00] - Dr. Meier (control)" << "\n"; // Example
        out.close();
    }

    // Creating file with all the medications the Patient needs
    if (!std::filesystem::exists(folderName + "/medications.txt")) {
        std::ofstream out( folderName + "/medication.txt");
        out << "--- Example ---" << patient_full_id << "\n"; // PatientID P00000001
        out << "Ibuprofen 400 mg - 3x daily - from 2025-06-08 to 2025-06-12" << "\n"; // Example
        out << "Ramipril 5 mg – 1x daily in the morning - permanently" << "\n"; // Example
        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Patient ID for new Patient (+1)
    Patient_ID::update_patient_id(patient_id); // without P
    // -----------------------------------------


}

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
    }
}
