#include "application/usecase/UserProfileQueryService.hpp"

UserProfileQueryService::UserProfileQueryService(IUserRepository& repository)
    : repository_(repository) {}

std::vector<std::string> UserProfileQueryService::getUserInfo(const std::string& id) const {
    return repository_.readInfo(id);
}
