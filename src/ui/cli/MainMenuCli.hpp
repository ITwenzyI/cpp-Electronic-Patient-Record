#ifndef MAIN_MENU_CLI_HPP
#define MAIN_MENU_CLI_HPP

#include <string>

class MainMenuCli {
  public:
    std::string promptRoleSelection() const;
    void promptLoginIdentity(std::string& id, std::string& firstName, std::string& lastName) const;
};

#endif //MAIN_MENU_CLI_HPP
