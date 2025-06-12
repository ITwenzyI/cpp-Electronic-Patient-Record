
#include "Doctor.hpp"

Doctor::Doctor(const std::string& doctor_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(doctor_id, "Doctor", firstName, lastName,
           "", "", "", "", "", "", "", "") {}


void Doctor::displayMenu() {
    int choice;

    do {
        std::cout << "\n=== Doctor Menu ===" << std::endl;
        std::cout << "1. View Medical Records" << std::endl;
        std::cout << "2. View Documents" << std::endl;
        std::cout << "3. View open Appointments" << std::endl;
        std::cout << "4. View Calender" << std::endl;
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

void Doctor::check_id_name(std::string id, std::string firstName, std::string lastName) {

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

void Doctor::createNewDoctor(const std::string& firstName, const std::string& lastName) {


    int doctor_id = Doctor_ID::get_doctor_id(); // get new Doctor ID
    std::filesystem::create_directories("data/Doctors");
    std::string folderName = "data/Doctors/D" + std::string(4 - std::to_string(doctor_id).length(), '0') + std::to_string(doctor_id); // Style: D0001
    std::filesystem::create_directories(folderName);


    // Full Doctor ID = D0001
    std::string doctor_full_id = "D" + std::string(4 - std::to_string(doctor_id).length(), '0') + std::to_string(doctor_id);


    // -----------------------------------------
    // File creation for Doctor


    // Creating file with all the Infos from the Doctor
    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out( folderName + "/info.txt");
        out << "PatientID: " << doctor_full_id << "\n\n"; // DoctorID
        out << "--- Personal Infos ---"  << "\n";
        out << "Full Name: " << firstName << " " << lastName << "\n";
        out << "First Name: " << firstName << "\n"; // First Name
        out << "Last Name: " << lastName << "\n"; // Last Name
        out << "Date of Birth: " << lastName << "\n";
        out << "Gender: " << lastName << "\n";
        out << "Nationality: " << lastName << "\n";

        out << "\n" << "--- Contact Infos ---"  << "\n";
        out << "Adress: " << lastName << "\n";
        out << "Phone Number: " << lastName << "\n";
        out << "Email Adress: " << lastName << "\n";

        out << "\n" << "--- Insurance Infos ---"  << "\n";
        out << "InsuranceID: " << lastName << "\n";
        out << "InsuranceType: " << lastName << "\n";

        out << "\n" << "--- Extra Infos ---"  << "\n";


        out.close();
    }

    // Creating file with all the Actions from the Doctor
    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out( folderName + "/actions.txt");
        out << "DoctorID: " << doctor_full_id << "\n\n"; // DoctorID

        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";


        out.close();
    }

    // Creating file with all the Patients seen from the Doctor
    if (!std::filesystem::exists(folderName + "/patients_seen.txt")) {
        std::ofstream out( folderName + "/patients_seen.txt");
        out << "DoctorID: " << doctor_full_id << "\n\n"; // DoctorID

        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08] P00000013 - Follow-up appointment aftercare" << "\n";


        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Doctor ID for new Doctor (+1)
    Doctor_ID::update_doctor_id(doctor_id);
    // -----------------------------------------


}

void Doctor::get_doctor_info(const std::string &doctor_full_id) {
    std::string path = "data/Doctors/" + doctor_full_id + "/info.txt";  // To call Doctor::get_doctor_info("D0001")
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


