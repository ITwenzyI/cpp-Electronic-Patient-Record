
#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include "domain/model/User/User.hpp"
#include "common/util/Utils/Utils.hpp"
#include "infrastructure/persistence/IDs/IDs.hpp"
#include "domain/model/Patient/Patient.hpp"

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
