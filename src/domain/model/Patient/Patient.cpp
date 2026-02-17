#include "Patient.hpp"

Patient::Patient(const std::string& patient_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(patient_id, UserRole::Patient, firstName, lastName,
           "", "", "", "", "", "", "", "") {}


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






