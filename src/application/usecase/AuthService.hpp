#ifndef AUTH_SERVICE_HPP
#define AUTH_SERVICE_HPP

#include "application/ports/IUserRepository.hpp"
#include "common/result/Result.hpp"

#include <string>

class AuthService {
  public:
    explicit AuthService(IUserRepository& repository);

    Result<void> authenticate(
        const std::string& id, const std::string& firstName, const std::string& lastName) const;

  private:
    IUserRepository& repository_;
};

#endif // AUTH_SERVICE_HPP
