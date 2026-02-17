cmake_minimum_required(VERSION 3.29.6)
project(patient_record)

set(CMAKE_CXX_STANDARD 20)

add_executable(patient_record
        src/main.cpp
        src/application/EprApplication.cpp
        src/application/EprApplication.hpp
        src/application/ports/IUserRepository.hpp
        src/application/ports/IPatientRepository.hpp
        src/domain/model/Patient/Patient.cpp
        src/domain/model/Patient/Patient.hpp
        src/domain/model/User/User.cpp
        src/domain/model/User/User.hpp
        src/domain/model/Doctor/Doctor.cpp
        src/domain/model/Doctor/Doctor.hpp
        src/domain/model/Assistant/Assistant.cpp
        src/domain/model/Assistant/Assistant.hpp
        src/common/util/Utils/Utils.cpp
        src/common/util/Utils/Utils.hpp
        src/infrastructure/persistence/IDs/IDs.cpp
        src/infrastructure/persistence/IDs/IDs.hpp
        src/infrastructure/persistence/FileUserRepository.cpp
        src/infrastructure/persistence/FileUserRepository.hpp
        src/infrastructure/persistence/FilePatientRepository.cpp
        src/infrastructure/persistence/FilePatientRepository.hpp
        src/ui/cli/UserConsole.cpp
        src/ui/cli/PatientConsole.cpp
        src/ui/cli/DoctorConsole.cpp
        src/ui/cli/AssistantConsole.cpp
        src/ui/cli/Admin/Admin.cpp
        src/ui/cli/Admin/Admin.hpp
)

target_include_directories(patient_record PRIVATE src)
