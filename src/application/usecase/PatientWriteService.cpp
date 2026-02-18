#include "application/usecase/PatientWriteService.hpp"

#include "common/result/ErrorCodes.hpp"
#include "common/result/ErrorSources.hpp"

PatientWriteService::PatientWriteService(IPatientRepository& repository)
    : repository_(repository) {}

Result<void> PatientWriteService::addAppointment(
    const std::string& patientId,
    const std::string& date,
    const std::string& time,
    const std::string& doctorName,
    const std::string& reason
) const {
    const std::string line = "[" + date + " " + time + "] - " + doctorName + " (" + reason + ")";
    if (!repository_.appendAppointment(patientId, line)) {
        return Result<void>::failure(ErrorCodes::kWriteFailed, "Could not open appointment file for writing.", ErrorSources::kApplication, "PatientWriteService::addAppointment");
    }
    return Result<void>::success();
}

Result<void> PatientWriteService::addMedication(
    const std::string& patientId,
    const std::string& nameAndDose,
    const std::string& frequency,
    const std::string& startDate,
    const std::string& endDate
) const {
    const std::string line = nameAndDose + " - " + frequency + " - from " + startDate + " to " + endDate;
    if (!repository_.appendMedication(patientId, line)) {
        return Result<void>::failure(ErrorCodes::kWriteFailed, "Could not open medication file for writing.", ErrorSources::kApplication, "PatientWriteService::addMedication");
    }
    return Result<void>::success();
}

Result<void> PatientWriteService::addRecord(
    const std::string& patientId,
    const std::string& date,
    const std::string& doctor,
    const std::string& type,
    const std::string& content
) const {
    const std::string line = "[" + date + "] " + doctor + ": " + type + ": " + content;
    if (!repository_.appendRecord(patientId, line)) {
        return Result<void>::failure(ErrorCodes::kWriteFailed, "Could not open records file for writing.", ErrorSources::kApplication, "PatientWriteService::addRecord");
    }
    return Result<void>::success();
}

Result<void> PatientWriteService::requestAppointment(
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
    if (!repository_.appendAppointmentRequest(line)) {
        return Result<void>::failure(ErrorCodes::kWriteFailed, "Error: could not open data/Appointments/requests.txt", ErrorSources::kApplication, "PatientWriteService::requestAppointment");
    }
    return Result<void>::success();
}
