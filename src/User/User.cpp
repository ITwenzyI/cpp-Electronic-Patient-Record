#include "User.hpp"

User::User(const std::string& firstName, const std::string& lastName)
    : firstName(firstName), lastName(lastName) { }

User::~User() = default;

std::string User::getFirstName() const {
    return firstName;
}

