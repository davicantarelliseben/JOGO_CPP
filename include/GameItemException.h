#pragma once

#include <stdexcept>
#include <string>

class GameItemException : public std::runtime_error {
public:
    explicit GameItemException(const std::string& msg)
        : std::runtime_error(msg) {}
};