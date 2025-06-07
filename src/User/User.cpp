#include "User.hpp"

User::User(const std::string& firstName, const std::string& lastName)
    : firstName(firstName), lastName(lastName) { }

User::~User() {}


// Getters

std::string User::getFirstName() const {
    return firstName;
}

std::string User::getLastName() const {
    return lastName;
}

// Setters

void User::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void User::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}

