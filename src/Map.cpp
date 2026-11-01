#include "../include/Map.h"
#include "../include/Battle.h"
#include "../include/Event.h"
#include "../include/Enemy.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <random>
#include <cmath>

Map::Map(int stepsCounter, bool day)
    : stepsCounter(stepsCounter), day(day) {
    grid = std::vector<std::vector<Tiles>>(altura, std::vector<Tiles>(largura, Tiles()));
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

int Map::getVisionBonus() const {
    // Durante o dia ganha +1 no raio de visão, à noite sofre penalidade de -1
    return day ? 1 : -1;
}

void Map::addSteps(int val) {
    stepsCounter += val;
}

void Map::setSteps(int val) {
    stepsCounter = val;
}

int Map::getAltura() {
    return this->altura;
}

int Map::getLargura() {
    return this->largura;
}

Tiles& Map::getTile(int y, int x) {
    return this->grid[y][x];
}

// 1. Método original: Revela a área ao redor de coordenadas específicas
void Map::revealAroundPlayer(int playerY, int playerX, int visionRadius) {
    if (grid.empty() || playerY < 0 || playerY >= altura || playerX < 0 || playerX >= largura) {
        return;
    }

    // Converte tiles visíveis anteriormente para o estado "Explorado"
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            if (grid[i][j].getState() == TileState::Visible) {
                grid[i][j].setState(TileState::Explored);
            }
        }
    }

    // Revela a nova área dentro do raio de visão considerando distância euclidiana
    for (int y = playerY - visionRadius; y <= playerY + visionRadius; ++y) {
        for (int x = playerX - visionRadius; x <= playerX + visionRadius; ++x) {
            if (y >= 0 && y < altura && x >= 0 && x < largura) {
                float distance = std::sqrt(std::pow(y - playerY, 2) + std::pow(x - playerX, 2));
                if (distance <= visionRadius) {
                    grid[y][x].setState(TileState::Visible);
                }
            }
        }
    }
}

// 2. Sobrecarga para a Torre de Vigia: Procura onde está o evento e revela uma área estendida em volta dele
void Map::revealAroundPlayer(int visionRadius) {
    if (grid.empty()) return;

    for (int y = 0; y < altura; ++y) {
        for (int x = 0; x < largura; ++x) {
            if (grid[y][x].getEvent() != nullptr && 
                grid[y][x].getEvent()->getEventType() == eventType::lookoutTower) {
                
                // Aplica a revelação por raio euclidiano ao redor da posição da torre encontrada
                for (int cy = y - visionRadius; cy <= y + visionRadius; ++cy) {
                    for (int cx = x - visionRadius; cx <= x + visionRadius; ++cx) {
                        if (cy >= 0 && cy < altura && cx >= 0 && cx < largura) {
                            float distance = std::sqrt(std::pow(cy - y, 2) + std::pow(cx - x, 2));
                            if (distance <= visionRadius) {
                                grid[cy][cx].setState(TileState::Visible);
                            }
                        }
                    }
                }
                return; 
            }
        }
    }
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);

    try {
        file.open(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Nao foi possivel abrir o arquivo: " + filename);
        }

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

        grid = std::vector<std::vector<Tiles>>(
            altura, 
            std::vector<Tiles>(largura, Tiles(false, nullptr, nullptr))
        );

        for (int i = 0; i < altura; ++i) {
            for (int j = 0; j < largura; ++j) {
                char ch = lines[i][j];
                
                if (ch == 'O' || ch == 'P') {
                    grid[i][j].setWalkable(true);
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

void Map::printMap(int playerY, int playerX) {
    if (grid.empty()) {
        std::cout << "[Mapa Vazio]: Nenhum grid foi carregado.\n";
        return;
    }

    std::cout << "\n=== EXIBICAO DO MAPA (" << altura << "x" << largura << ") ===\n";
    std::cout << "Periodo: " << (day ? "\033[1;33mDia\033[0m" : "\033[1;35mNoite\033[0m") 
              << " | Passos restantes na fase: " << stepsCounter << "\n";
    std::cout << "Legenda: \033[1;34mP\033[0m=Player | \033[1;31mE\033[0m=Enemy | \033[1;33mV\033[0m=Event | \033[32mO\033[0m=Vazio | \033[90mX\033[0m=Parede | \033[37m.\033[0m=Explorado | \033[90m?\033[0m=Nevoada\n\n";

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            
            // 1. Posição do Jogador
            if (i == playerY && j == playerX) {
                std::cout << "\033[1;34mP\033[0m"; 
            }
            else {
                TileState state = grid[i][j].getState();

                // Célula Não Explorada (Névoa de Guerra Total)
                if (state == TileState::Unexplored) {
                    std::cout << "\033[90m?\033[0m";
                }
                // Célula Já Explorada anteriormente (Memória do Mapa)
                else if (state == TileState::Explored) {
                    if (grid[i][j].isWalkable()) {
                        std::cout << "\033[37m.\033[0m"; // Mostra que o terreno é caminhável
                    } else {
                        std::cout << "\033[90mX\033[0m"; // Parede já conhecida
                    }
                }
                // Célula Visível no raio atual
                else if (state == TileState::Visible) {
                    if (grid[i][j].isWalkable()) {
                        if (grid[i][j].getEnemy() != nullptr) {
                            std::cout << "\033[1;31mE\033[0m"; // Inimigo Visível
                        } else if (grid[i][j].getEvent() != nullptr) {
                            std::cout << "\033[1;33mV\033[0m"; // Evento Visível
                        } else {
                            std::cout << "\033[32mO\033[0m";    // Terreno Livre Visível
                        }
                    } else {
                        std::cout << "\033[90mX\033[0m";     // Parede Visível
                    }
                }
            }
        }
        std::cout << '\n';
    }

    std::cout << "\n=====================================\n";
}

void Map::populateEventsAndBattles(int playerY, int playerX, Player* player, ItemManager* itemManager) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> chance(1, 100);

    const int ZONA_DE_SEGURANCA = 5;
    const int ESPACAMENTO_MINIMO = 3;

    auto temEntidadeProxima = [this, ESPACAMENTO_MINIMO](int cy, int cx) -> bool {
        int minY = std::max(0, cy - ESPACAMENTO_MINIMO);
        int maxY = std::min(altura - 1, cy + ESPACAMENTO_MINIMO);
        int minX = std::max(0, cx - ESPACAMENTO_MINIMO);
        int maxX = std::min(largura - 1, cx + ESPACAMENTO_MINIMO);

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                if (grid[y][x].getEnemy() != nullptr || grid[y][x].getEvent() != nullptr) {
                    return true;
                }
            }
        }
        return false;
    };

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {

            if (!grid[i][j].isWalkable()) {
                continue;
            }

            int distanciaPlayer = std::abs(i - playerY) + std::abs(j - playerX);
            if (distanciaPlayer <= ZONA_DE_SEGURANCA) {
                grid[i][j].setEnemy(nullptr);
                grid[i][j].setEvent(nullptr);
                continue;
            }

            if (temEntidadeProxima(i, j)) {
                grid[i][j].setEnemy(nullptr);
                grid[i][j].setEvent(nullptr);
                continue;
            }

            int roll = chance(gen);

            if (roll <= 35) { 
                Enemy* novoInimigo = Enemy::createRandomEnemy(1);
                grid[i][j].setEnemy(novoInimigo);
                grid[i][j].setEvent(nullptr);

            } else if (roll <= 85) { 
                grid[i][j].setEnemy(nullptr);
                Event* novoEvento = Event::createRandomEvent(player, itemManager, this, true);
                grid[i][j].setEvent(novoEvento);

            } else {
                grid[i][j].setEnemy(nullptr);
                grid[i][j].setEvent(nullptr);
            }
        }
    }
}

bool Map::movePlayer(int& playerY, int& playerX, Direction dir, int baseVisionRadius) {
    int newY = playerY;
    int newX = playerX;

    switch (dir) {
        case Direction::UP:    newY--; break;
        case Direction::DOWN:  newY++; break;
        case Direction::LEFT:  newX--; break;
        case Direction::RIGHT: newX++; break;
    }

    if (newY < 0 || newY >= altura || newX < 0 || newX >= largura) {
        std::cout << "\n[Movimento]: Limite do mapa atingido!\n";
        return false;
    }

    if (!grid[newY][newX].isWalkable()) {
        std::cout << "\n[Movimento]: Colisao com parede ou obstaculo!\n";
        return false;
    }

    playerY = newY;
    playerX = newX;

    // Incrementa os passos e avança o ciclo dia/noite
    countStep();

    // Calcula raio de visão final aplicando os bônus do ciclo de tempo
    int effectiveVision = baseVisionRadius + getVisionBonus();
    if (effectiveVision < 1) effectiveVision = 1;

    // Atualiza as células descobertas em volta do jogador
    revealAroundPlayer(playerY, playerX, effectiveVision);

    return true;
}

void Map::checkTileContent(int playerY, int playerX, Player* player, ItemManager* itemManager) {
    Tiles& tileAtual = grid[playerY][playerX];

    if (tileAtual.getEnemy() != nullptr) {
        std::cout << "\033[1;31m\n[BATALHA]: Inimigo detectado!\033[0m\n";

        Battle batalha(player, tileAtual.getEnemy());
        batalha.battleGoing();

        delete tileAtual.getEnemy();
        tileAtual.setEnemy(nullptr);
    } 
    else if (tileAtual.getEvent() != nullptr) {
        std::cout << "\033[1;33m\n[EVENTO]: Encontraste algo no caminho!\033[0m\n";

        Event* eventoAtual = tileAtual.getEvent();

        eventoAtual->setPlayer(player);
        eventoAtual->setItemManager(itemManager);
        eventoAtual->setMap(this);

        eventoAtual->triggerEvent(*player, itemManager, this);

        delete eventoAtual;
        tileAtual.setEvent(nullptr);
    }
}