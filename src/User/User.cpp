#include "User.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

User::User(std::string user_id,
           std::string role,
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
    return role;
}

// Setters

void User::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void User::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}




