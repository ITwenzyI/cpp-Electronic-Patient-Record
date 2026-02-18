

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <utility>

enum class UserRole {
    Patient,
    Doctor,
    Assistant
};

class User {
protected:
    std::string user_id; // Unique ID in the system
    UserRole role;

    // --- Personal Infos ---
    std::string firstName;
    std::string lastName;
    std::string dateOfBirth;     // Format: "YYYY-MM-DD"
    std::string gender;
    std::string nationality;

    // --- Contact Infos ---
    std::string address;
    std::string phoneNumber;
    std::string email;

    // --- Insurance Infos ---
    std::string insuranceID;
    std::string insuranceType;

public:
    // Constructor
    User(std::string user_id,
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
         std::string insuranceType);



    // Virtual destructor
    virtual ~User();

    // Getters
    virtual std::string getFirstName() const;
    virtual std::string getLastName() const;
    virtual std::string getRole() const;
    virtual std::string getID() const;
    virtual std::string getDateOfBirth() const;
    virtual std::string getGender() const;
    virtual std::string getNationality() const;
    virtual std::string getAddress() const;
    virtual std::string getPhoneNumber() const;
    virtual std::string getEmail() const;
    virtual std::string getInsuranceID() const;
    virtual std::string getInsuranceType() const;

    // Setters
    virtual void setFirstName(const std::string& firstName);
    virtual void setLastName(const std::string& lastName);

    // Abstract method
    virtual void displayMenu() = 0;

};

#endif // USER_HPP
