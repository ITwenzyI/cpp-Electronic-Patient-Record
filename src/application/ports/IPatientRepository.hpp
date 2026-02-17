#ifndef IPATIENT_REPOSITORY_HPP
#define IPATIENT_REPOSITORY_HPP

#include <string>
#include <vector>

class IPatientRepository {
public:
    virtual ~IPatientRepository() = default;

    virtual std::vector<std::string> readAppointments(const std::string& patientId) const = 0;
    virtual std::vector<std::string> readMedications(const std::string& patientId) const = 0;
    virtual std::vector<std::string> readRecords(const std::string& patientId) const = 0;

    virtual bool appendAppointment(const std::string& patientId, const std::string& line) = 0;
    virtual bool appendMedication(const std::string& patientId, const std::string& line) = 0;
    virtual bool appendRecord(const std::string& patientId, const std::string& line) = 0;

    virtual bool appendAppointmentRequest(const std::string& line) = 0;
    virtual bool appointmentRequestsExists() const = 0;
    virtual std::vector<std::string> readAppointmentRequests() const = 0;
    virtual bool writeAppointmentRequests(const std::vector<std::string>& lines) = 0;
    virtual bool ensurePatientDirectory(const std::string& patientId) = 0;
};

#endif //IPATIENT_REPOSITORY_HPP
