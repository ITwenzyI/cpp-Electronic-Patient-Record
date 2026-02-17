#include "application/EprApplication.hpp"

#include "application/ports/ISystemRepository.hpp"
#include "application/usecase/UserSessionService.hpp"
#include "ui/cli/Admin/Admin.hpp"
#include "infrastructure/persistence/FileSystemRepository.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <windows.h>

namespace {
ISystemRepository& systemRepository() {
    static FileSystemRepository repository;
    return repository;
}

const UserSessionService& userSessionService() {
    static UserSessionService service;
    return service;
}
}

int EprApplication::run() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Booting up System.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    std::cout << "Booting up System..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    std::cout << "Booting up System...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    systemRepository().ensureBootstrapData();

    while (!Admin::checkInitialSetup()) {}

    int choice;

    do {
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

        if (input == "#admin") {
            Admin::admin_setup();
        } else {
            try {
                choice = std::stoi(input);
            } catch (...) {
                std::cout << "Invalid input.\n";
                return 0;
            }

            if (choice == 0) {
                std::cout << "Exiting...\n";
                return 0;
            }

            std::string id;
            std::cout << "Please enter your ID: ";
            std::cin >> id;

            std::string firstName, lastName;
            std::cout << "Please enter your first name: ";
            std::cin >> firstName;
            std::cout << "Please enter your last name: ";
            std::cin >> lastName;

            userSessionService().runRoleSession(choice, id, firstName, lastName);
        }
    } while (choice != 0);

    return 0;
}
