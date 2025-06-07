#include <iostream>
#include <string>



#include "src/User/User.hpp"
#include "src/Patient/Patient.hpp"
#include "src/Doctor/Doctor.hpp"
#include "src/Assistant/Assistant.hpp"

int main() {
    Patient p = Patient("Kilian1", "Second");
    User *k = new Patient("Kilian2", "König");
    std::cout << p.getFirstName() << std::endl;
    std::cout << k->getFirstName() << std::endl;
    std::cout << p.getRole() << std::endl;

    return 0;
}