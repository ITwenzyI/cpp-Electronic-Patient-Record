#include "application/usecase/UserRecordService.hpp"

#include "common/util/Utils/Utils.hpp"

#include <vector>

UserRecordService::UserRecordService(IUserRepository& repository)
    : repository_(repository) {}

bool UserRecordService::updateFieldInFile(
    const std::string& id,
    const std::string& field,
    const std::string& newInput
) const {
    if (!repository_.exists(id)) {
        return false;
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
        return false;
    }

    return repository_.writeInfo(id, lines);
}

bool UserRecordService::addExtraInfo(const std::string& id, const std::string& extraInfo) const {
    if (!repository_.exists(id)) {
        return false;
    }

    const std::string line = "[" + getDate() + "] " + extraInfo + "\n";
    return repository_.appendInfoLine(id, line);
}
