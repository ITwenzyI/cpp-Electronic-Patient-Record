#include "application/usecase/AuthService.hpp"

#include "common/result/ErrorCodes.hpp"
#include "common/result/ErrorSources.hpp"
#include "common/util/Utils/Utils.hpp"

#include <vector>

namespace {
std::string extractField(const std::vector<std::string>& lines, const std::string& keyPrefix) {
    // info.txt entries are line-based key/value pairs like "First Name: John".
    for (const auto& line : lines) {
        if (line.starts_with(keyPrefix)) {
            return line.substr(keyPrefix.size());
        }
    }
    return "";
}
}

AuthService::AuthService(IUserRepository& repository)
    : repository_(repository) {}

Result<void> AuthService::authenticate(
    const std::string& id,
    const std::string& firstName,
    const std::string& lastName
) const {
    if (!repository_.exists(id)) {
        return Result<void>::failure(
            ErrorCodes::kUserNotFound, "Failed to read file!", ErrorSources::kApplication, "AuthService::authenticate"
        );
    }

    // Compare normalized strings to keep compatibility with existing text-file data.
    const std::vector<std::string> info = repository_.readInfo(id);
    const std::string fileFirstName = extractField(info, "First Name:");
    const std::string fileLastName = extractField(info, "Last Name:");

    if (cleaned(fileFirstName) == cleaned(firstName) &&
        cleaned(fileLastName) == cleaned(lastName)) {
        return Result<void>::success();
    }

    return Result<void>::failure(
        ErrorCodes::kAuthNameMismatch, "Name does not match the ID.", ErrorSources::kApplication, "AuthService::authenticate"
    );
}
