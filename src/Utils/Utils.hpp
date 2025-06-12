#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <ctime>
#include <iomanip>
#include <random>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>


// Returns Date in Format: DD.MM.YYYY
std::string getDate();


// Returns Time in Format: HH:MM:SS
std::string getTime();


// Returns Random Number between min and max
int random_number(int min, int max);


// Cleans a string from \r and white spaces ike \n \t ...
std::string cleaned(const std::string& str);



#endif //UTILS_HPP
