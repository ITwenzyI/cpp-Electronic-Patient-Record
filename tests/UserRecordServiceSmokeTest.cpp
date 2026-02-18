#include "application/usecase/UserRecordService.hpp"
#include "common/result/ErrorCodes.hpp"

#include <iostream>
#include <string>
#include <vector>

namespace {
class FakeUserRepository final : public IUserRepository {
  public:
    bool existsResult = true;
    bool writeInfoResult = true;
    bool appendInfoLineResult = true;

    std::vector<std::string> infoLines;
    std::vector<std::string> writtenLines;
    std::string appendedLine;

    bool exists(const std::string&) const override {
        return existsResult;
    }

    std::vector<std::string> readInfo(const std::string&) const override {
        return infoLines;
    }

    bool writeInfo(const std::string&, const std::vector<std::string>& lines) override {
        writtenLines = lines;
        return writeInfoResult;
    }

    bool appendInfoLine(const std::string&, const std::string& line) override {
        appendedLine = line;
        return appendInfoLineResult;
    }
};

bool testUpdateFieldInFileUpdatesMatchingField() {
    FakeUserRepository repository;
    repository.infoLines = {"First Name: John", "Last Name: Doe", "Insurance ID: OLD"};
    UserRecordService service(repository);

    const Result<void> result = service.updateFieldInFile("P12345678", "Insurance ID", "NEW");

    return result && repository.writtenLines.size() == 3 &&
        repository.writtenLines[2] == "Insurance ID: NEW";
}

bool testUpdateFieldInFileReturnsUserNotFoundWhenMissing() {
    FakeUserRepository repository;
    repository.existsResult = false;
    UserRecordService service(repository);

    const Result<void> result = service.updateFieldInFile("P12345678", "Insurance ID", "NEW");

    return !result && result.errorCode() == ErrorCodes::kUserNotFound;
}

bool testAddExtraInfoReturnsWriteFailedWhenAppendFails() {
    FakeUserRepository repository;
    repository.appendInfoLineResult = false;
    UserRecordService service(repository);

    const Result<void> result = service.addExtraInfo("P12345678", "New note");

    return !result && result.errorCode() == ErrorCodes::kWriteFailed;
}
} // namespace

bool runUserRecordServiceSmokeTests() {
    if (!testUpdateFieldInFileUpdatesMatchingField()) {
        std::cerr << "testUpdateFieldInFileUpdatesMatchingField failed\n";
        return false;
    }

    if (!testUpdateFieldInFileReturnsUserNotFoundWhenMissing()) {
        std::cerr << "testUpdateFieldInFileReturnsUserNotFoundWhenMissing failed\n";
        return false;
    }

    if (!testAddExtraInfoReturnsWriteFailedWhenAppendFails()) {
        std::cerr << "testAddExtraInfoReturnsWriteFailedWhenAppendFails failed\n";
        return false;
    }

    std::cout << "UserRecordService smoke tests passed\n";
    return true;
}
