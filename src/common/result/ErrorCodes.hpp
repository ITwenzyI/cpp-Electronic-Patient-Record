#ifndef ERROR_CODES_HPP
#define ERROR_CODES_HPP

namespace ErrorCodes {
constexpr const char* kWriteFailed = "WRITE_FAILED";
constexpr const char* kUserNotFound = "USER_NOT_FOUND";
constexpr const char* kFieldNotFound = "FIELD_NOT_FOUND";
constexpr const char* kPatientNotFound = "PATIENT_NOT_FOUND";
constexpr const char* kAppointmentsNotFound = "APPOINTMENTS_NOT_FOUND";
constexpr const char* kMedicationsNotFound = "MEDICATIONS_NOT_FOUND";
constexpr const char* kRecordsNotFound = "RECORDS_NOT_FOUND";
constexpr const char* kCreatePatientFailed = "CREATE_PATIENT_FAILED";
constexpr const char* kCreateDoctorFailed = "CREATE_DOCTOR_FAILED";
constexpr const char* kCreateAssistantFailed = "CREATE_ASSISTANT_FAILED";
constexpr const char* kDoctorNameNotFound = "DOCTOR_NAME_NOT_FOUND";
constexpr const char* kRequestsFileMissing = "REQUESTS_FILE_MISSING";
constexpr const char* kWriteRequestsFailed = "WRITE_REQUESTS_FAILED";
constexpr const char* kAuthNameMismatch = "AUTH_NAME_MISMATCH";
constexpr const char* kInvalidSelection = "INVALID_SELECTION";
} // namespace ErrorCodes

#endif // ERROR_CODES_HPP
