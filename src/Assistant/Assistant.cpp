#include "Assistant.hpp"

Assistant::Assistant(const std::string& assistant_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(assistant_id, "Assistant", firstName, lastName,
           "", "", "", "", "", "", "", "") {}


// The Assistant Menu
void Assistant::displayMenu() {
    int choice;
    std::string id;

    while (true) {
        std::cout << "\n=== Assistant Menu ===" << std::endl;
        std::cout << getRole() << ": " << getFirstName() << " " << getLastName() << "\nID: " << getID() <<std::endl;
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
                Admin::admin_getNames( firstName, lastName);
                Patient p("", firstName, lastName);
                p.fill_patient_info();
                p.createNewPatient();
                std::cout << std::endl;
                std::cout << "Patient: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
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

            default:
                std::cout << "Invalid Choice." << std::endl;
                break;

        }
    }
}

// Assistant::createNewAssistant();
void Assistant::createNewAssistant() const {


    int assistant_id = Assistant_ID::get_assistant_id(); // get new Assistant ID
    std::filesystem::create_directories("data/Assistants");
    std::string folderName = std::format("data/Assistants/A{:04}", assistant_id); // Style: A0001
    std::filesystem::create_directories(folderName);


    // Full Assistant ID = A0001
    std::string assistant_full_id = std::format("A{:04}", assistant_id); // Style: A0001


    // -----------------------------------------
    // File creation for Assistant


    // Creating file with all the Infos from the Assistant
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

    // Creating file with all the Actions from the Assistant (Currently not available)
    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out( folderName + "/actions.txt");

        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";


        out.close();
    }

    // -----------------------------------------



    // -----------------------------------------
    // Update Assistant ID for new Assistant (+1)
    Assistant_ID::update_assistant_id(assistant_id); // without A
    // -----------------------------------------

}


// Checks if the Login Details are correct.
void Assistant::check_id_name(std::string id, std::string firstName, std::string lastName) {

    std::string path = "data/Assistants/" + id + "/info.txt";
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


// Prints out all the Infos from info.txt
void Assistant::get_assistant_info(const std::string &assistant_full_id) {
    const std::string path = "data/Assistants/" + assistant_full_id + "/info.txt";  // To call Assistant::get_assistant_info("A0001")
    std::ifstream file_in(path);

    if (file_in) {
        std::string line;
        std::vector<std::string> content;
        std::cout << "File Content:" << std::endl;
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;       // Output: line
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
    std::string requestFile = "data/Appointments/requests.txt";

    std::ifstream in(requestFile);
    if (!in.is_open()) {
        std::cerr << "Error: Could not open " << requestFile << "\n";
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read all requests
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    in.close();

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
                // Extract patient ID
                size_t idStart = entry.find("P");
                std::string patientID = entry.substr(idStart, 9); // Annahme: P0001

                // Extract time
                size_t bracketStart = entry.find('[');
                size_t bracketEnd = entry.find(']');
                std::string dateTime = entry.substr(bracketStart, bracketEnd - bracketStart + 1);

                // Extract doctor's name from the entry
                size_t drStart = entry.find("Dr. ");
                if (drStart == std::string::npos) {
                    std::cerr << "Doctor name not found.\n";
                    return;
                }

                // Find the position of the next " -" after "Dr. "
                size_t nameEnd = entry.find(" -", drStart);

                // Extract the substring that represents the doctor's name
                // Skip "Dr. " (4 characters), and take everything until the next " -"
                std::string doctor = entry.substr(drStart + 4, nameEnd - (drStart + 4));


                // Patient folder
                std::string path = "data/Patients/" + patientID + "/appointments.txt";
                std::filesystem::create_directories("data/Patients/" + patientID);

                std::ofstream out(path, std::ios::app);
                if (!out.is_open()) {
                    std::cerr << "Error writing to " << path << "\n";
                    continue;
                }

                out << dateTime << " - Dr. " << doctor << " (confirmed)\n";
                out.close();

                // === Anfrage aktualisieren ===
                entry.replace(entry.find("pending"), 7, "confirmed");
                changed = true;

                std::cout << "Appointment confirmed and added to patient file.\n";
            }
            else if (choice == 'R' || choice == 'r') {
                entry.replace(entry.find("pending"), 7, "rejected");
                changed = true;
                std::cout << "Appointment rejected.\n";
            }
            else {
                std::cout << "Skipped.\n";
            }
        }
    }

    // Update file
    if (changed) {
        std::ofstream out(requestFile);
        for (const auto& updated : lines) {
            out << updated << "\n";
        }
        out.close();
        std::cout << "\nAppointment file updated.\n";
    } else {
        std::cout << "\nNo changes made.\n";
    }
}


