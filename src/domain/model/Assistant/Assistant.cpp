#include "Assistant.hpp"

Assistant::Assistant(const std::string& assistant_id,
                 const std::string& firstName,
                 const std::string& lastName)
    : User(assistant_id, UserRole::Assistant, firstName, lastName,
           "", "", "", "", "", "", "", "") {}




