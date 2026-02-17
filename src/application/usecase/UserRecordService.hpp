#ifndef USER_RECORD_SERVICE_HPP
#define USER_RECORD_SERVICE_HPP

#include "application/ports/IUserRepository.hpp"

#include <string>

class UserRecordService {
public:
    explicit UserRecordService(IUserRepository& repository);

    bool updateFieldInFile(const std::string& id, const std::string& field, const std::string& newInput) const;
    bool addExtraInfo(const std::string& id, const std::string& extraInfo) const;

private:
    IUserRepository& repository_;
};

#endif //USER_RECORD_SERVICE_HPP
