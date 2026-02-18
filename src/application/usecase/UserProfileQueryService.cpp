#include "application/usecase/UserProfileQueryService.hpp"

UserProfileQueryService::UserProfileQueryService(IUserRepository& repository)
    : repository_(repository) {}

Result<std::vector<std::string>> UserProfileQueryService::getUserInfo(const std::string& id) const {
    if (!repository_.exists(id)) {
        return Result<std::vector<std::string>>::failure("USER_NOT_FOUND", "Failed to read file!");
    }

    return Result<std::vector<std::string>>::success(repository_.readInfo(id));
}
