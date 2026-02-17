# Project Structure - Electronic Patient Record (EPR)

## Layered Architecture

The project now follows a layered structure under `src/`:

```text
src/
  main.cpp
  application/
    EprApplication.cpp
    EprApplication.hpp
    ports/
      IPatientRepository.hpp
      IUserRepository.hpp
  domain/
    model/
      User/
      Patient/
      Doctor/
      Assistant/
  infrastructure/
    persistence/
      IDs/
      FilePatientRepository.cpp
      FilePatientRepository.hpp
      FileUserRepository.cpp
      FileUserRepository.hpp
  ui/
    cli/
      Admin/
      UserConsole.cpp
      PatientConsole.cpp
      DoctorConsole.cpp
      AssistantConsole.cpp
  common/
    util/
      Utils/
```

## Responsibilities

- `domain/`: business entities and core data model logic.
- `application/`: application flow/use-case orchestration and ports (interfaces).
- `infrastructure/`: file-based persistence adapters and ID persistence details.
- `ui/`: CLI interaction (menus, rendering, input handling).
- `common/`: shared technical utilities.

## Dependency Direction

Intended dependency direction:

1. `ui` -> `application` -> `domain`
2. `infrastructure` -> `application` (implements ports)
3. `application` may use `domain`
4. `domain` should not depend on `ui` or `infrastructure`
5. `common` can be used by all layers for technical helpers

`src/main.cpp` is the composition root and starts `EprApplication`.
