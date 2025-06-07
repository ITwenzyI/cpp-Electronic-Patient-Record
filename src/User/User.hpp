

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
protected:
    std::string firstName;
    std::string lastName;
    std::string role;

public:
    // Constructor
    User(const std::string& firstName, const std::string& lastName, const std::string& role = "Unknown");

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
