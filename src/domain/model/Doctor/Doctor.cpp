#include "Doctor.hpp"

Doctor::Doctor(const std::string& doctor_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(doctor_id, UserRole::Doctor, firstName, lastName,
           "", "", "", "", "", "", "", "") {}




