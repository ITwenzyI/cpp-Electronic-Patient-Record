

#include "IDs.hpp"
#include <string>
#include <ctime>
#include <iomanip>
#include <random>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>


int Patient_ID::get_patient_id() {
    std::ifstream file_in("data/patient_id.txt");
    int id;
    if (file_in.is_open()) {
        file_in >> id;
        file_in.close();
    } else {
        std::cerr << "Faild to open and get ID!\n";
    }
    return id;
}

void Patient_ID::update_patient_id(int old_id) {
    std::ofstream file_out("data/patient_id.txt");
    if (file_out.is_open()) {
        file_out << old_id + 1;
        file_out.close();
    } else {
        std::cerr << "Faild to open and update ID!\n";
    }
}
