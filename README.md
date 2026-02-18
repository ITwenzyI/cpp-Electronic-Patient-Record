# Electronic Patient Record (EPR) - C++ CLI

A layered C++ project that simulates a file-based Electronic Patient Record system with role-based workflows for Patients, Doctors, Assistants, and Admin setup.

## Project Status

- Active refactor state with clean layered structure
- CLI-based interaction
- File-based persistence (no database yet)

## Goals

- Keep business and orchestration logic separated from persistence and UI
- Improve maintainability and testability through explicit layers
- Preserve existing behavior while incrementally modernizing architecture

## Architecture

The project is organized under `src/` using layered boundaries:

- `domain/`: entities and core model state
- `application/`: use-cases and ports (interfaces)
- `infrastructure/`: file-system adapters implementing ports
- `ui/`: CLI menus, prompts, rendering, and composition root
- `common/`: shared technical utilities (`Result`, error constants, helpers)

Detailed architecture documentation:

- `docs/project_structure.md`

## Key Components

### Application Use-Cases

- `AuthService`: validates login identity (`id`, `firstName`, `lastName`)
- `UserSessionService`: session-level validation/orchestration checks
- `PatientRecordQueryService`: read patient info, appointments, medications, records
- `PatientWriteService`: add records/medications/appointment requests
- `UserRecordService`: update user info fields / append extra info
- `UserProvisioningService`: create Patient/Doctor/Assistant data
- `AppointmentReviewService`: assistant workflow for request review/confirmation
- `SystemBootstrapUseCase`: startup/bootstrap checks
- `LoginDecisionUseCase`: interprets main menu input

### UI Composition

- Entry point: `src/main.cpp`
- Composition root: `src/ui/cli/EprCliApplication.cpp`
- Role menu controllers:
  - `src/ui/cli/PatientMenuController.hpp`
  - `src/ui/cli/DoctorMenuController.hpp`
  - `src/ui/cli/AssistantMenuController.hpp`

### Error Model

- Unified result type: `src/common/result/Result.hpp`
- Centralized error codes: `src/common/result/ErrorCodes.hpp`
- Error source constants: `src/common/result/ErrorSources.hpp`
- UI rendering helper: `ConsoleIO::printError(const Error&)`

## Features

### Admin

- Initial setup and system bootstrapping support
- Create Patient / Doctor / Assistant profiles
- Read user profile data
- Update user fields
- Export user backup data

### Patient

- View appointments
- View medications
- View records
- Request new appointment

### Doctor

- Add medications for patient
- Add records for patient
- View patient info/appointments/medications/records
- Update info field
- Add extra info

### Assistant

- Create new patient
- Update info field
- Review appointment requests (accept/reject/skip)
- Add medications/records
- View patient info/appointments/medications/records
- Add extra info

## Build Requirements

- CMake `>= 3.29`
- C++20-compatible compiler
- Works with MSVC and MinGW/GCC toolchains (project currently used on Windows)

## Build and Run

From repository root:

```powershell
cmake -S . -B build
cmake --build build
```

Run executable:

```powershell
.\build\patient_record.exe
```

## Tests

Smoke tests cover key application use-cases with fake repositories.

Test target:

- `usecase_smoke_tests`

Run tests:

```powershell
ctest --test-dir build --output-on-failure
```

Test files:

- `tests/TestMain.cpp`
- `tests/PatientWriteServiceSmokeTest.cpp`
- `tests/UserRecordServiceSmokeTest.cpp`
- `tests/README.md`

## Data Storage

Persistence is file-based under `data/` (runtime-generated/updated):

- role directories (`Patients`, `Doctors`, `Assistants`)
- per-user info files
- patient sub-files (`appointments.txt`, `medications.txt`, `records.txt`)
- appointment requests (`data/Appointments/requests.txt`)
- role ID counters (`*_id.txt`)

## Dependency Direction

Intended dependencies:

1. `ui` -> `application`
2. `application` -> `domain` + `application/ports`
3. `infrastructure` -> `application/ports`
4. `domain` independent of `ui` and `infrastructure`
5. `common` shared by all layers for technical concerns

## Roadmap (Pragmatic Next Steps)

- Optional: extract role menu dispatch from `EprCliApplication` into dedicated UI routing module
- Expand use-case tests (additional negative/edge cases)
- Introduce optional database adapter behind existing ports
- Improve input validation for date/time and IDs

## Author

- Kilian
