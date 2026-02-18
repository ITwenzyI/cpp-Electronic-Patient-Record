# Project Structure - Electronic Patient Record (EPR)

## 1. Overview

This project follows a layered architecture under `src/`:

- `domain`: core entities and domain state
- `application`: use-cases, orchestration, and ports (interfaces)
- `infrastructure`: file-based adapters implementing ports
- `ui`: CLI rendering, prompts, menu handling
- `common`: shared technical building blocks (`Result`, error constants, utilities)

Entry point:

- `src/main.cpp` creates and runs `EprApplication`

## 2. Current Source Layout

```text
src/
  main.cpp

  application/
    EprApplication.cpp
    EprApplication.hpp
    ports/
      IPatientRepository.hpp
      IUserRepository.hpp
      IUserProvisioningRepository.hpp
      ISystemRepository.hpp
    usecase/
      AppointmentReviewService.cpp/.hpp
      AuthService.cpp/.hpp
      LoginDecisionUseCase.cpp/.hpp
      PatientRecordQueryService.cpp/.hpp
      PatientWriteService.cpp/.hpp
      SystemBootstrapUseCase.cpp/.hpp
      UserProfileQueryService.cpp/.hpp
      UserProvisioningService.cpp/.hpp
      UserRecordService.cpp/.hpp
      UserSessionService.cpp/.hpp

  domain/
    model/
      User/User.cpp/.hpp
      Patient/Patient.cpp/.hpp
      Doctor/Doctor.cpp/.hpp
      Assistant/Assistant.cpp/.hpp

  infrastructure/
    persistence/
      FilePatientRepository.cpp/.hpp
      FileUserRepository.cpp/.hpp
      FileUserProvisioningRepository.cpp/.hpp
      FileSystemRepository.cpp/.hpp
      IDs/IDs.cpp/.hpp

  ui/
    cli/
      ConsoleIO.cpp/.hpp
      MainMenuCli.cpp/.hpp
      PatientConsole.cpp
      DoctorConsole.cpp
      AssistantConsole.cpp
      UserProvisioningInputCli.cpp/.hpp
      Admin/Admin.cpp/.hpp

  common/
    result/
      Result.hpp
      ErrorCodes.hpp
      ErrorSources.hpp
    util/
      Utils/Utils.cpp/.hpp
```

## 3. Layer Responsibilities

## 3.1 Domain (`src/domain`)

- Contains role entities (`User`, `Patient`, `Doctor`, `Assistant`)
- Holds domain data (IDs, names, profile fields)
- Does not perform persistence directly

Notes:

- `check_id_name` was removed from domain classes.
- `displayMenu` role entrypoints were also removed from domain classes.
- Authentication is now centralized in application (`AuthService`).

## 3.2 Application (`src/application`)

- Central business orchestration and use-case logic
- Uses repository interfaces from `application/ports`
- Produces `Result<T>` / `Result<void>` with structured `Error`

Key use-cases:

- `EprApplication`: top-level app loop and composition-style orchestration
- `SystemBootstrapUseCase`: startup/bootstrap flow
- `LoginDecisionUseCase`: parses role/admin/exit menu input
- `AuthService`: validates `(id, firstName, lastName)` against user info
- `UserSessionService`: authenticates + dispatches to role menu
- `PatientRecordQueryService`: reads patient info/appointments/medications/records
- `PatientWriteService`: writes records, medications, appointment requests
- `UserRecordService`: updates info fields and appends extra info
- `UserProfileQueryService`: reads user profile info
- `UserProvisioningService`: creates Patient/Doctor/Assistant records
- `AppointmentReviewService`: loads/reviews/saves appointment requests

## 3.3 Infrastructure (`src/infrastructure`)

- Implements ports with file-system backed adapters
- Encapsulates filesystem layout and file read/write mechanics

Adapters:

- `FileUserRepository` implements `IUserRepository`
- `FilePatientRepository` implements `IPatientRepository`
- `FileUserProvisioningRepository` implements `IUserProvisioningRepository`
- `FileSystemRepository` implements `ISystemRepository`
- `IDs` helpers manage role ID counters in files

## 3.4 UI (`src/ui`)

- CLI only: printing, prompts, simple display flow
- Delegates business operations to application services
- Uses shared output helpers from `ConsoleIO`

Main UI components:

- `MainMenuCli`: main menu + login identity prompts
- `Admin/Admin.cpp`: admin setup and admin operations
- `PatientConsole.cpp`, `DoctorConsole.cpp`, `AssistantConsole.cpp`: role menus
- `UserProvisioningInputCli`: role-specific input collection for creation
- `ConsoleIO`: shared prompt/render/pause/error-output helpers

## 3.5 Common (`src/common`)

Technical shared modules:

- `Result.hpp`: generic result container + `Error { code, message, source, detail }`
- `ErrorCodes.hpp`: centralized error code constants
- `ErrorSources.hpp`: centralized source constants (`app`, `ui`, `infra`)
- `Utils`: date/time, cleanup helpers, path helper

## 4. Dependency Direction

Intended direction:

1. `ui` -> `application`
2. `application` -> `domain` and `application/ports`
3. `infrastructure` -> `application/ports`
4. `domain` is independent from `ui` and `infrastructure`
5. `common` is shared technical support

Practical note:

- Role menu dispatch now uses explicit UI controllers:
  - `runPatientMenu(Patient&)`
  - `runDoctorMenu(Doctor&)`
  - `runAssistantMenu(Assistant&)`
- Authentication and identity check logic is centralized in `AuthService`.

## 5. Runtime Flow

1. `main.cpp` runs `EprApplication::run()`.
2. `SystemBootstrapUseCase` prepares startup state and initialization checks.
3. `MainMenuCli` reads role/admin selection and login identity.
4. `LoginDecisionUseCase` decides admin/exit/session branch.
5. `UserSessionService` calls `AuthService` to validate login data.
6. On success, the selected role menu controller is entered.
7. Role UI screens call application services, which use ports/adapters.

## 6. Error Handling Model

Current standard:

- Use `Result<T>` or `Result<void>` for expected errors
- Use centralized error codes from `ErrorCodes`
- Include source/detail context (`ErrorSources` + method detail)
- Render via `ConsoleIO::printError(const Error&)`

Example error payload:

- `code`: stable machine-readable category (`WRITE_FAILED`)
- `message`: user-facing message
- `source`: `app` / `ui` / `infra`
- `detail`: technical context (e.g. `PatientWriteService::addRecord`)

## 7. Tests

Smoke tests are located in `tests/`:

- `tests/PatientWriteServiceSmokeTest.cpp`
- `tests/UserRecordServiceSmokeTest.cpp`
- `tests/TestMain.cpp`

Test build target:

- `usecase_smoke_tests`

How to run:

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## 8. Build System Notes

- CMake uses `GLOB_RECURSE ... CONFIGURE_DEPENDS` for `src/*.cpp` and `src/*.hpp`.
- Test target is explicitly listed under `if(BUILD_TESTING)`.
- C++ standard: C++20.
- Warnings:
  - MSVC: `/W4 /permissive-`
  - GCC/Clang/MinGW: `-Wall -Wextra -Wpedantic`

## 9. Architectural Rules (Current Team Conventions)

- No direct persistence logic in UI.
- Application should depend on ports, not file implementations.
- Domain should avoid infrastructure concerns.
- Keep changes incremental and compilable per commit.
- Prefer centralized error rendering and centralized error code definitions.

## 10. Known Pragmatic Tradeoffs

- `UserSessionService` currently includes UI controller headers to dispatch role menus.
- This keeps behavior stable during the refactor, but a stricter layering would move final menu dispatch fully into UI composition code.
