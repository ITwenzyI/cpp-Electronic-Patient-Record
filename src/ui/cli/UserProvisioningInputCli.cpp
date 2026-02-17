#include "ui/cli/UserProvisioningInputCli.hpp"

#include <iostream>

UserProvisioningData UserProvisioningInputCli::promptPatientInput() {
    return promptCommonInput("Patient");
}

UserProvisioningData UserProvisioningInputCli::promptDoctorInput() {
    return promptCommonInput("Doctor");
}

UserProvisioningData UserProvisioningInputCli::promptAssistantInput() {
    return promptCommonInput("Assistant");
}

UserProvisioningData UserProvisioningInputCli::promptCommonInput(const std::string& roleLabel) {
    UserProvisioningData data{};

    std::cout << "\nPlease provide all Infos from the " << roleLabel << "!\n" << std::endl;
    std::cout << "Date of Birth: ";
    std::getline(std::cin >> std::ws, data.dateOfBirth);
    std::cout << "Gender: ";
    std::getline(std::cin, data.gender);
    std::cout << "Nationality: ";
    std::getline(std::cin, data.nationality);
    std::cout << "Address: ";
    std::getline(std::cin, data.address);
    std::cout << "Phone Number: ";
    std::getline(std::cin, data.phoneNumber);
    std::cout << "Email Address: ";
    std::getline(std::cin, data.email);
    std::cout << "Insurance ID: ";
    std::getline(std::cin, data.insuranceID);
    std::cout << "InsuranceType: ";
    std::getline(std::cin, data.insuranceType);

    return data;
}
