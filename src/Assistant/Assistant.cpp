

#include "Assistant.hpp"
#include <iostream>

Assistant::Assistant(const std::string& firstName, const std::string& lastName) 
    : User(firstName, lastName) {

};

Assistant::~Assistant() {};

void Assistant::displayMenu() {
    std::cout << "\n=== Assistant Menu ===" << std::endl;
    std::cout << "1. View Medical Records" << std::endl;
    std::cout << "2. View Documents" << std::endl;
    std::cout << "3. View open Appointments" << std::endl;
    std::cout << "4. View Calender" << std::endl;
    std::cout << "9. Logout" << std::endl;
}
