
#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP
#include "../User/User.hpp"

class Assistant : public User {
    public:

    Assistant(const std::string& assistant_id,
            const std::string& firstName,
            const std::string& lastName);

    //Desturctor


    void displayMenu() override;
    void check_id_name(std::string id, std::string firstName, std::string lastName) override;

    // Assistant Folder Actions
    static void createNewAssistant(const std::string& firstName, const std::string& lastName);
    static void get_assistant_info(const std::string &assistant_full_id);

};



#endif //ASSISTANT_HPP
