#include "Utils.hpp"

std::string getDate() {
    const std::time_t t = std::time(nullptr);
    const std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y"); // Example 13.06.2006
    std::string dateStr = oss.str();
    return dateStr;
}

std::string getTime() {
    const std::time_t t = std::time(nullptr);
    const std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S"); // Example: 12:30:32
    std::string timeStr = oss.str();
    return timeStr;
}

int random_number(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    const int random = dist(gen);

    return random;
}

std::string cleaned(const std::string& str) {
    std::string result = str;
    std::erase(result, '\r');
    std::erase_if(result, [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    });
    return result;
}

std::string get_file_path_from_id(const std::string& id) {
    if (id.empty()) return "";

    const char rolePrefix = id[0];  // Example: 'P', 'D', 'A'
    std::string folder;

    switch (rolePrefix) {
        case 'P': folder = "Patients"; break;
        case 'D': folder = "Doctors"; break;
        case 'A': folder = "Assistants"; break;
        default: return "";  // Unknown Type
    }

    std::string path = "data/" + folder + "/" + id + "/info.txt";

    return path;
}

