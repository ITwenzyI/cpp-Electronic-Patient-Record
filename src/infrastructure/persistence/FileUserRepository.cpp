#include "infrastructure/persistence/FileUserRepository.hpp"

#include "common/util/Utils/Utils.hpp"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

bool FileUserRepository::exists(const std::string& id) const {
    const std::string path = get_file_path_from_id(id);
    if (path.empty()) {
        return false;
    }

    return std::filesystem::exists(path);
}

std::vector<std::string> FileUserRepository::readInfo(const std::string& id) const {
    const std::string path = get_file_path_from_id(id);
    std::vector<std::string> lines;

    if (path.empty()) {
        return lines;
    }

    std::ifstream in(path);
    if (!in.is_open()) {
        return lines;
    }

    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }

    return lines;
}

bool FileUserRepository::writeInfo(const std::string& id, const std::vector<std::string>& lines) {
    const std::string path = get_file_path_from_id(id);
    if (path.empty()) {
        return false;
    }

    std::ofstream out(path);
    if (!out.is_open()) {
        return false;
    }

    for (const auto& line : lines) {
        out << line << '\n';
    }

    return true;
}

bool FileUserRepository::appendInfoLine(const std::string& id, const std::string& line) {
    const std::string path = get_file_path_from_id(id);
    if (path.empty()) {
        return false;
    }

    std::ofstream out(path, std::ios::app);
    if (!out.is_open()) {
        return false;
    }

    out << line << '\n';
    return true;
}
