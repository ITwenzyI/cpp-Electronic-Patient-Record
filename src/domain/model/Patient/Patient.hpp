

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "domain/model/User/User.hpp"

class Patient : public User {
public:
    // Constructor
    Patient(const std::string& patient_id,
            const std::string& firstName,
            const std::string& lastName);




    // If check_id_name is true, Menu will be displayed
    void displayMenu() override;

    // Checks if ID and firstName and lastName of info.txt match.
    void check_id_name(std::string id, std::string firstName, std::string lastName) override;

};

#endif //PATIENT_HPP
