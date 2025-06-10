

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
protected:
    std::string user_id; // Unique ID in the system
    std::string role;

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
         std::string insuranceType);



    // Virtual destructor
    virtual ~User();

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;
    virtual std::string getRole() const;

    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);

    // Abstract method
    virtual void displayMenu() = 0;

};

#endif // USER_HPP
