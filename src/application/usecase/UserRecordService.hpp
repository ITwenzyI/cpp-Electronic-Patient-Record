#ifndef USER_RECORD_SERVICE_HPP
#define USER_RECORD_SERVICE_HPP

#include "application/ports/IUserRepository.hpp"
#include "common/result/Result.hpp"

#include <string>

class UserRecordService {
  public:
    explicit UserRecordService(IUserRepository& repository);

    Result<void> updateFieldInFile(
        const std::string& id, const std::string& field, const std::string& newInput) const;
    Result<void> addExtraInfo(const std::string& id, const std::string& extraInfo) const;

  private:
    IUserRepository& repository_;
};

#endif //USER_RECORD_SERVICE_HPP
