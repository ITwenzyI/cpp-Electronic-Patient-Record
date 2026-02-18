#include "application/usecase/UserProfileQueryService.hpp"

#include "common/result/ErrorCodes.hpp"
#include "common/result/ErrorSources.hpp"

UserProfileQueryService::UserProfileQueryService(IUserRepository& repository)
    : repository_(repository) {
}

Result<std::vector<std::string>> UserProfileQueryService::getUserInfo(const std::string& id) const {
    if (!repository_.exists(id)) {
        return Result<std::vector<std::string>>::failure(ErrorCodes::kUserNotFound,
            "Failed to read file!", ErrorSources::kApplication,
            "UserProfileQueryService::getUserInfo");
    }

    return Result<std::vector<std::string>>::success(repository_.readInfo(id));
}
