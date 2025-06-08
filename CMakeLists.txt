cmake_minimum_required(VERSION 3.31)
project(patient_record)

set(CMAKE_CXX_STANDARD 20)

add_executable(patient_record main.cpp
        src/Patient/Patient.cpp
        src/Patient/Patient.hpp
        src/user/User.cpp
        src/user/User.hpp
        src/Doctor/Doctor.cpp
        src/Doctor/Doctor.hpp
        src/Menu.cpp
        src/Menu.hpp
        src/Assistant/Assistant.cpp
        src/Assistant/Assistant.hpp
        src/Utils/Utils.cpp
        src/Utils/Utils.hpp
        src/IDs/IDs.cpp
        src/IDs/IDs.hpp
)
