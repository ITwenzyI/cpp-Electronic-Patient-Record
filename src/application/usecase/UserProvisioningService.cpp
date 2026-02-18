#include "application/usecase/UserProvisioningService.hpp"

UserProvisioningService::UserProvisioningService(IUserProvisioningRepository& repository)
    : repository_(repository) {}

Result<void> UserProvisioningService::createPatient(const UserProvisioningData& data) const {
    if (!repository_.createPatient(data)) {
        return Result<void>::failure("CREATE_PATIENT_FAILED", "Failed to create patient.");
    }
    return Result<void>::success();
}

Result<void> UserProvisioningService::createDoctor(const UserProvisioningData& data) const {
    if (!repository_.createDoctor(data)) {
        return Result<void>::failure("CREATE_DOCTOR_FAILED", "Failed to create doctor.");
    }
    return Result<void>::success();
}

Result<void> UserProvisioningService::createAssistant(const UserProvisioningData& data) const {
    if (!repository_.createAssistant(data)) {
        return Result<void>::failure("CREATE_ASSISTANT_FAILED", "Failed to create assistant.");
    }
    return Result<void>::success();
}

Result<void> UserProvisioningService::createPatient(const Patient& patient) const {
    return createPatient(toProvisioningData(patient));
}

Result<void> UserProvisioningService::createDoctor(const Doctor& doctor) const {
    return createDoctor(toProvisioningData(doctor));
}

Result<void> UserProvisioningService::createAssistant(const Assistant& assistant) const {
    return createAssistant(toProvisioningData(assistant));
}

UserProvisioningData UserProvisioningService::toProvisioningData(const User& user) {
    return {
        user.getFirstName(),
        user.getLastName(),
        user.getDateOfBirth(),
        user.getGender(),
        user.getNationality(),
        user.getAddress(),
        user.getPhoneNumber(),
        user.getEmail(),
        user.getInsuranceID(),
        user.getInsuranceType()
    };
}
