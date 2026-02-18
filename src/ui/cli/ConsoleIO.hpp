#ifndef CONSOLE_IO_HPP
#define CONSOLE_IO_HPP

#include "common/result/Result.hpp"

#include <string>
#include <vector>

namespace ConsoleIO {
int promptInt(const std::string& prompt);
std::string promptToken(const std::string& prompt);
std::string promptLine(const std::string& prompt);
void printHeader(const std::string& title);
void printLines(const std::vector<std::string>& lines);
void printError(const Error& error);
void pauseMilliseconds(int milliseconds);
void pauseSeconds(int seconds);
} // namespace ConsoleIO

#endif // CONSOLE_IO_HPP
