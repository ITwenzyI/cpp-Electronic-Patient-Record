#include "ui/cli/ConsoleIO.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace ConsoleIO {
int promptInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

std::string promptToken(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::cin >> value;
    return value;
}

std::string promptLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin >> std::ws, value);
    return value;
}

void printHeader(const std::string& title) {
    std::cout << std::endl;
    std::cout << title << std::endl;
}

void printLines(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}

void pauseMilliseconds(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void pauseSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}
}
