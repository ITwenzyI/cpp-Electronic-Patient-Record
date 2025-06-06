

#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {
protected:
    std::string firstName;
    std::string lastName;

public:
    // Constructor
    User(const std::string& firstName, const std::string& lastName);

    // Virtual destructor
    virtual ~User();

    // Getters
    std::string getFirstName() const;
    std::string getLastName() const;

    // Setters
    void setFirstName(const std::string& firstName);
    void setLastName(const std::string& lastName);

    // Abstract method
    virtual void displayMenu() = 0;
};

#endif // USER_HPP
