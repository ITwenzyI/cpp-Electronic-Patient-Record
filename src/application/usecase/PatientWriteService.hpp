#ifndef PATIENT_WRITE_SERVICE_HPP
#define PATIENT_WRITE_SERVICE_HPP

#include "application/ports/IPatientRepository.hpp"
#include "common/result/Result.hpp"

#include <string>

class PatientWriteService {
public:
    explicit PatientWriteService(IPatientRepository& repository);

    Result<void> addAppointment(
        const std::string& patientId,
        const std::string& date,
        const std::string& time,
        const std::string& doctorName,
        const std::string& reason
    ) const;

    Result<void> addMedication(
        const std::string& patientId,
        const std::string& nameAndDose,
        const std::string& frequency,
        const std::string& startDate,
        const std::string& endDate
    ) const;

    Result<void> addRecord(
        const std::string& patientId,
        const std::string& date,
        const std::string& doctor,
        const std::string& type,
        const std::string& content
    ) const;

    Result<void> requestAppointment(
        const std::string& patientId,
        const std::string& date,
        const std::string& time,
        const std::string& doctorName,
        const std::string& reason
    ) const;

private:
    IPatientRepository& repository_;
};

#endif //PATIENT_WRITE_SERVICE_HPP
