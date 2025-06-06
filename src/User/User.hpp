

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
private:
    std::string dateOfBirth;     // Format: "YYYY-MM-DD"
    std::string gender;
    std::string nationality;
    std::string address;
    std::string phoneNumber;
    std::string insuranceID;
    std::string insuranceType;
    std::string userID;          // Unique ID in the system
    std::string email;

protected:
    std::string firstName;
    std::string lastName;
    std::string role;            // e.g. "patient", "doctor", "assistant"

    // Setter only accessible by derived classes
    void setUserID(const std::string& userID);
    void setRole(const std::string& role);

public:
    // Constructor
    User(const std::string& firstName, const std::string& lastName,
         const std::string& dateOfBirth, const std::string& gender,
         const std::string& nationality, const std::string& address,
         const std::string& phoneNumber, const std::string& insuranceID,
         const std::string& insuranceType, const std::string& role,
         const std::string& email);

    // Virtual destructor
    virtual ~User();

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getDateOfBirth() const;
    std::string getGender() const;
    std::string getNationality() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    std::string getInsuranceID() const;
    std::string getInsuranceType() const;
    std::string getUserID() const;
    std::string getRole() const;
    std::string getEmail() const;

    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);
    void setDateOfBirth(const std::string& dateOfBirth);
    void setGender(const std::string& gender);
    void setNationality(const std::string& nationality);
    void setAddress(const std::string& address);
    void setPhoneNumber(const std::string& phoneNumber);
    void setInsuranceID(const std::string& insuranceID);
    void setInsuranceType(const std::string& insuranceType);
    void setEmail(const std::string& email);

    // Abstract method
    virtual void displayMenu() = 0;
};

#endif // USER_HPP
