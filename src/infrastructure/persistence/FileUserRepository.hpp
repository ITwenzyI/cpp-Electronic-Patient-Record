#ifndef FILE_USER_REPOSITORY_HPP
#define FILE_USER_REPOSITORY_HPP

#include "application/ports/IUserRepository.hpp"

class FileUserRepository final : public IUserRepository {
  public:
    bool exists(const std::string& id) const override;
    std::vector<std::string> readInfo(const std::string& id) const override;
    bool writeInfo(const std::string& id, const std::vector<std::string>& lines) override;
    bool appendInfoLine(const std::string& id, const std::string& line) override;
};

#endif //FILE_USER_REPOSITORY_HPP
