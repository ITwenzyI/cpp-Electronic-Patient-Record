#ifndef PATIENT_RECORD_QUERY_SERVICE_HPP
#define PATIENT_RECORD_QUERY_SERVICE_HPP

#include "application/ports/IPatientRepository.hpp"
#include "application/ports/IUserRepository.hpp"
#include "common/result/Result.hpp"

#include <string>
#include <vector>

class PatientRecordQueryService {
public:
    PatientRecordQueryService(IUserRepository& userRepository, IPatientRepository& patientRepository);

    Result<std::vector<std::string>> getPatientInfo(const std::string& patientId) const;
    Result<std::vector<std::string>> getAppointments(const std::string& patientId) const;
    Result<std::vector<std::string>> getMedications(const std::string& patientId) const;
    Result<std::vector<std::string>> getRecords(const std::string& patientId) const;

private:
    IUserRepository& userRepository_;
    IPatientRepository& patientRepository_;
};

#endif //PATIENT_RECORD_QUERY_SERVICE_HPP
