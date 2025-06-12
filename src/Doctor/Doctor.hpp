
#ifndef DOCTOR_HPP
#define DOCTOR_HPP
#include "../User/User.hpp"
#include "../Utils/Utils.hpp"

class Doctor : public User {
    public:

    // Constructor
    Doctor(const std::string& doctor_id,
            const std::string& firstName,
            const std::string& lastName);

    //Destructor

    void displayMenu() override;
    void check_id_name(std::string id, std::string firstName, std::string lastName) override;

    // Doctor Folder Actions
    static void createNewDoctor(const std::string& firstName, const std::string& lastName);
    static void get_doctor_info(const std::string &doctor_full_id);

};

#endif //DOCTOR_HPP
