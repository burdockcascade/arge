#pragma once
#include <quickjs.h>

class Runner {
public:
    // Lifecycle
    explicit Runner(std::string path);

    ~Runner();

    // Deleted Copy/Assignment
    Runner(const Runner&) = delete;
    Runner& operator=(const Runner&) = delete;

    // Execution
    void Run() const;

private:
    std::string scriptPath;
    JSRuntime* rt = nullptr;
    JSContext* ctx = nullptr;

    [[nodiscard]] bool EvalModule(const std::string &code, const std::string &filename) const;
    void HandleException() const;
};