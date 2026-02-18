#include "application/usecase/PatientRecordQueryService.hpp"

PatientRecordQueryService::PatientRecordQueryService(
    IUserRepository& userRepository,
    IPatientRepository& patientRepository
) : userRepository_(userRepository), patientRepository_(patientRepository) {}

Result<std::vector<std::string>> PatientRecordQueryService::getPatientInfo(const std::string& patientId) const {
    if (!userRepository_.exists(patientId)) {
        return Result<std::vector<std::string>>::failure("PATIENT_NOT_FOUND", "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(userRepository_.readInfo(patientId));
}

Result<std::vector<std::string>> PatientRecordQueryService::getAppointments(const std::string& patientId) const {
    const std::vector<std::string> appointments = patientRepository_.readAppointments(patientId);
    if (appointments.empty()) {
        return Result<std::vector<std::string>>::failure("APPOINTMENTS_NOT_FOUND", "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(appointments);
}

Result<std::vector<std::string>> PatientRecordQueryService::getMedications(const std::string& patientId) const {
    const std::vector<std::string> medications = patientRepository_.readMedications(patientId);
    if (medications.empty()) {
        return Result<std::vector<std::string>>::failure("MEDICATIONS_NOT_FOUND", "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(medications);
}

Result<std::vector<std::string>> PatientRecordQueryService::getRecords(const std::string& patientId) const {
    const std::vector<std::string> records = patientRepository_.readRecords(patientId);
    if (records.empty()) {
        return Result<std::vector<std::string>>::failure("RECORDS_NOT_FOUND", "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(records);
}
