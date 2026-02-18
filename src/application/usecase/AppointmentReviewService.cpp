#include "application/usecase/AppointmentReviewService.hpp"

namespace {
std::string extractPatientId(const std::string& entry) {
    const size_t idStart = entry.find("P");
    if (idStart == std::string::npos) {
        return "";
    }
    return entry.substr(idStart, 9);
}

std::string extractDateTime(const std::string& entry) {
    const size_t bracketStart = entry.find('[');
    const size_t bracketEnd = entry.find(']');
    if (bracketStart == std::string::npos || bracketEnd == std::string::npos || bracketEnd < bracketStart) {
        return "";
    }
    return entry.substr(bracketStart, bracketEnd - bracketStart + 1);
}

Result<std::string> extractDoctor(const std::string& entry) {
    const size_t drStart = entry.find("Dr. ");
    if (drStart == std::string::npos) {
        return Result<std::string>::failure("DOCTOR_NAME_NOT_FOUND", "Doctor name not found.");
    }

    const size_t nameEnd = entry.find(" -", drStart);
    if (nameEnd == std::string::npos || nameEnd <= drStart + 4) {
        return Result<std::string>::failure("DOCTOR_NAME_NOT_FOUND", "Doctor name not found.");
    }

    return Result<std::string>::success(entry.substr(drStart + 4, nameEnd - (drStart + 4)));
}
}

AppointmentReviewService::AppointmentReviewService(IPatientRepository& repository)
    : repository_(repository) {}

Result<std::vector<std::string>> AppointmentReviewService::loadRequests() const {
    if (!repository_.appointmentRequestsExists()) {
        return Result<std::vector<std::string>>::failure("REQUESTS_FILE_MISSING", "Error: Could not open data/Appointments/requests.txt");
    }
    return Result<std::vector<std::string>>::success(repository_.readAppointmentRequests());
}

Result<AppointmentDecisionOutcome> AppointmentReviewService::applyDecision(std::string& entry, const AppointmentDecision decision) const {
    if (decision == AppointmentDecision::Skip) {
        return Result<AppointmentDecisionOutcome>::success({false, false, "Skipped."});
    }

    if (decision == AppointmentDecision::Reject) {
        entry.replace(entry.find("pending"), 7, "rejected");
        return Result<AppointmentDecisionOutcome>::success({true, false, "Appointment rejected."});
    }

    const std::string patientId = extractPatientId(entry);
    const std::string dateTime = extractDateTime(entry);
    const Result<std::string> doctorResult = extractDoctor(entry);
    if (!doctorResult.ok()) {
        return Result<AppointmentDecisionOutcome>::failure(doctorResult.error().code, doctorResult.error().message);
    }

    if (!repository_.ensurePatientDirectory(patientId) ||
        !repository_.appendAppointment(patientId, dateTime + " - Dr. " + doctorResult.value() + " (confirmed)")) {
        return Result<AppointmentDecisionOutcome>::success({
            false,
            true,
            "Error writing to data/Patients/" + patientId + "/appointments.txt"
        });
    }

    entry.replace(entry.find("pending"), 7, "confirmed");
    return Result<AppointmentDecisionOutcome>::success({true, false, "Appointment confirmed and added to patient file."});
}

Result<void> AppointmentReviewService::saveRequests(const std::vector<std::string>& lines) const {
    if (!repository_.writeAppointmentRequests(lines)) {
        return Result<void>::failure("WRITE_REQUESTS_FAILED", "\nFailed to update appointment file.");
    }
    return Result<void>::success();
}

bool AppointmentReviewService::isPending(const std::string& entry) {
    return entry.find("Status: pending") != std::string::npos;
}
