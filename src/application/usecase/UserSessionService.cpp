#include "application/usecase/UserSessionService.hpp"

#include "application/ports/IUserRepository.hpp"
#include "application/usecase/AuthService.hpp"
#include "common/result/ErrorCodes.hpp"
#include "common/result/ErrorSources.hpp"
#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"
#include "ui/cli/AssistantMenuController.hpp"
#include "ui/cli/DoctorMenuController.hpp"
#include "ui/cli/PatientMenuController.hpp"

#include <chrono>
#include <iostream>
#include <thread>

namespace {
IUserRepository& userRepository() {
    static FileUserRepository repository;
    return repository;
}

const AuthService& authService() {
    static AuthService service(userRepository());
    return service;
}
}

Result<void> UserSessionService::runRoleSession(
    const int choice,
    const std::string& id,
    const std::string& firstName,
    const std::string& lastName
) const {
    const Result<void> authResult = authService().authenticate(id, firstName, lastName);
    if (!authResult) {
        return authResult;
    }

    std::cout << std::endl;
    std::cout << "Login successful.\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));

    switch (choice) {
        case 1: {
            Patient p(id, firstName, lastName);
            runPatientMenu(p);
            break;
        }
        case 2: {
            Doctor d(id, firstName, lastName);
            runDoctorMenu(d);
            break;
        }
        case 3: {
            Assistant a(id, firstName, lastName);
            runAssistantMenu(a);
            break;
        }
        default:
            return Result<void>::failure(
                ErrorCodes::kInvalidSelection, "Invalid selection.", ErrorSources::kApplication, "UserSessionService::runRoleSession"
            );
    }

    return Result<void>::success();
}
