#include "application/usecase/PatientWriteService.hpp"

PatientWriteService::PatientWriteService(IPatientRepository& repository)
    : repository_(repository) {}

bool PatientWriteService::addAppointment(
    const std::string& patientId,
    const std::string& date,
    const std::string& time,
    const std::string& doctorName,
    const std::string& reason
) const {
    const std::string line = "[" + date + " " + time + "] - " + doctorName + " (" + reason + ")";
    return repository_.appendAppointment(patientId, line);
}

bool PatientWriteService::addMedication(
    const std::string& patientId,
    const std::string& nameAndDose,
    const std::string& frequency,
    const std::string& startDate,
    const std::string& endDate
) const {
    const std::string line = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;
    return repository_.appendMedication(patientId, line);
}

bool PatientWriteService::addRecord(
    const std::string& patientId,
    const std::string& date,
    const std::string& doctor,
    const std::string& type,
    const std::string& content
) const {
    const std::string line = "[" + date + "] " + doctor + ": " + type + ": " + content;
    return repository_.appendRecord(patientId, line);
}

bool PatientWriteService::requestAppointment(
    const std::string& patientId,
    const std::string& date,
    const std::string& time,
    const std::string& doctorName,
    const std::string& reason
) const {
    std::string line = "[" + date + " " + time + "] - " + patientId + " - Dr. " + doctorName;
    if (!reason.empty()) {
        line += " - Reason: " + reason;
    }
    line += " - Status: pending";
    return repository_.appendAppointmentRequest(line);
}
