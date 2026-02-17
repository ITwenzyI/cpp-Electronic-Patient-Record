#ifndef USER_PROVISIONING_INPUT_CLI_HPP
#define USER_PROVISIONING_INPUT_CLI_HPP

#include "application/ports/IUserProvisioningRepository.hpp"

#include <string>

class UserProvisioningInputCli {
public:
    static UserProvisioningData promptPatientInput();
    static UserProvisioningData promptDoctorInput();
    static UserProvisioningData promptAssistantInput();

private:
    static UserProvisioningData promptCommonInput(const std::string& roleLabel);
};

#endif //USER_PROVISIONING_INPUT_CLI_HPP
