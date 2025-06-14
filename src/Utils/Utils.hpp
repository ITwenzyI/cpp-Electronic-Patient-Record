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
#include <format>


// Returns Date in Format: YYYY-MM-DD
std::string getDate();


// Returns Time in Format: HH:MM:SS
std::string getTime();


// Returns Random Number between min and max
int random_number(int min, int max);


// Cleans a string from \r and white spaces ike \n \t ...
std::string cleaned(const std::string& str);


// Gets the correct Path from the ID so for D0001 it's Doctors...
std::string get_file_path_from_id(const std::string& id);



#endif //UTILS_HPP
