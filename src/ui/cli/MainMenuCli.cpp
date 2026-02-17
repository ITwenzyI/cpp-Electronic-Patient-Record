#include "ui/cli/MainMenuCli.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

std::string MainMenuCli::promptRoleSelection() const {
    std::cout << "Welcome to the Electronic Patient Record System.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    std::cout << "Please choice your role:\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    std::string input;
    std::cout << std::endl;
    std::cout << "=== ELECTRONIC PATIENT RECORD SYSTEM ===\n";
    std::cout << "1. Patient\n";
    std::cout << "2. Doctor\n";
    std::cout << "3. Assistant\n";
    std::cout << "0. Exit\n";
    std::cout << "Please enter your choice (or #admin): ";
    std::cin >> input;

    return input;
}

void MainMenuCli::promptLoginIdentity(std::string& id, std::string& firstName, std::string& lastName) const {
    std::cout << "Please enter your ID: ";
    std::cin >> id;

    std::cout << "Please enter your first name: ";
    std::cin >> firstName;
    std::cout << "Please enter your last name: ";
    std::cin >> lastName;
}
