#ifndef FILE_SYSTEM_REPOSITORY_HPP
#define FILE_SYSTEM_REPOSITORY_HPP

#include "application/ports/ISystemRepository.hpp"

class FileSystemRepository final : public ISystemRepository {
public:
    void ensureBootstrapData() override;
    bool hasAssistantsDirectory() const override;
    bool hasDoctorsDirectory() const override;
    void writeAdminSetupLog(const std::string& line) override;
    bool createUserBackupIfMissing(
        const std::string& id,
        const std::vector<std::string>& infoLines,
        std::string& outFolderName
    ) override;
};

#endif //FILE_SYSTEM_REPOSITORY_HPP
