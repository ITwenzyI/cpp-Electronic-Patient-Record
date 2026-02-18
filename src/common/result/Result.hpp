#ifndef RESULT_HPP
#define RESULT_HPP

#include <string>
#include <utility>

struct Error {
    std::string code;
    std::string message;
    std::string source;
    std::string detail;
};

template <typename T> class Result {
  public:
    static Result<T> success(T value) {
        return Result<T>(true, std::move(value), {});
    }

    static Result<T> failure(std::string code, std::string message) {
        return Result<T>(false, T{}, {std::move(code), std::move(message), "", ""});
    }

    static Result<T> failure(
        std::string code, std::string message, std::string source, std::string detail = "") {
        return Result<T>(false, T{},
            {std::move(code), std::move(message), std::move(source), std::move(detail)});
    }

    bool ok() const {
        return ok_;
    }

    explicit operator bool() const {
        return ok();
    }

    bool hasError() const {
        return !ok_;
    }

    const T& value() const {
        return value_;
    }

    T& value() {
        return value_;
    }

    T valueOr(T fallback) const {
        return ok_ ? value_ : std::move(fallback);
    }

    const Error& error() const {
        return error_;
    }

    const std::string& errorCode() const {
        return error_.code;
    }

    const std::string& errorMessage() const {
        return error_.message;
    }

    const std::string& errorSource() const {
        return error_.source;
    }

    const std::string& errorDetail() const {
        return error_.detail;
    }

  private:
    Result(bool ok, T value, Error error)
        : ok_(ok), value_(std::move(value)), error_(std::move(error)) {
    }

    bool ok_;
    T value_;
    Error error_;
};

template <> class Result<void> {
  public:
    static Result<void> success() {
        return Result<void>(true, {});
    }

    static Result<void> failure(std::string code, std::string message) {
        return Result<void>(false, {std::move(code), std::move(message), "", ""});
    }

    static Result<void> failure(
        std::string code, std::string message, std::string source, std::string detail = "") {
        return Result<void>(
            false, {std::move(code), std::move(message), std::move(source), std::move(detail)});
    }

    bool ok() const {
        return ok_;
    }

    explicit operator bool() const {
        return ok();
    }

    bool hasError() const {
        return !ok_;
    }

    const Error& error() const {
        return error_;
    }

    const std::string& errorCode() const {
        return error_.code;
    }

    const std::string& errorMessage() const {
        return error_.message;
    }

    const std::string& errorSource() const {
        return error_.source;
    }

    const std::string& errorDetail() const {
        return error_.detail;
    }

  private:
    Result(bool ok, Error error) : ok_(ok), error_(std::move(error)) {
    }

    bool ok_;
    Error error_;
};

#endif // RESULT_HPP
