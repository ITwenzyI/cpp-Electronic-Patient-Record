#ifndef LOGIN_DECISION_USE_CASE_HPP
#define LOGIN_DECISION_USE_CASE_HPP

#include <string>

enum class LoginAction { AdminSetup, ExitApplication, StartRoleSession, InvalidInput };

struct LoginDecision {
    LoginAction action;
    int roleChoice;
};

class LoginDecisionUseCase {
  public:
    LoginDecision decide(const std::string& input) const;
};

#endif //LOGIN_DECISION_USE_CASE_HPP
