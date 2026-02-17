#ifndef IUSER_REPOSITORY_HPP
#define IUSER_REPOSITORY_HPP

#include <string>
#include <vector>

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual bool exists(const std::string& id) const = 0;
    virtual std::vector<std::string> readInfo(const std::string& id) const = 0;
    virtual bool writeInfo(const std::string& id, const std::vector<std::string>& lines) = 0;
    virtual bool appendInfoLine(const std::string& id, const std::string& line) = 0;
};

#endif //IUSER_REPOSITORY_HPP
