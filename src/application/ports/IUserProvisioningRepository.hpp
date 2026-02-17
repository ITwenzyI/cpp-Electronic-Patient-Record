#ifndef IUSER_PROVISIONING_REPOSITORY_HPP
#define IUSER_PROVISIONING_REPOSITORY_HPP

#include <string>

struct UserProvisioningData {
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;
    std::string gender;
    std::string nationality;
    std::string address;
    std::string phoneNumber;
    std::string email;
    std::string insuranceID;
    std::string insuranceType;
};

class IUserProvisioningRepository {
public:
    virtual ~IUserProvisioningRepository() = default;

    virtual bool createPatient(const UserProvisioningData& data) = 0;
    virtual bool createDoctor(const UserProvisioningData& data) = 0;
    virtual bool createAssistant(const UserProvisioningData& data) = 0;
};

#endif //IUSER_PROVISIONING_REPOSITORY_HPP
