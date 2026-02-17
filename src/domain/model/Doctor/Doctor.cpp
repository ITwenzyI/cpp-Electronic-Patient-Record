#include "Doctor.hpp"

Doctor::Doctor(const std::string& doctor_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(doctor_id, UserRole::Doctor, firstName, lastName,
           "", "", "", "", "", "", "", "") {}


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




