#ifndef USER_PROVISIONING_SERVICE_HPP
#define USER_PROVISIONING_SERVICE_HPP

#include "application/ports/IUserProvisioningRepository.hpp"
#include "common/result/Result.hpp"
#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"

class UserProvisioningService {
public:
    explicit UserProvisioningService(IUserProvisioningRepository& repository);

    Result<void> createPatient(const UserProvisioningData& data) const;
    Result<void> createDoctor(const UserProvisioningData& data) const;
    Result<void> createAssistant(const UserProvisioningData& data) const;

    Result<void> createPatient(const Patient& patient) const;
    Result<void> createDoctor(const Doctor& doctor) const;
    Result<void> createAssistant(const Assistant& assistant) const;

private:
    IUserProvisioningRepository& repository_;
    static UserProvisioningData toProvisioningData(const User& user);
};

#endif //USER_PROVISIONING_SERVICE_HPP
