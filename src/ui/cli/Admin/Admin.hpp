/*
 * File: Admin
 * Author: Kilian | ItwenzyI
 * Created: 10.06.2025
 * Description: 
 */
//

#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <string>


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
