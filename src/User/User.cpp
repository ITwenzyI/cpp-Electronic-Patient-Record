#include "User.hpp"

User::User(const std::string& firstName, const std::string& lastName,
           const std::string& dateOfBirth, const std::string& gender,
           const std::string& nationality, const std::string& address,
           const std::string& phoneNumber, const std::string& insuranceID,
           const std::string& insuranceType, const std::string& role,
           const std::string& email)
    : firstName(firstName), lastName(lastName), dateOfBirth(dateOfBirth),
      gender(gender), nationality(nationality), address(address),
      phoneNumber(phoneNumber), insuranceID(insuranceID),
      insuranceType(insuranceType), userID(""), role(role), email(email) { }

User::~User() = default;
