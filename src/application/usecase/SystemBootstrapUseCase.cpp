#include "application/usecase/SystemBootstrapUseCase.hpp"

#include "application/ports/ISystemRepository.hpp"
#include "infrastructure/persistence/FileSystemRepository.hpp"
#include "ui/cli/Admin/Admin.hpp"

#include <chrono>
#include <iostream>
#include <thread>

#include <windows.h>

namespace {
ISystemRepository& systemRepository() {
    static FileSystemRepository repository;
    return repository;
}
}

void SystemBootstrapUseCase::run() const {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "Booting up System.\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    std::cout << "Booting up System..\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
    std::cout << "Booting up System...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(900));

    systemRepository().ensureBootstrapData();

    while (!Admin::checkInitialSetup()) {}
}
