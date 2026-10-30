#include "../include/Map.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

Map::Map(int stepsCounter, bool day)
    : stepsCounter(stepsCounter), day(day) {
        grid = std::vector<std::vector<Tiles>>(altura, std::vector<Tiles>(largura, Tiles(false, nullptr, nullptr)));
    }

int Map::countStep() {
    if (stepsCounter == 0) {
        cycleDay();
    }

    --stepsCounter;
    if (stepsCounter == 0) {
        cycleDay();
    }
    return stepsCounter;
}

void Map::cycleDay() {
    if (this->day) {
        this->day = false;
        this->stepsCounter = 30;
    } else {
        this->day = true;
        this->stepsCounter = 50;
    }
}

int Map::getSteps() {
    return stepsCounter;
}

bool Map::isDay() const {
    return day;
}

void Map::addSteps(int val) {
    stepsCounter += val;
}

void Map::setSteps(int val) {
    stepsCounter = val;
}

void Map::revealAroundPlayer(int radius) {
    std::cout << "[Visao do Mapa]: Area em torno do jogador revelada (raio de " << radius << " tiles)!\n";
    std::cout << "[Visao do Mapa]: Periodo: " << (day ? "Dia (claro e visivel)" : "Noite (perigosa e escura)")
              << " | Passos restantes: " << stepsCounter << "\n";
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    try {
        file.open(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filename);
        }

        // 1. Lemos todas as linhas do arquivo primeiro para saber as dimensoes do mapa
        std::vector<std::string> lines;
        std::string line;

        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (!line.empty()) {
                lines.push_back(line);
            }
        }

        file.close();

        if (lines.empty()) {
            throw std::runtime_error("O arquivo de mapa esta vazio.");
        }

        altura = static_cast<int>(lines.size());
        largura = static_cast<int>(lines[0].size());

        // 2. Inicializamos a matriz 2D com o tamanho exato (altura x largura)
        grid = std::vector<std::vector<Tiles>>(
            altura, 
            std::vector<Tiles>(largura, Tiles(false, nullptr, nullptr))
        );

        // 3. Modificamos os elementos diretamente acessando a matriz [i][j]
        for (int i = 0; i < altura; ++i) {
            for (int j = 0; j < largura; ++j) {
                char ch = lines[i][j];
                
                if (ch == 'O' || ch == 'P') {
                    grid[i][j].setWalkable(true); // Ou grid[i][j].setWalkable(); dependendo da sua classe
                } else {
                    grid[i][j].setWalkable(false);
                }
            }
        }

        return true;

    } catch (const std::ifstream::failure& e) {
        std::cerr << "[Erro de I/O] Falha na leitura do arquivo: " << e.what() << '\n';
        return false;
    } catch (const std::exception& e) {
        std::cerr << "[Erro no Mapa] " << e.what() << '\n';
        return false;
    }
}

void Map::printMap() {
    if (grid.empty()) {
        std::cout << "[Mapa Vazio]: Nenhum grid foi carregado.\n";
        return;
    }

    std::cout << "\n=== EXIBICAO DO MAPA (" << altura << "x" << largura << ") ===\n\n";

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            // Se a célula for caminhável, imprime 'O', caso contrário 'X'
            if(grid[i][j].isWalkable()) { // Ajuste o nome do método de acordo com o header de Tiles
                std::cout << "\033[32mO\033[0m";
            } else {
                std::cout << 'X';
            }
        }
        std::cout << '\n'; // Quebra de linha ao fim de cada fileira
    }

    std::cout << "\n=====================================\n";
}
