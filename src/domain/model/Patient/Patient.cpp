#include "Patient.hpp"

Patient::Patient(
    const std::string& patient_id, const std::string& firstName, const std::string& lastName)
    : User(patient_id, UserRole::Patient, firstName, lastName, "", "", "", "", "", "", "", "") {
}
