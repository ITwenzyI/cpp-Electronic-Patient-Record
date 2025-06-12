//
// Created by User on 07.06.2025.
//

#include "Utils.hpp"
#include <string>
#include <ctime>
#include <iomanip>
#include <random>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>

std::string getDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y"); // Example 13.06.2006
    std::string dateStr = oss.str();
    return dateStr;
}

std::string getTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S"); // Example: 12:30:32
    std::string timeStr = oss.str();
    return timeStr;
}

int random_number(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    int random = dist(gen);

    return random;
}

std::string cleaned(const std::string& str) {
    std::string result = str;
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    result.erase(std::remove_if(result.begin(), result.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));
    }), result.end());
    return result;
}
