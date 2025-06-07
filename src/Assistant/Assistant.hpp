
#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP
#include "../User/User.hpp"

class Assistant : public User {
    public:

    Assistant(const std::string& firstName, const std::string& lastName);

    //Desturctor
    virtual ~Assistant();

    void displayMenu() override;
};



#endif //ASSISTANT_HPP
