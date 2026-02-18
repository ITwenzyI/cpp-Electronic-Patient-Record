#ifndef APPOINTMENT_REVIEW_SERVICE_HPP
#define APPOINTMENT_REVIEW_SERVICE_HPP

#include "application/ports/IPatientRepository.hpp"
#include "common/result/Result.hpp"

#include <cstddef>
#include <string>
#include <vector>

enum class AppointmentDecision {
    Accept,
    Reject,
    Skip
};

struct AppointmentDecisionOutcome {
    bool changed;
    bool hasError;
    std::string message;
};

class AppointmentReviewService {
public:
    explicit AppointmentReviewService(IPatientRepository& repository);

    Result<std::vector<std::string>> loadRequests() const;
    Result<AppointmentDecisionOutcome> applyDecision(std::string& entry, AppointmentDecision decision) const;
    Result<void> saveRequests(const std::vector<std::string>& lines) const;
    static bool isPending(const std::string& entry);

private:
    IPatientRepository& repository_;
};

#endif // APPOINTMENT_REVIEW_SERVICE_HPP
