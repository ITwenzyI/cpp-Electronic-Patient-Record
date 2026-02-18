
#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include "domain/model/User/User.hpp"

class Doctor : public User {
    public:

    // Constructor
    Doctor(const std::string& doctor_id,
            const std::string& firstName,
            const std::string& lastName);

    // Role-specific menu entrypoint.
    void displayMenu() override;

};

#endif //DOCTOR_HPP
