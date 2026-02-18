
#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP

#include "domain/model/User/User.hpp"

class Assistant : public User {
    public:

    Assistant(const std::string& assistant_id,
            const std::string& firstName,
            const std::string& lastName);

};



#endif //ASSISTANT_HPP
