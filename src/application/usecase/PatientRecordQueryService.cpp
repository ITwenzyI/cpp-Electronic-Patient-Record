#include "application/usecase/PatientRecordQueryService.hpp"

PatientRecordQueryService::PatientRecordQueryService(
    IUserRepository& userRepository,
    IPatientRepository& patientRepository
) : userRepository_(userRepository), patientRepository_(patientRepository) {}

std::vector<std::string> PatientRecordQueryService::getPatientInfo(const std::string& patientId) const {
    return userRepository_.readInfo(patientId);
}

std::vector<std::string> PatientRecordQueryService::getAppointments(const std::string& patientId) const {
    return patientRepository_.readAppointments(patientId);
}

std::vector<std::string> PatientRecordQueryService::getMedications(const std::string& patientId) const {
    return patientRepository_.readMedications(patientId);
}

std::vector<std::string> PatientRecordQueryService::getRecords(const std::string& patientId) const {
    return patientRepository_.readRecords(patientId);
}
