cmake_minimum_required(VERSION 3.29)

project(
    patient_record
    VERSION 0.1.0
    DESCRIPTION "Electronic Patient Record (EPR) CLI application"
    LANGUAGES CXX
)

set(PATIENT_RECORD_SOURCES
    src/main.cpp
    src/application/EprApplication.cpp
    src/domain/model/Patient/Patient.cpp
    src/domain/model/User/User.cpp
    src/domain/model/Doctor/Doctor.cpp
    src/domain/model/Assistant/Assistant.cpp
    src/common/util/Utils/Utils.cpp
    src/infrastructure/persistence/IDs/IDs.cpp
    src/infrastructure/persistence/FileUserRepository.cpp
    src/infrastructure/persistence/FilePatientRepository.cpp
    src/ui/cli/UserConsole.cpp
    src/ui/cli/PatientConsole.cpp
    src/ui/cli/DoctorConsole.cpp
    src/ui/cli/AssistantConsole.cpp
    src/ui/cli/Admin/Admin.cpp
)

set(PATIENT_RECORD_HEADERS
    src/application/EprApplication.hpp
    src/application/ports/IUserRepository.hpp
    src/application/ports/IPatientRepository.hpp
    src/domain/model/Patient/Patient.hpp
    src/domain/model/User/User.hpp
    src/domain/model/Doctor/Doctor.hpp
    src/domain/model/Assistant/Assistant.hpp
    src/common/util/Utils/Utils.hpp
    src/infrastructure/persistence/IDs/IDs.hpp
    src/infrastructure/persistence/FileUserRepository.hpp
    src/infrastructure/persistence/FilePatientRepository.hpp
    src/ui/cli/Admin/Admin.hpp
)

add_executable(patient_record)

target_sources(patient_record
    PRIVATE
        ${PATIENT_RECORD_SOURCES}
        ${PATIENT_RECORD_HEADERS}
)

target_include_directories(patient_record
    PRIVATE
        src
)

target_compile_features(patient_record PRIVATE cxx_std_20)
set_target_properties(patient_record PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(MSVC)
    target_compile_options(patient_record PRIVATE /W4 /permissive-)
else()
    target_compile_options(patient_record PRIVATE -Wall -Wextra -Wpedantic)
endif()
