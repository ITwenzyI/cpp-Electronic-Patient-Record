#ifndef USER_SESSION_SERVICE_HPP
#define USER_SESSION_SERVICE_HPP

#include <string>

class UserSessionService {
public:
    void runRoleSession(int choice, const std::string& id, const std::string& firstName, const std::string& lastName) const;
};

#endif //USER_SESSION_SERVICE_HPP
