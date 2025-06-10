/*
 * File: Admin
 * Author: Kilian | ItwenzyI
 * Created: 10.06.2025
 * Description: 
 */
//

#include "Admin.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

#include "../Utils/Utils.hpp"

bool Admin::checkInitialSetup() {
    if (!std::filesystem::exists("data/Patients") && !std::filesystem::exists("data/Assistants") && !std::filesystem::exists("data/Doctors")) {

        std::ofstream out("data/admin_logging.txt");
        out << "Admin Logging at: " << getDate() << " " << getTime() << "\n\n"; // Initialvalue
        out.close();

        std::cout << "[!] No user structure found.\n";
        std::cout << "→ Entering admin setup mode...\n";

        return false;

    } else {
        return true;
    }
}
