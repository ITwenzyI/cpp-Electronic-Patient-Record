#include "domain/model/User/User.hpp"

#include <chrono>
#include <iostream>
#include <limits>
#include <thread>

// Updates a specific field in info.txt of the id.
void User::update_field_in_file(const std::string& id, const std::string& field, const std::string& newInput) {
    std::string path = get_file_path_from_id(id);

    if (path.empty()) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::ifstream inFile(path);
    if (!inFile.is_open()) {
        std::cerr << "Could not open file: " << path << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    bool updated = false;

    while (std::getline(inFile, line)) {
        if (line.substr(0, field.length() + 2) == field + ": ") {
            line = field + ": " + newInput;
            updated = true;
        }
        lines.push_back(line);
    }

    inFile.close();

    if (!updated) {
        std::cerr << "Field \"" << field << "\" not found in file.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    std::ofstream outFile(path);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing: " << path << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    for (const auto& newline : lines) {
        outFile << newline << '\n';
    }

    outFile.close();
    std::cout << field << " successfully updated.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

// Adds extra info in info.txt for the ID.
void User::add_extra_info(const std::string &id) {
    std::string path = get_file_path_from_id(id);

    if (path.empty()) {
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

    std::ofstream out(path, std::ios::app);
    if (!out.is_open()) {
        std::cerr << "Could not open file for writing.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    out << newLine << '\n';
    out.close();

    std::cout << "Extra Info added:\n" << newLine << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
