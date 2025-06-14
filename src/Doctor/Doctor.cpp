#include "Doctor.hpp"

Doctor::Doctor(const std::string& doctor_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(doctor_id, "Doctor", firstName, lastName,
           "", "", "", "", "", "", "", "") {}


// The Doctor Menu
void Doctor::displayMenu() {
    int choice;
    std::string id;

    while (true) {
        std::cout << "\n=== Doctor Menu ===" << std::endl;
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() <<std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "1. Add Medications for Patient" << std::endl;
        std::cout << "2. Add Records for Patient" << std::endl;
        std::cout << "3. View Patient Info" << std::endl;
        std::cout << "4. View Patient Appointments" << std::endl;
        std::cout << "5. View Patient Medications" << std::endl;
        std::cout << "6. View Patient Records" << std::endl;
        std::cout << "7. Update Field in Info\n";
        std::cout << "0. Logout" << std::endl;
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 0:
                std::cout << "Logging out..." << std::endl;
                return;

            case 1: {
                std::cout << std::endl;
                std::cout << "Add Medication\n";
                std::cout << "Enter the full ID of the Patient: ";
                Patient::add_patient_medication(id);
                break;
            }

            case 2: {
                std::cout << std::endl;
                std::cout << "Add Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                Patient::add_patient_record(id);
                break;
            }

            case 3: {
                std::cout << std::endl;
                std::cout << "Patient Info\n";
                std::cout << "Enter the full ID of the Patient: ";
                Patient::get_patient_info(id);
                break;
            }

            case 4: {
                std::cout << std::endl;
                std::cout << "Patient Appointments\n";
                std::cout << "Enter the full ID of the Patient: ";
                Patient::get_patient_appointments(id);
                break;
            }

            case 5: {
                std::cout << std::endl;
                std::cout << "Patient Medications\n";
                std::cout << "Enter the full ID of the Patient: ";
                Patient::get_patient_medications(id);
                break;
            }

            case 6: {
                std::cout << std::endl;
                std::cout << "Patient Records\n";
                std::cout << "Enter the full ID of the Patient: ";
                Patient::get_patient_records(id);
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
                update_field_in_file(id, field, newInput);
                break;
            }

            default:
                std::cout << "Invalid Choice." << std::endl;
                break;

        }
    }
}


// Checks if the Login Details are correct.
void Doctor::check_id_name(std::string id, std::string firstName, std::string lastName) {

    std::string path = "data/Doctors/" + id + "/info.txt";
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


// Creates new Doctor
void Doctor::createNewDoctor() const{


    int doctor_id = Doctor_ID::get_doctor_id(); // get new Doctor ID
    std::filesystem::create_directories("data/Doctors");
    std::string folderName = std::format("data/Doctors/D{:04}", doctor_id); // Style: D0001
    std::filesystem::create_directories(folderName);


    // Full Doctor ID = D0001
    std::string doctor_full_id = std::format("D{:04}", doctor_id); // Style: D0001


    // -----------------------------------------
    // File creation for Doctor


    // Creating file with all the Infos from the Doctor
    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out( folderName + "/info.txt");
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

    // Creating file with all the Actions from the Doctor (currently not available)
    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out( folderName + "/actions.txt");
        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";


        out.close();
    }

    // Creating file with all the Patients seen from the Doctor (currently not available)
    if (!std::filesystem::exists(folderName + "/patients_seen.txt")) {
        std::ofstream out( folderName + "/patients_seen.txt");
        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08] P00000013 - Follow-up appointment aftercare" << "\n";


        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Doctor ID for new Doctor (+1)
    Doctor_ID::update_doctor_id(doctor_id); // without D
    // -----------------------------------------


}


// Prints out all the Infos from info.txt
void Doctor::get_doctor_info(const std::string &doctor_full_id) {
    const std::string path = "data/Doctors/" + doctor_full_id + "/info.txt";  // To call Doctor::get_doctor_info("D0001")
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << "File Content:" << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Output: line
            content.push_back(line);               // safe line in vector
        }
        file_in.close();
    } else {
        std::cerr << "Failed to read file!" << std::endl;
    }
}


// Gets all the Infos for info.txt
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


