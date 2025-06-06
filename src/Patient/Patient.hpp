//
// Created by User on 04.06.2025.
//

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "../User/User.hpp"

class Patient : public User {
public:
    Patient(const std::string& firstName, const std::string& lastName);

    void displayMenu() override;
};

#endif //PATIENT_HPP
