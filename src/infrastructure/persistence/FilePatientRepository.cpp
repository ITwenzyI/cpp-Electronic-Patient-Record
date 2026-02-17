#include "infrastructure/persistence/FilePatientRepository.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {
std::string patientFilePath(const std::string& patientId, const std::string& filename) {
    return "data/Patients/" + patientId + "/" + filename;
}

std::string appointmentRequestsPath() {
    return "data/Appointments/requests.txt";
}

std::vector<std::string> readLines(const std::string& path) {
    std::vector<std::string> lines;
    std::ifstream in(path);
    if (!in.is_open()) {
        return lines;
    }

    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    return lines;
}

bool appendLine(const std::string& path, const std::string& line) {
    std::ofstream out(path, std::ios::app);
    if (!out.is_open()) {
        return false;
    }

    out << line << '\n';
    return true;
}

bool writeLines(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream out(path);
    if (!out.is_open()) {
        return false;
    }

    for (const auto& line : lines) {
        out << line << '\n';
    }

    return true;
}
} // namespace

std::vector<std::string> FilePatientRepository::readAppointments(const std::string& patientId) const {
    return readLines(patientFilePath(patientId, "appointments.txt"));
}

std::vector<std::string> FilePatientRepository::readMedications(const std::string& patientId) const {
    return readLines(patientFilePath(patientId, "medications.txt"));
}

std::vector<std::string> FilePatientRepository::readRecords(const std::string& patientId) const {
    return readLines(patientFilePath(patientId, "records.txt"));
}

bool FilePatientRepository::appendAppointment(const std::string& patientId, const std::string& line) {
    return appendLine(patientFilePath(patientId, "appointments.txt"), line);
}

bool FilePatientRepository::appendMedication(const std::string& patientId, const std::string& line) {
    return appendLine(patientFilePath(patientId, "medications.txt"), line);
}

bool FilePatientRepository::appendRecord(const std::string& patientId, const std::string& line) {
    return appendLine(patientFilePath(patientId, "records.txt"), line);
}

bool FilePatientRepository::appendAppointmentRequest(const std::string& line) {
    std::filesystem::create_directories("data/Appointments");
    return appendLine(appointmentRequestsPath(), line);
}

bool FilePatientRepository::appointmentRequestsExists() const {
    return std::filesystem::exists(appointmentRequestsPath());
}

std::vector<std::string> FilePatientRepository::readAppointmentRequests() const {
    return readLines(appointmentRequestsPath());
}

bool FilePatientRepository::writeAppointmentRequests(const std::vector<std::string>& lines) {
    return writeLines(appointmentRequestsPath(), lines);
}

bool FilePatientRepository::ensurePatientDirectory(const std::string& patientId) {
    return std::filesystem::create_directories("data/Patients/" + patientId) ||
           std::filesystem::exists("data/Patients/" + patientId);
}
