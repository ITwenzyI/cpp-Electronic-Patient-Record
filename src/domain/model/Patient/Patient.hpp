

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "domain/model/User/User.hpp"

class Patient : public User {
  public:
    // Constructor
    Patient(
        const std::string& patient_id, const std::string& firstName, const std::string& lastName);
};

#endif //PATIENT_HPP
