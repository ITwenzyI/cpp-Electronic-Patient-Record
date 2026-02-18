#include "application/usecase/UserRecordService.hpp"

#include "common/util/Utils/Utils.hpp"

#include <vector>

UserRecordService::UserRecordService(IUserRepository& repository)
    : repository_(repository) {}

Result<void> UserRecordService::updateFieldInFile(
    const std::string& id,
    const std::string& field,
    const std::string& newInput
) const {
    if (!repository_.exists(id)) {
        return Result<void>::failure("USER_NOT_FOUND", "Invalid ID.");
    }

    std::vector<std::string> lines = repository_.readInfo(id);
    bool updated = false;

    for (auto& line : lines) {
        if (line.substr(0, field.length() + 2) == field + ": ") {
            line = field + ": " + newInput;
            updated = true;
        }
    }

    if (!updated) {
        return Result<void>::failure("FIELD_NOT_FOUND", "Field does not exist in user info.");
    }

    if (!repository_.writeInfo(id, lines)) {
        return Result<void>::failure("WRITE_FAILED", "Could not update field in file.");
    }

    return Result<void>::success();
}

Result<void> UserRecordService::addExtraInfo(const std::string& id, const std::string& extraInfo) const {
    if (!repository_.exists(id)) {
        return Result<void>::failure("USER_NOT_FOUND", "Invalid ID.");
    }

    const std::string line = "[" + getDate() + "] " + extraInfo + "\n";
    if (!repository_.appendInfoLine(id, line)) {
        return Result<void>::failure("WRITE_FAILED", "Could not open file for writing.");
    }

    return Result<void>::success();
}
