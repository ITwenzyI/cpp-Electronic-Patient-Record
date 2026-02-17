#include "application/usecase/LoginDecisionUseCase.hpp"

LoginDecision LoginDecisionUseCase::decide(const std::string& input) const {
    if (input == "#admin") {
        return {LoginAction::AdminSetup, -1};
    }

    int choice = -1;
    try {
        choice = std::stoi(input);
    } catch (...) {
        return {LoginAction::InvalidInput, -1};
    }

    if (choice == 0) {
        return {LoginAction::ExitApplication, 0};
    }

    return {LoginAction::StartRoleSession, choice};
}
