
#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP

#include "../User/User.hpp"
#include "../Patient/Patient.hpp"
#include "../Utils/Utils.hpp"
#include "../IDs/IDs.hpp"
#include "../Admin/Admin.hpp"


#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <chrono>

class Assistant : public User {
    public:

    Assistant(const std::string& assistant_id,
            const std::string& firstName,
            const std::string& lastName);


    // If check_id_name is true, Menu will be displayed
    void displayMenu() override;

    // Checks if ID and firstName and lastName of info.txt match.
    void check_id_name(std::string id, std::string firstName, std::string lastName) override;

    // Assistant Folder Actions
    void createNewAssistant() const;
    static void get_assistant_info(const std::string &assistant_full_id);
    void fill_assistant_info();
    static void review_appointments();

};



#endif //ASSISTANT_HPP
