#include "domain/model/User/User.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"

#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

namespace {
IUserRepository& userRepository() {
    static FileUserRepository repository;
    return repository;
}
}

// Updates a specific field in info.txt of the id.
void User::update_field_in_file(const std::string& id, const std::string& field, const std::string& newInput) {
    if (!userRepository().exists(id)) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::vector<std::string> lines = userRepository().readInfo(id);
    bool updated = false;

    for (auto& line : lines) {
        if (line.substr(0, field.length() + 2) == field + ": ") {
            line = field + ": " + newInput;
            updated = true;
        }
    }

    if (!updated) {
        std::cerr << "Field \"" << field << "\" not found in file.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    if (!userRepository().writeInfo(id, lines)) {
        std::cerr << "Failed to open file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }
    std::cout << field << " successfully updated.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Adds extra info in info.txt for the ID.
void User::add_extra_info(const std::string &id) {
    if (!userRepository().exists(id)) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::string extra_info;

    std::cout << "ID: " << id << std::endl;
    std::cout << "Enter the Extra Info: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, extra_info);
    std::cout << std::endl;

    std::string newLine = "[" + getDate() + "] " + extra_info + "\n";

    if (!userRepository().appendInfoLine(id, newLine)) {
        std::cerr << "Could not open file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::cout << "Extra Info added:\n" << newLine << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
