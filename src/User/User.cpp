#include "User.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

User::User(const std::string& firstName, const std::string& lastName, const std::string& role)
    : firstName(firstName), lastName(lastName), role(role) { }


User::~User() = default;


// Getters

std::string User::getFirstName() const {
    return firstName;
}

std::string User::getLastName() const {
    return lastName;
}

std::string User::getRole() const {
    return role;
}

// Setters

void User::setFirstName(const std::string& firstName) {
    this->firstName = firstName;
}

void User::setLastName(const std::string& lastName) {
    this->lastName = lastName;
}


// Patient Folder Actions

void User::get_patient_info(const std::string &patient_full_id) {
    std::string path = "data/" + patient_full_id + "/info.txt"; // To call: User::get_patient_info("P00000006");
    std::ifstream file_in(path);
    std::string line;
    std::vector<std::string> content;

    if (file_in) {
        std::cout << "File Content:" << std::endl; // Ausgabe: Dateiinhalt:
        while (std::getline(file_in, line)) {
            std::cout << line << std::endl;        // Ausgabe: Zeile n
           content.push_back(line);                // Zeile speichern
        }
        file_in.close();
    } else {
        std::cerr << "Faild to read file!" << std::endl;
    }
}


