#ifndef FILE_PATIENT_REPOSITORY_HPP
#define FILE_PATIENT_REPOSITORY_HPP

#include "application/ports/IPatientRepository.hpp"

class FilePatientRepository final : public IPatientRepository {
public:
    std::vector<std::string> readAppointments(const std::string& patientId) const override;
    std::vector<std::string> readMedications(const std::string& patientId) const override;
    std::vector<std::string> readRecords(const std::string& patientId) const override;

    bool appendAppointment(const std::string& patientId, const std::string& line) override;
    bool appendMedication(const std::string& patientId, const std::string& line) override;
    bool appendRecord(const std::string& patientId, const std::string& line) override;

    bool appendAppointmentRequest(const std::string& line) override;
    bool appointmentRequestsExists() const override;
    std::vector<std::string> readAppointmentRequests() const override;
    bool writeAppointmentRequests(const std::vector<std::string>& lines) override;
    bool ensurePatientDirectory(const std::string& patientId) override;
};

#endif //FILE_PATIENT_REPOSITORY_HPP
