//
// Created by User on 04.06.2025.
//

#include "Patient.hpp"
#include <iostream>

Patient::Patient(const std::string& firstName, const std::string& lastName,
                 const std::string& dateOfBirth, const std::string& gender,
                 const std::string& nationality, const std::string& address,
                 const std::string& phoneNumber, const std::string& insuranceID,
                 const std::string& insuranceType, const std::string& email)
    : User(firstName, lastName, dateOfBirth, gender, nationality, address,
           phoneNumber, insuranceID, insuranceType, "patient", email)
{ }

void Patient::displayMenu() {
    std::cout << "\n=== Patient Menu ===" << std::endl;
    std::cout << "1. View Medical Record" << std::endl;
    std::cout << "2. View Documents" << std::endl;
    std::cout << "3. Book Appointment" << std::endl;
    std::cout << "4. Logout" << std::endl;
}

