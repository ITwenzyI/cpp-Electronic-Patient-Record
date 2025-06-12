#include "IDs.hpp"


#include <string>
#include <ctime>
#include <iomanip>
#include <random>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>


/// ------------------------- Patient ---------------------------------------------------

int Patient_ID::get_patient_id() {
    std::ifstream file_in("data/patient_id.txt");
    int id;
    if (file_in.is_open()) {
        file_in >> id;
        file_in.close();
    } else {
        std::cerr << "Failed to open and get ID from Patient!\n";
    }
    return id;
}

void Patient_ID::update_patient_id(const int old_id) {
    std::ofstream file_out("data/patient_id.txt");
    if (file_out.is_open()) {
        file_out << old_id + 1;
        file_out.close();
    } else {
        std::cerr << "Failed to open and update ID from Patient!\n";
    }
}


/// ------------------------- Assistant ---------------------------------------------------


int Assistant_ID::get_assistant_id() {
    std::ifstream file_in("data/assistant_id.txt");
    int id;
    if (file_in.is_open()) {
        file_in >> id;
        file_in.close();
    } else {
        std::cerr << "Failed to open and get ID from Assistant!\n";
    }
    return id;
}

void Assistant_ID::update_assistant_id(const int old_id) {
    std::ofstream file_out("data/assistant_id.txt");
    if (file_out.is_open()) {
        file_out << old_id + 1;
        file_out.close();
    } else {
        std::cerr << "Failed to open and update ID from Assistant!\n";
    }
}




/// ------------------------- Doctor ---------------------------------------------------



int Doctor_ID::get_doctor_id() {
    std::ifstream file_in("data/doctor_id.txt");
    int id;
    if (file_in.is_open()) {
        file_in >> id;
        file_in.close();
    } else {
        std::cerr << "Failed to open and get ID from Doctor!\n";
    }
    return id;
}

void Doctor_ID::update_doctor_id(const int old_id) {
    std::ofstream file_out("data/doctor_id.txt");
    if (file_out.is_open()) {
        file_out << old_id + 1;
        file_out.close();
    } else {
        std::cerr << "Failed to open and update ID from Doctor!\n";
    }
}


