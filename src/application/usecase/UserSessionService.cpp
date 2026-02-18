#include "application/usecase/UserSessionService.hpp"

#include "application/ports/IUserRepository.hpp"
#include "application/usecase/AuthService.hpp"
#include "common/result/ErrorCodes.hpp"
#include "common/result/ErrorSources.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"

namespace {
IUserRepository& userRepository() {
    static FileUserRepository repository;
    return repository;
}

const AuthService& authService() {
    static AuthService service(userRepository());
    return service;
}
} // namespace

Result<void> UserSessionService::runRoleSession(const int choice, const std::string& id,
    const std::string& firstName, const std::string& lastName) const {
    // Session service validates role and credentials only; no UI dispatch here.
    if (choice < 1 || choice > 3) {
        return Result<void>::failure(ErrorCodes::kInvalidSelection, "Invalid selection.",
            ErrorSources::kApplication, "UserSessionService::runRoleSession");
    }

    const Result<void> authResult = authService().authenticate(id, firstName, lastName);
    if (!authResult) {
        return authResult;
    }

    return Result<void>::success();
}
