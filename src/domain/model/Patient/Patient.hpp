

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include "domain/model/User/User.hpp"

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



    static void get_patient_info(const std::string &patient_full_id);
    void fill_patient_info();
    static void add_patient_appointment(const std::string &patient_full_id);
    static void add_patient_medication(const std::string &patient_full_id);
    static void add_patient_record(const std::string &patient_full_id);
    static void get_patient_appointments(const std::string &patient_full_id);
    static void get_patient_medications(const std::string &patient_full_id);
    static void get_patient_records(const std::string &patient_full_id);
    static void request_appointment(const std::string &patient_full_id);


};

#endif //PATIENT_HPP
