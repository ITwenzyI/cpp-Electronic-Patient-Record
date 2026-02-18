#ifndef ISYSTEM_REPOSITORY_HPP
#define ISYSTEM_REPOSITORY_HPP

#include <string>
#include <vector>

class ISystemRepository {
  public:
    virtual ~ISystemRepository() = default;

    virtual void ensureBootstrapData() = 0;
    virtual bool hasAssistantsDirectory() const = 0;
    virtual bool hasDoctorsDirectory() const = 0;
    virtual void writeAdminSetupLog(const std::string& line) = 0;
    virtual bool createUserBackupIfMissing(const std::string& id,
        const std::vector<std::string>& infoLines, std::string& outFolderName) = 0;
};

#endif //ISYSTEM_REPOSITORY_HPP
