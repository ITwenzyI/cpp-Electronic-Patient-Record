#include "application/usecase/UserProvisioningService.hpp"

UserProvisioningService::UserProvisioningService(IUserProvisioningRepository& repository)
    : repository_(repository) {}

bool UserProvisioningService::createPatient(const UserProvisioningData& data) const {
    return repository_.createPatient(data);
}

bool UserProvisioningService::createDoctor(const UserProvisioningData& data) const {
    return repository_.createDoctor(data);
}

bool UserProvisioningService::createAssistant(const UserProvisioningData& data) const {
    return repository_.createAssistant(data);
}

bool UserProvisioningService::createPatient(const Patient& patient) const {
    return repository_.createPatient(toProvisioningData(patient));
}

bool UserProvisioningService::createDoctor(const Doctor& doctor) const {
    return repository_.createDoctor(toProvisioningData(doctor));
}

bool UserProvisioningService::createAssistant(const Assistant& assistant) const {
    return repository_.createAssistant(toProvisioningData(assistant));
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
