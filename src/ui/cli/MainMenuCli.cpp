#include "ui/cli/MainMenuCli.hpp"
#include "ui/cli/ConsoleIO.hpp"

#include <iostream>
#include <string>

std::string MainMenuCli::promptRoleSelection() const {
    std::cout << "Welcome to the Electronic Patient Record System.\n";
    ConsoleIO::pauseMilliseconds(1500);
    std::cout << "Please choice your role:\n";
    ConsoleIO::pauseMilliseconds(900);

    std::string input;
    ConsoleIO::printHeader("=== ELECTRONIC PATIENT RECORD SYSTEM ===");
    std::cout << "1. Patient\n";
    std::cout << "2. Doctor\n";
    std::cout << "3. Assistant\n";
    std::cout << "0. Exit\n";
    input = ConsoleIO::promptToken("Please enter your choice (or #admin): ");

    return input;
}

void MainMenuCli::promptLoginIdentity(std::string& id, std::string& firstName, std::string& lastName) const {
    id = ConsoleIO::promptToken("Please enter your ID: ");
    firstName = ConsoleIO::promptToken("Please enter your first name: ");
    lastName = ConsoleIO::promptToken("Please enter your last name: ");
}
