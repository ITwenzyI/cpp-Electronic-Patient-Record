#include "infrastructure/persistence/FileUserProvisioningRepository.hpp"

#include "infrastructure/persistence/IDs/IDs.hpp"

#include <filesystem>
#include <format>
#include <fstream>
#include <string>

namespace {
void writeCommonInfo(std::ofstream& out, const UserProvisioningData& data) {
    out << "--- Personal Infos ---" << "\n";
    out << "Full Name: " << data.firstName << " " << data.lastName << "\n";
    out << "First Name: " << data.firstName << "\n";
    out << "Last Name: " << data.lastName << "\n";
    out << "Date of Birth: " << data.dateOfBirth << "\n";
    out << "Gender: " << data.gender << "\n";
    out << "Nationality: " << data.nationality << "\n";

    out << "\n" << "--- Contact Infos ---" << "\n";
    out << "Address: " << data.address << "\n";
    out << "Phone Number: " << data.phoneNumber << "\n";
    out << "Email Address: " << data.email << "\n";

    out << "\n" << "--- Insurance Infos ---" << "\n";
    out << "InsuranceID: " << data.insuranceID << "\n";
    out << "InsuranceType: " << data.insuranceType << "\n";

    out << "\n" << "--- Extra Infos ---" << "\n";
}
} // namespace

bool FileUserProvisioningRepository::createPatient(const UserProvisioningData& data) {
    const int patientId = Patient_ID::get_patient_id();
    std::filesystem::create_directories("data/Patients");
    const std::string folderName = std::format("data/Patients/P{:08}", patientId);
    std::filesystem::create_directories(folderName);
    const std::string patientFullId = std::format("P{:08}", patientId);

    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out(folderName + "/info.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "PatientID: " << patientFullId << "\n\n";
        writeCommonInfo(out, data);
    }

    if (!std::filesystem::exists(folderName + "/records.txt")) {
        std::ofstream out(folderName + "/records.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "--- Records ---" << "\n";
    }

    if (!std::filesystem::exists(folderName + "/appointments.txt")) {
        std::ofstream out(folderName + "/appointments.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "--- Appointments ---" << "\n";
    }

    if (!std::filesystem::exists(folderName + "/medications.txt")) {
        std::ofstream out(folderName + "/medications.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "--- Medications ---" << "\n";
    }

    Patient_ID::update_patient_id(patientId);
    return true;
}

bool FileUserProvisioningRepository::createDoctor(const UserProvisioningData& data) {
    const int doctorId = Doctor_ID::get_doctor_id();
    std::filesystem::create_directories("data/Doctors");
    const std::string folderName = std::format("data/Doctors/D{:04}", doctorId);
    std::filesystem::create_directories(folderName);

    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out(folderName + "/info.txt");
        if (!out.is_open()) {
            return false;
        }
        writeCommonInfo(out, data);
    }

    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out(folderName + "/actions.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";
    }

    if (!std::filesystem::exists(folderName + "/patients_seen.txt")) {
        std::ofstream out(folderName + "/patients_seen.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08] P00000013 - Follow-up appointment aftercare" << "\n";
    }

    Doctor_ID::update_doctor_id(doctorId);
    return true;
}

bool FileUserProvisioningRepository::createAssistant(const UserProvisioningData& data) {
    const int assistantId = Assistant_ID::get_assistant_id();
    std::filesystem::create_directories("data/Assistants");
    const std::string folderName = std::format("data/Assistants/A{:04}", assistantId);
    std::filesystem::create_directories(folderName);

    if (!std::filesystem::exists(folderName + "/info.txt")) {
        std::ofstream out(folderName + "/info.txt");
        if (!out.is_open()) {
            return false;
        }
        writeCommonInfo(out, data);
    }

    if (!std::filesystem::exists(folderName + "/actions.txt")) {
        std::ofstream out(folderName + "/actions.txt");
        if (!out.is_open()) {
            return false;
        }
        out << "\n" << "--- Example ---" << "\n";
        out << "\n" << "[2025-06-08 10:03] Created patient P00000012" << "\n";
    }

    Assistant_ID::update_assistant_id(assistantId);
    return true;
}
