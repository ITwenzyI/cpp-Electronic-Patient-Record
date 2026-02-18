#include <iostream>

bool runPatientWriteServiceSmokeTests();
bool runUserRecordServiceSmokeTests();

int main() {
    if (!runPatientWriteServiceSmokeTests()) {
        return 1;
    }

    if (!runUserRecordServiceSmokeTests()) {
        return 1;
    }

    std::cout << "All use-case smoke tests passed\n";
    return 0;
}
