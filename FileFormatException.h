//
// Created by Martin on 2023. 05. 13..
//

#pragma once

#include <exception>
#include <string>
#include <utility>

class FileFormatException : public std::exception {
private:
    std::string message;

public:
    explicit FileFormatException(std::string message): message(std::move(message)) {}

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};
