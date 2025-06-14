/*
 * File: Admin
 * Author: Kilian | ItwenzyI
 * Created: 10.06.2025
 * Description: 
 */
//

#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "Admin.hpp"
#include "../Utils/Utils.hpp"
#include "../Assistant/Assistant.hpp"
#include "../Patient/Patient.hpp"
#include "../Doctor/Doctor.hpp"


#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>


class Admin {
public:
    Admin();
    ~Admin();

    static bool checkInitialSetup();

    static void admin_setup();

    static void admin_getNames(std::string &firstName, std::string &lastName);
};

#endif //ADMIN_HPP
