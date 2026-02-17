#include "infrastructure/persistence/FileSystemRepository.hpp"

#include <filesystem>
#include <fstream>
#include <format>

void FileSystemRepository::ensureBootstrapData() {
    std::filesystem::create_directories("data");

    if (!std::filesystem::exists("data/patient_id.txt")) {
        std::ofstream out("data/patient_id.txt");
        out << "1";
    }

    if (!std::filesystem::exists("data/assistant_id.txt")) {
        std::ofstream out("data/assistant_id.txt");
        out << "1";
    }

    if (!std::filesystem::exists("data/doctor_id.txt")) {
        std::ofstream out("data/doctor_id.txt");
        out << "1";
    }
}

bool FileSystemRepository::hasAssistantsDirectory() const {
    return std::filesystem::exists("data/Assistants");
}

bool FileSystemRepository::hasDoctorsDirectory() const {
    return std::filesystem::exists("data/Doctors");
}

void FileSystemRepository::writeAdminSetupLog(const std::string& line) {
    std::ofstream out("data/admin_logging.txt");
    out << line;
}

bool FileSystemRepository::createUserBackupIfMissing(
    const std::string& id,
    const std::vector<std::string>& infoLines,
    std::string& outFolderName
) {
    std::filesystem::create_directories("data/Exports");
    outFolderName = std::format("data/Exports/{}", id);
    std::filesystem::create_directories(outFolderName);

    const std::string backupPath = outFolderName + "/backup_info.txt";
    if (!std::filesystem::exists(backupPath)) {
        std::ofstream out(backupPath);
        if (!out.is_open()) {
            return false;
        }
        for (const auto& line : infoLines) {
            out << line << "\n";
        }
    }

    return true;
}
