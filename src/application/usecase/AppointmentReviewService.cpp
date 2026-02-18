#include "application/usecase/AppointmentReviewService.hpp"

#include "common/result/ErrorCodes.hpp"
#include "common/result/ErrorSources.hpp"

namespace {
std::string extractPatientId(const std::string& entry) {
    // Requests currently encode IDs with a leading role marker (e.g. P00000001).
    const size_t idStart = entry.find("P");
    if (idStart == std::string::npos) {
        return "";
    }
    return entry.substr(idStart, 9);
}

std::string extractDateTime(const std::string& entry) {
    // Datetime is stored in brackets: "[YYYY-MM-DD HH:MM]".
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
        return Result<std::string>::failure(
            ErrorCodes::kDoctorNameNotFound, "Doctor name not found.", ErrorSources::kApplication, "AppointmentReviewService::extractDoctor"
        );
    }

    const size_t nameEnd = entry.find(" -", drStart);
    if (nameEnd == std::string::npos || nameEnd <= drStart + 4) {
        return Result<std::string>::failure(
            ErrorCodes::kDoctorNameNotFound, "Doctor name not found.", ErrorSources::kApplication, "AppointmentReviewService::extractDoctor"
        );
    }

    return Result<std::string>::success(entry.substr(drStart + 4, nameEnd - (drStart + 4)));
}
}

AppointmentReviewService::AppointmentReviewService(IPatientRepository& repository)
    : repository_(repository) {}

Result<std::vector<std::string>> AppointmentReviewService::loadRequests() const {
    if (!repository_.appointmentRequestsExists()) {
        return Result<std::vector<std::string>>::failure(
            ErrorCodes::kRequestsFileMissing, "Error: Could not open data/Appointments/requests.txt",
            ErrorSources::kApplication, "AppointmentReviewService::loadRequests"
        );
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
    if (!doctorResult) {
        return Result<AppointmentDecisionOutcome>::failure(
            doctorResult.errorCode(), doctorResult.errorMessage(), doctorResult.errorSource(), doctorResult.errorDetail()
        );
    }

    if (!repository_.ensurePatientDirectory(patientId) ||
        !repository_.appendAppointment(patientId, dateTime + " - Dr. " + doctorResult.value() + " (confirmed)")) {
        // Keep review loop running for this recoverable write failure.
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
        return Result<void>::failure(
            ErrorCodes::kWriteRequestsFailed, "\nFailed to update appointment file.",
            ErrorSources::kApplication, "AppointmentReviewService::saveRequests"
        );
    }
    return Result<void>::success();
}

bool AppointmentReviewService::isPending(const std::string& entry) {
    return entry.find("Status: pending") != std::string::npos;
}
