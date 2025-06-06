//
// Created by User on 04.06.2025.
//

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "../User/User.hpp"

class Patient : public User {
public:
    Patient(const std::string& firstName, const std::string& lastName,
            const std::string& dateOfBirth, const std::string& gender,
            const std::string& nationality, const std::string& address,
            const std::string& phoneNumber, const std::string& insuranceID,
            const std::string& insuranceType, const std::string& email);

    void displayMenu() override;

    // weitere Funktionen:
    void viewMedicalRecord();
    void viewDocuments();
    void bookAppointment();
};

#endif //PATIENT_HPP
