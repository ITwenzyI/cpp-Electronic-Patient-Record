#include "User.hpp"

User::User(std::string user_id,
           UserRole role,
           std::string firstName,
           std::string lastName,
           std::string dateOfBirth,
           std::string gender,
           std::string nationality,
           std::string address,
           std::string phoneNumber,
           std::string email,
           std::string insuranceID,
           std::string insuranceType)
    : user_id(std::move(user_id)),
      role(std::move(role)),
      firstName(std::move(firstName)),
      lastName(std::move(lastName)),
      dateOfBirth(std::move(dateOfBirth)),
      gender(std::move(gender)),
      nationality(std::move(nationality)),
      address(std::move(address)),
      phoneNumber(std::move(phoneNumber)),
      email(std::move(email)),
      insuranceID(std::move(insuranceID)),
      insuranceType(std::move(insuranceType)) {}




User::~User() = default;





// Getters

std::string User::getFirstName() const {
    return firstName;
}

std::string User::getLastName() const {
    return lastName;
}

std::string User::getRole() const {
    switch (role) {
        case UserRole::Patient:
            return "Patient";
        case UserRole::Doctor:
            return "Doctor";
        case UserRole::Assistant:
            return "Assistant";
        default:
            return "";
    }
}

std::string User::getID() const {
    return user_id;
}

std::string User::getDateOfBirth() const {
    return dateOfBirth;
}

std::string User::getGender() const {
    return gender;
}

std::string User::getNationality() const {
    return nationality;
}

std::string User::getAddress() const {
    return address;
}

std::string User::getPhoneNumber() const {
    return phoneNumber;
}

std::string User::getEmail() const {
    return email;
}

std::string User::getInsuranceID() const {
    return insuranceID;
}

std::string User::getInsuranceType() const {
    return insuranceType;
}


// Setters

void User::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void User::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}







