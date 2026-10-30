#include "../include/GameItemException.h"

GameItemException::GameItemException(const std::string& msg)
    : mensagem(msg) {}

const char* GameItemException::what() const noexcept {
    return mensagem.c_str();
}