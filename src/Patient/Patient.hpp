

#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "../User/User.hpp"

class Patient : public User {
public:
    // Constructor
    Patient(const std::string& patient_id,
            const std::string& firstName,
            const std::string& lastName);

    // Destructor

    

    void displayMenu() override;



    // Patient Folder Actions
    static void createNewPatient(const std::string& firstName, const std::string& lastName);
    static void get_patient_info(const std::string &patient_full_id);
    //static void get_patient_appointments(const std::string &patient_full_id);
    //static void get_patient_medications(const std::string &patient_full_id);
    //static void get_patient_records(const std::string &patient_full_id);


};

#endif //PATIENT_HPP
