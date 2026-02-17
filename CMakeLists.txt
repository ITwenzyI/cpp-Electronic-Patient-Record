cmake_minimum_required(VERSION 3.29)

project(
    patient_record
    VERSION 0.1.0
    DESCRIPTION "Electronic Patient Record (EPR) CLI application"
    LANGUAGES CXX
)

file(GLOB_RECURSE PATIENT_RECORD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB_RECURSE PATIENT_RECORD_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
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
