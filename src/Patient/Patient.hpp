

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "../User/User.hpp"

class Patient : public User {
public:
    // Constructor
    Patient(const std::string& firstName, const std::string& lastName);

    // Destructor
    virtual ~Patient();
    

    void displayMenu() override;
};

#endif //PATIENT_HPP
