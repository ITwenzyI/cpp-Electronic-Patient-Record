#include "ui/cli/EprCliApplication.hpp"

#include "application/usecase/LoginDecisionUseCase.hpp"
#include "application/usecase/SystemBootstrapUseCase.hpp"
#include "application/usecase/UserSessionService.hpp"
#include "common/result/ErrorCodes.hpp"
#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Doctor/Doctor.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "ui/cli/Admin/Admin.hpp"
#include "ui/cli/AssistantMenuController.hpp"
#include "ui/cli/ConsoleIO.hpp"
#include "ui/cli/DoctorMenuController.hpp"
#include "ui/cli/MainMenuCli.hpp"
#include "ui/cli/PatientMenuController.hpp"

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

namespace {
const UserSessionService& userSessionService() {
    static UserSessionService service;
    return service;
}

const LoginDecisionUseCase& loginDecisionUseCase() {
    static LoginDecisionUseCase useCase;
    return useCase;
}

const SystemBootstrapUseCase& systemBootstrapUseCase() {
    static SystemBootstrapUseCase useCase;
    return useCase;
}

const MainMenuCli& mainMenuCli() {
    static MainMenuCli cli;
    return cli;
}
}

int EprCliApplication::run() {
    systemBootstrapUseCase().run();

    int choice;

    do {
        std::string input = mainMenuCli().promptRoleSelection();

        const LoginDecision decision = loginDecisionUseCase().decide(input);

        if (decision.action == LoginAction::AdminSetup) {
            Admin::admin_setup();
            continue;
        }

        if (decision.action == LoginAction::InvalidInput) {
            std::cout << "Invalid input.\n";
            return 0;
        }

        choice = decision.roleChoice;
        if (decision.action == LoginAction::ExitApplication) {
            std::cout << "Exiting...\n";
            return 0;
        }

        std::string firstName, lastName;
        std::string id;
        mainMenuCli().promptLoginIdentity(id, firstName, lastName);

        const Result<void> sessionResult = userSessionService().runRoleSession(choice, id, firstName, lastName);
        if (!sessionResult) {
            ConsoleIO::printError(sessionResult.error());
            if (sessionResult.errorCode() == ErrorCodes::kUserNotFound) {
                ConsoleIO::pauseSeconds(2);
            } else if (sessionResult.errorCode() == ErrorCodes::kAuthNameMismatch) {
                ConsoleIO::pauseSeconds(3);
            }
            continue;
        }

        std::cout << std::endl;
        std::cout << "Login successful.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (choice == 1) {
            Patient patient(id, firstName, lastName);
            runPatientMenu(patient);
        } else if (choice == 2) {
            Doctor doctor(id, firstName, lastName);
            runDoctorMenu(doctor);
        } else if (choice == 3) {
            Assistant assistant(id, firstName, lastName);
            runAssistantMenu(assistant);
        }
    } while (choice != 0);

    return 0;
}
