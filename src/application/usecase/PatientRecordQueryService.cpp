#include "application/usecase/PatientRecordQueryService.hpp"

#include "common/result/ErrorCodes.hpp"

PatientRecordQueryService::PatientRecordQueryService(
    IUserRepository& userRepository,
    IPatientRepository& patientRepository
) : userRepository_(userRepository), patientRepository_(patientRepository) {}

Result<std::vector<std::string>> PatientRecordQueryService::getPatientInfo(const std::string& patientId) const {
    if (!userRepository_.exists(patientId)) {
        return Result<std::vector<std::string>>::failure(ErrorCodes::kPatientNotFound, "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(userRepository_.readInfo(patientId));
}

Result<std::vector<std::string>> PatientRecordQueryService::getAppointments(const std::string& patientId) const {
    const std::vector<std::string> appointments = patientRepository_.readAppointments(patientId);
    if (appointments.empty()) {
        return Result<std::vector<std::string>>::failure(ErrorCodes::kAppointmentsNotFound, "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(appointments);
}

Result<std::vector<std::string>> PatientRecordQueryService::getMedications(const std::string& patientId) const {
    const std::vector<std::string> medications = patientRepository_.readMedications(patientId);
    if (medications.empty()) {
        return Result<std::vector<std::string>>::failure(ErrorCodes::kMedicationsNotFound, "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(medications);
}

Result<std::vector<std::string>> PatientRecordQueryService::getRecords(const std::string& patientId) const {
    const std::vector<std::string> records = patientRepository_.readRecords(patientId);
    if (records.empty()) {
        return Result<std::vector<std::string>>::failure(ErrorCodes::kRecordsNotFound, "Failed to read file!");
    }
    return Result<std::vector<std::string>>::success(records);
}
