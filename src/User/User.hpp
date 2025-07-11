

#ifndef USER_HPP
#define USER_HPP

#include "../Utils/Utils.hpp"

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <format>
#include <ctime>
#include <thread>

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
    virtual std::string getFirstName() const;
    virtual std::string getLastName() const;
    virtual std::string getRole() const;
    virtual std::string getID() const;

    // Setters
    virtual void setFirstName(const std::string& firstName);
    virtual void setLastName(const std::string& lastName);

    static void update_field_in_file(const std::string& id, const std::string& field, const std::string& newInput);
    static void add_extra_info(const std::string& id);

    // Abstract method
    virtual void displayMenu() = 0;
    virtual void check_id_name(std::string id, std::string firstName, std::string lastName) = 0;

};

#endif // USER_HPP
