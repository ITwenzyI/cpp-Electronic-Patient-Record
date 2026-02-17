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
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (!systemRepository().hasAssistantsDirectory() && !systemRepository().hasDoctorsDirectory()) {
            std::cout << "[!] No Assistant and Doctor structure found.\n";
        }
        else if (!systemRepository().hasAssistantsDirectory()) {
            std::cout << "[!] No Assistant structure found.\n";
        }
        else if (!systemRepository().hasDoctorsDirectory()) {
            std::cout << "[!] No Doctor structure found.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "→ Entering admin setup mode...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
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
        std::cout << std::endl;
        std::cout << "=== Admin Logging | EPR SYSTEM ===\n";
        std::cout << "1. Create Patient\n";
        std::cout << "2. Info Patient\n";
        std::cout << "3. Create Doctor\n";
        std::cout << "4. Info Doctor\n";
        std::cout << "5. Create Assistant\n";
        std::cout << "6. Info Assistant\n";
        std::cout << "7. Update Field in File\n";
        std::cout << "8. Backup User Info\n";
        std::cout << "0. Exit\n";
        std::cout << "Please enter your choice: ";
        std::cin >> choice;

    switch (choice) {
        case 1: {
            std::cout << std::endl;
            admin_getNames( firstName, lastName);
            Patient p("", firstName, lastName);
            p.fill_patient_info();
            userProvisioningService().createPatient(p);
            std::cout << std::endl;
            std::cout << "Patient: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 2: {
            std::cout << std::endl;
            std::cout << "Please enter the full Patient-ID: ";
            std::cin >> id;
            std::cout << std::endl;
            {
                const std::vector<std::string> info = patientRecordQueryService().getPatientInfo(id);
                if (info.empty()) {
                    std::cerr << "Failed to read file!" << std::endl;
                    break;
                }
                std::cout << "File Content:" << std::endl;
                for (const auto& line : info) {
                    std::cout << line << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            break;
        }

        case 3: {
            std::cout << std::endl;
            admin_getNames(firstName, lastName);
            Doctor d("", firstName, lastName);
            d.fill_doctor_info();
            userProvisioningService().createDoctor(d);
            std::cout << std::endl;
            std::cout << "Doctor: [" << firstName << " " << lastName << "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 4: {
            std::cout << std::endl;
            std::cout << "Please enter the full Doctor-ID: ";
            std::cin >> id;
            {
                const std::vector<std::string> info = userProfileQueryService().getUserInfo(id);
                if (info.empty()) {
                    std::cerr << "Failed to read file!" << std::endl;
                    break;
                }
                std::cout << "File Content:" << std::endl;
                for (const auto& line : info) {
                    std::cout << line << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
            break;
        }

        case 5: {
            std::cout << std::endl;
            admin_getNames(firstName, lastName);
            Assistant a("", firstName, lastName);
            a.fill_assistant_info();
            userProvisioningService().createAssistant(a);
            std::cout << std::endl;
            std::cout << "Assistant: [" << firstName << " " << lastName <<  "] successfully created!" << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 6: {
            std::cout << std::endl;
            std::cout << "Please enter the full Assistant-ID: ";
            std::cin >> id;
            Assistant::get_assistant_info(id);
            break;
        }

        case 7: {
            std::string field, newInput;
            std::cout << std::endl;
            std::cout << "Please enter the full ID: ";
            std::cin >> id;
            std::cout << "Please enter the field to change: ";
            std::cin >> field;
            std::cout << "Please enter the new input: ";
            std::cin >> newInput;
            if (!userRecordService().updateFieldInFile(id, field, newInput)) {
                std::cerr << "Could not update field in file.\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }
            std::cout << field << " successfully updated.\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 8: {
            std::cout << std::endl;
            std::cout << "Please enter the full ID to backup: ";
            std::cin >> id;
            exportUserData(id);
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
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
    std::cout << "Enter first name: ";
    std::cin >> firstName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;
}


void Admin::exportUserData(const std::string& id) {

    if (!userRepository().exists(id)) {
        std::cerr << "Invalid ID: " << id << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return;
    }

    const std::vector<std::string> content = userRepository().readInfo(id);
    if (content.empty()) {
        std::cerr << "Failed to read file!" << std::endl;
        return;
    }

    std::string folderName;
    if (!systemRepository().createUserBackupIfMissing(id, content, folderName)) {
        std::cerr << "Failed to create backup file." << std::endl;
        return;
    }

    std::cout << "Successfully created backup_info.txt file for: " << folderName << "\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));

}





