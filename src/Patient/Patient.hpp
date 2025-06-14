

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "../User/User.hpp"
#include "../Utils/Utils.hpp"
#include "../IDs/IDs.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <chrono>

class Patient : public User {
public:
    // Constructor
    Patient(const std::string& patient_id,
            const std::string& firstName,
            const std::string& lastName);




    // If check_id_name is true, Menu will be displayed
    void displayMenu() override;

    // Checks if ID and firstName and lastName of info.txt match.
    void check_id_name(std::string id, std::string firstName, std::string lastName) override;



    // Patient Folder Actions
    void createNewPatient() const;
    static void get_patient_info(const std::string &patient_full_id);
    void fill_patient_info();
    //static void get_patient_appointments(const std::string &patient_full_id);
    //static void get_patient_medications(const std::string &patient_full_id);
    //static void get_patient_records(const std::string &patient_full_id);


};

#endif //PATIENT_HPP
