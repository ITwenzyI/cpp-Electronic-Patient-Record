#ifndef FILE_USER_PROVISIONING_REPOSITORY_HPP
#define FILE_USER_PROVISIONING_REPOSITORY_HPP

#include "application/ports/IUserProvisioningRepository.hpp"

class FileUserProvisioningRepository final : public IUserProvisioningRepository {
public:
    bool createPatient(const UserProvisioningData& data) override;
    bool createDoctor(const UserProvisioningData& data) override;
    bool createAssistant(const UserProvisioningData& data) override;
};

#endif //FILE_USER_PROVISIONING_REPOSITORY_HPP
