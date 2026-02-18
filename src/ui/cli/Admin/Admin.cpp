/*
 * File: Admin
 * Author: Kilian | ItwenzyI
 * Created: 10.06.2025
 * Description: 
 */
//

#include "Admin.hpp"

#include "application/ports/ISystemRepository.hpp"
#include "application/ports/IUserRepository.hpp"
#include "application/usecase/PatientRecordQueryService.hpp"
#include "application/usecase/UserProfileQueryService.hpp"
#include "application/usecase/UserRecordService.hpp"
#include "application/usecase/UserProvisioningService.hpp"
#include "common/result/ErrorSources.hpp"
#include "ui/cli/ConsoleIO.hpp"
#include "ui/cli/UserProvisioningInputCli.hpp"
#include "common/util/Utils/Utils.hpp"
#include "domain/model/Assistant/Assistant.hpp"
#include "domain/model/Patient/Patient.hpp"
#include "domain/model/Doctor/Doctor.hpp"
#include "infrastructure/persistence/FileSystemRepository.hpp"
#include "infrastructure/persistence/FilePatientRepository.hpp"
#include "infrastructure/persistence/FileUserProvisioningRepository.hpp"
#include "infrastructure/persistence/FileUserRepository.hpp"

#include <iostream>
#include <thread>

namespace {
ISystemRepository& systemRepository() {
    static FileSystemRepository repository;
    return repository;
}

IUserRepository& userRepository() {
    static FileUserRepository repository;
    return repository;
}

IPatientRepository& patientRepository() {
    static FilePatientRepository repository;
    return repository;
}

UserProvisioningService& userProvisioningService() {
    static FileUserProvisioningRepository repository;
    static UserProvisioningService service(repository);
    return service;
}

UserRecordService& userRecordService() {
    static UserRecordService service(userRepository());
    return service;
}

UserProfileQueryService& userProfileQueryService() {
    static UserProfileQueryService service(userRepository());
    return service;
}

PatientRecordQueryService& patientRecordQueryService() {
    static PatientRecordQueryService service(userRepository(), patientRepository());
    return service;
}
}

Admin::Admin() = default;

Admin::~Admin() = default;



// Checks if any Folder of Patients, Assistants or Doctors is already created, if not then the System needs an Initialization
bool Admin::checkInitialSetup() {
    if (!systemRepository().hasAssistantsDirectory() || !systemRepository().hasDoctorsDirectory()) {
        systemRepository().writeAdminSetupLog(
            "EPR-System Setup from Admin: " + getDate() + " " + getTime() + "\n\n"
        );

        std::cout << "[!] System is not initialized yet.\n";
        ConsoleIO::pauseSeconds(2);

        if (!systemRepository().hasAssistantsDirectory() && !systemRepository().hasDoctorsDirectory()) {
            std::cout << "[!] No Assistant and Doctor structure found.\n";
        }
        else if (!systemRepository().hasAssistantsDirectory()) {
            std::cout << "[!] No Assistant structure found.\n";
        }
        else if (!systemRepository().hasDoctorsDirectory()) {
            std::cout << "[!] No Doctor structure found.\n";
        }

        ConsoleIO::pauseSeconds(1);
        std::cout << "→ Entering admin setup mode...\n";
        ConsoleIO::pauseSeconds(3);
        admin_setup();

        return false;

    }
    return true;
}


// Admin Menu with all the Options
void Admin::admin_setup() {
    int choice;
    std::string firstName, lastName;
    std::string id;


    do {
        ConsoleIO::printHeader("=== Admin Logging | EPR SYSTEM ===");
        std::cout << "1. Create Patient\n";
        std::cout << "2. Info Patient\n";
        std::cout << "3. Create Doctor\n";
        std::cout << "4. Info Doctor\n";
        std::cout << "5. Create Assistant\n";
        std::cout << "6. Info Assistant\n";
        std::cout << "7. Update Field in File\n";
        std::cout << "8. Backup User Info\n";
        std::cout << "0. Exit\n";
        choice = ConsoleIO::promptInt("Please enter your choice: ");

    switch (choice) {
        case 1: {
            std::cout << std::endl;
            admin_getNames( firstName, lastName);
            UserProvisioningData data = UserProvisioningInputCli::promptPatientInput();
            data.firstName = firstName;
            data.lastName = lastName;
            const Result<void> createPatientResult = userProvisioningService().createPatient(data);
            if (!createPatientResult) {
                ConsoleIO::printError(createPatientResult.error());
                ConsoleIO::pauseSeconds(2);
                break;
            }
            std::cout << std::endl;
            std::cout << "Patient: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            ConsoleIO::pauseSeconds(2);
            break;
        }

        case 2: {
            std::cout << std::endl;
            id = ConsoleIO::promptToken("Please enter the full Patient-ID: ");
            std::cout << std::endl;
            {
                const Result<std::vector<std::string>> infoResult = patientRecordQueryService().getPatientInfo(id);
                if (!infoResult) {
                    ConsoleIO::printError(infoResult.error());
                    break;
                }
                std::cout << "File Content:" << std::endl;
                ConsoleIO::printLines(infoResult.value());
                ConsoleIO::pauseSeconds(3);
            }
            break;
        }

        case 3: {
            std::cout << std::endl;
            admin_getNames(firstName, lastName);
            UserProvisioningData data = UserProvisioningInputCli::promptDoctorInput();
            data.firstName = firstName;
            data.lastName = lastName;
            const Result<void> createDoctorResult = userProvisioningService().createDoctor(data);
            if (!createDoctorResult) {
                ConsoleIO::printError(createDoctorResult.error());
                ConsoleIO::pauseSeconds(2);
                break;
            }
            std::cout << std::endl;
            std::cout << "Doctor: [" << firstName << " " << lastName << "] successfully created!" << "\n";
            ConsoleIO::pauseSeconds(2);
            break;
        }

        case 4: {
            std::cout << std::endl;
            id = ConsoleIO::promptToken("Please enter the full Doctor-ID: ");
            {
                const Result<std::vector<std::string>> infoResult = userProfileQueryService().getUserInfo(id);
                if (!infoResult) {
                    ConsoleIO::printError(infoResult.error());
                    break;
                }
                std::cout << "File Content:" << std::endl;
                ConsoleIO::printLines(infoResult.value());
                ConsoleIO::pauseSeconds(3);
            }
            break;
        }

        case 5: {
            std::cout << std::endl;
            admin_getNames(firstName, lastName);
            UserProvisioningData data = UserProvisioningInputCli::promptAssistantInput();
            data.firstName = firstName;
            data.lastName = lastName;
            const Result<void> createAssistantResult = userProvisioningService().createAssistant(data);
            if (!createAssistantResult) {
                ConsoleIO::printError(createAssistantResult.error());
                ConsoleIO::pauseSeconds(2);
                break;
            }
            std::cout << std::endl;
            std::cout << "Assistant: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            ConsoleIO::pauseSeconds(2);
            break;
        }

        case 6: {
            std::cout << std::endl;
            id = ConsoleIO::promptToken("Please enter the full Assistant-ID: ");
            {
                const Result<std::vector<std::string>> infoResult = userProfileQueryService().getUserInfo(id);
                if (!infoResult) {
                    ConsoleIO::printError(infoResult.error());
                    break;
                }
                std::cout << "File Content:" << std::endl;
                ConsoleIO::printLines(infoResult.value());
                ConsoleIO::pauseSeconds(3);
            }
            break;
        }

        case 7: {
            std::string field, newInput;
            std::cout << std::endl;
            id = ConsoleIO::promptToken("Please enter the full ID: ");
            field = ConsoleIO::promptToken("Please enter the field to change: ");
            newInput = ConsoleIO::promptToken("Please enter the new input: ");
            const Result<void> updateResult = userRecordService().updateFieldInFile(id, field, newInput);
            if (!updateResult) {
                ConsoleIO::printError(updateResult.error());
                ConsoleIO::pauseSeconds(2);
                break;
            }
            std::cout << field << " successfully updated.\n";
            ConsoleIO::pauseSeconds(2);
            break;
        }

        case 8: {
            std::cout << std::endl;
            id = ConsoleIO::promptToken("Please enter the full ID to backup: ");
            exportUserData(id);
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            ConsoleIO::pauseSeconds(3);
            return;

        default: {
                std::cout << "Invalid choice.\n";
                break;
            }
    }
    } while (choice != 0);


}


// Just a simple function to get the Names
void Admin::admin_getNames(std::string &firstName, std::string &lastName) {
    firstName = ConsoleIO::promptToken("Enter first name: ");
    lastName = ConsoleIO::promptToken("Enter last name: ");
}


void Admin::exportUserData(const std::string& id) {

    if (!userRepository().exists(id)) {
        ConsoleIO::printError({"USER_NOT_FOUND", "Invalid ID: " + id, ErrorSources::kUi, "Admin::exportUserData"});
        ConsoleIO::pauseSeconds(2);
        return;
    }

    const std::vector<std::string> content = userRepository().readInfo(id);
    if (content.empty()) {
        ConsoleIO::printError({"READ_FAILED", "Failed to read file!", ErrorSources::kUi, "Admin::exportUserData"});
        return;
    }

    std::string folderName;
    if (!systemRepository().createUserBackupIfMissing(id, content, folderName)) {
        ConsoleIO::printError({"WRITE_FAILED", "Failed to create backup file.", ErrorSources::kUi, "Admin::exportUserData"});
        return;
    }

    std::cout << "Successfully created backup_info.txt file for: " << folderName << "\n";

    ConsoleIO::pauseSeconds(3);

}





