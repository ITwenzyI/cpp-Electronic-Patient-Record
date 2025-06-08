//
// Created by User on 07.06.2025.
//

#include "Utils.hpp"
#include <string>
#include <ctime>
#include <iomanip>
#include <random>

std::string getDate() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y");
    std::string dateStr = oss.str();
    return dateStr;
}

std::string getTime() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%H:%M:%S");
    std::string timeStr = oss.str();
    return timeStr;
}

int random_number(int min, int max) {
    std::random_device rd;                              // Zufallsquelle
    std::mt19937 gen(rd());                             // Mersenne Twister Generator
    std::uniform_int_distribution<> dist(min, max);        // Gleichverteilung von Anfang bis Ende
    int random = dist(gen);

    return random;
}