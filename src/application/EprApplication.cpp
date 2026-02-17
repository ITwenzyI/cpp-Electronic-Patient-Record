#include "application/EprApplication.hpp"

#include "application/usecase/LoginDecisionUseCase.hpp"
#include "application/usecase/SystemBootstrapUseCase.hpp"
#include "application/usecase/UserSessionService.hpp"
#include "ui/cli/Admin/Admin.hpp"
#include "ui/cli/MainMenuCli.hpp"

#include <iostream>
#include <string>

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

int EprApplication::run() {
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

        userSessionService().runRoleSession(choice, id, firstName, lastName);
    } while (choice != 0);

    return 0;
}
