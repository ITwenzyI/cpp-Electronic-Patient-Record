
#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include "../User/User.hpp"

class Doctor : public User {
    public:

    // Constructor
    Doctor(const std::string& patient_id,
            const std::string& firstName,
            const std::string& lastName);

    //Destructor
    virtual ~Doctor();

    void displayMenu() override;

};

#endif //DOCTOR_HPP
