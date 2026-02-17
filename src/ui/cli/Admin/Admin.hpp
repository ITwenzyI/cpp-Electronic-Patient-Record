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
#include "common/util/Utils/Utils.hpp"
#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "domain/model/Doctor/Doctor.hpp"


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

    static void exportUserData(const std::string& id);
};

#endif //ADMIN_HPP
