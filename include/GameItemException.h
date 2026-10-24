#pragma once
#include <exception>
#include <string>

class GameItemException : public std::exception {
private:
    std::string mensagem;

public:
    explicit GameItemException(const std::string& msg);
    const char* what() const noexcept override;
};