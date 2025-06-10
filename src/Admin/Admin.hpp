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

    static void createNewPatient(const std::string& firstName, const std::string& lastName);

    static void createNewAssistant(const std::string& firstName, const std::string& lastName);

    static void createNewDoctor(const std::string& firstName, const std::string& lastName);
};

#endif //ADMIN_HPP
