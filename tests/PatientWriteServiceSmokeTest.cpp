#include "application/usecase/PatientWriteService.hpp"
#include "common/result/ErrorCodes.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace {
class FakePatientRepository final : public IPatientRepository {
public:
    bool appendAppointmentResult = true;
    bool appendMedicationResult = true;
    bool appendRecordResult = true;
    bool appendRequestResult = true;

    std::string lastPatientId;
    std::string lastLine;
    std::string lastRequestLine;

    std::vector<std::string> readAppointments(const std::string&) const override { return {}; }
    std::vector<std::string> readMedications(const std::string&) const override { return {}; }
    std::vector<std::string> readRecords(const std::string&) const override { return {}; }

    bool appendAppointment(const std::string& patientId, const std::string& line) override {
        lastPatientId = patientId;
        lastLine = line;
        return appendAppointmentResult;
    }

    bool appendMedication(const std::string& patientId, const std::string& line) override {
        lastPatientId = patientId;
        lastLine = line;
        return appendMedicationResult;
    }

    bool appendRecord(const std::string& patientId, const std::string& line) override {
        lastPatientId = patientId;
        lastLine = line;
        return appendRecordResult;
    }

    bool appendAppointmentRequest(const std::string& line) override {
        lastRequestLine = line;
        return appendRequestResult;
    }

    bool appointmentRequestsExists() const override { return true; }
    std::vector<std::string> readAppointmentRequests() const override { return {}; }
    bool writeAppointmentRequests(const std::vector<std::string>&) override { return true; }
    bool ensurePatientDirectory(const std::string&) override { return true; }
};

bool testAddMedicationFormatsAndWritesLine() {
    FakePatientRepository repository;
    PatientWriteService service(repository);

    const Result<void> result = service.addMedication("P12345678", "Ibuprofen 400 mg", "3x daily", "2026-01-01", "2026-01-10");

    return result &&
           repository.lastPatientId == "P12345678" &&
           repository.lastLine == "Ibuprofen 400 mg - 3x daily - from 2026-01-01 to 2026-01-10";
}

bool testRequestAppointmentIncludesReason() {
    FakePatientRepository repository;
    PatientWriteService service(repository);

    const Result<void> result = service.requestAppointment("P12345678", "2026-02-18", "08:30", "House", "Checkup");

    return result &&
           repository.lastRequestLine ==
               "[2026-02-18 08:30] - P12345678 - Dr. House - Reason: Checkup - Status: pending";
}

bool testWriteFailureReturnsWriteFailedCode() {
    FakePatientRepository repository;
    repository.appendRecordResult = false;
    PatientWriteService service(repository);

    const Result<void> result = service.addRecord("P12345678", "2026-02-18", "Dr. House", "Diagnosis", "Stable");

    return !result && result.errorCode() == ErrorCodes::kWriteFailed;
}
}

int main() {
    if (!testAddMedicationFormatsAndWritesLine()) {
        std::cerr << "testAddMedicationFormatsAndWritesLine failed\n";
        return 1;
    }

    if (!testRequestAppointmentIncludesReason()) {
        std::cerr << "testRequestAppointmentIncludesReason failed\n";
        return 1;
    }

    if (!testWriteFailureReturnsWriteFailedCode()) {
        std::cerr << "testWriteFailureReturnsWriteFailedCode failed\n";
        return 1;
    }

    std::cout << "PatientWriteService smoke tests passed\n";
    return 0;
}
