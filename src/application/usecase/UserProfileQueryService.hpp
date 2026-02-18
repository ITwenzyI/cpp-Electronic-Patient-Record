#ifndef USER_PROFILE_QUERY_SERVICE_HPP
#define USER_PROFILE_QUERY_SERVICE_HPP

#include "application/ports/IUserRepository.hpp"

#include <string>
#include <vector>

class UserProfileQueryService {
public:
    explicit UserProfileQueryService(IUserRepository& repository);

    std::vector<std::string> getUserInfo(const std::string& id) const;

private:
    IUserRepository& repository_;
};

#endif //USER_PROFILE_QUERY_SERVICE_HPP
