#include "User.hpp"

User::User(const std::string& firstName, const std::string& lastName, const std::string& role)
    : firstName(firstName), lastName(lastName), role(role) { }


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

