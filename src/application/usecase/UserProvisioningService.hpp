#ifndef USER_PROVISIONING_SERVICE_HPP
#define USER_PROVISIONING_SERVICE_HPP

#include "application/ports/IUserProvisioningRepository.hpp"
#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"

class UserProvisioningService {
public:
    explicit UserProvisioningService(IUserProvisioningRepository& repository);

    bool createPatient(const Patient& patient) const;
    bool createDoctor(const Doctor& doctor) const;
    bool createAssistant(const Assistant& assistant) const;

private:
    IUserProvisioningRepository& repository_;
    static UserProvisioningData toProvisioningData(const User& user);
};

#endif //USER_PROVISIONING_SERVICE_HPP
