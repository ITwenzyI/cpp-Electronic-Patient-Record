
#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP

#include "domain/model/User/User.hpp"

class Assistant : public User {
    public:

    Assistant(const std::string& assistant_id,
            const std::string& firstName,
            const std::string& lastName);


    // If check_id_name is true, Menu will be displayed
    void displayMenu() override;

};



#endif //ASSISTANT_HPP
