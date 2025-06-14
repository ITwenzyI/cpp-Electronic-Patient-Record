
#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include "../User/User.hpp"
#include "../Utils/Utils.hpp"
#include "../IDs/IDs.hpp"
#include "../Patient/Patient.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

class Doctor : public User {
    public:

    // Constructor
    Doctor(const std::string& doctor_id,
            const std::string& firstName,
            const std::string& lastName);


    // If check_id_name is true, Menu will be displayed
    void displayMenu() override;

    // Checks if ID and firstName and lastName of info.txt match.
    void check_id_name(std::string id, std::string firstName, std::string lastName) override;

    // Doctor Folder Actions
    void createNewDoctor() const;
    static void get_doctor_info(const std::string &doctor_full_id);
    void fill_doctor_info();

};

#endif //DOCTOR_HPP
