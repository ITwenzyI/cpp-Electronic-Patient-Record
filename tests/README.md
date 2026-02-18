# Smoke Tests

This project includes lightweight smoke tests for application use-cases:

- `PatientWriteService`
- `UserRecordService`

## Run Tests

From the repository root:

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Test Target

All smoke checks are bundled into one executable target:

- `usecase_smoke_tests`
