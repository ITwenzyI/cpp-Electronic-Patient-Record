#include "application/usecase/UserSessionService.hpp"

#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"

#include <iostream>

void UserSessionService::runRoleSession(
    const int choice,
    const std::string& id,
    const std::string& firstName,
    const std::string& lastName
) const {
    switch (choice) {
        case 1: {
            Patient p(id, firstName, lastName);
            p.check_id_name(id, firstName, lastName);
            break;
        }
        case 2: {
            Doctor d(id, firstName, lastName);
            d.check_id_name(id, firstName, lastName);
            break;
        }
        case 3: {
            Assistant a(id, firstName, lastName);
            a.check_id_name(id, firstName, lastName);
            break;
        }
        default:
            std::cout << "Invalid selection.\n";
            break;
    }
}
