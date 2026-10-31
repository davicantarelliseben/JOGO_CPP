#include "../include/Map.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>
#include <random>

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

int Map::getAltura() {
    return this->altura;
}

int Map::getLargura() {
    return this->largura;
}

Tiles& Map::getTile(int y, int x) {
    return this->grid[y][x];
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

void Map::printMap(int playerY, int playerX) {
    if (grid.empty()) {
        std::cout << "[Mapa Vazio]: Nenhum grid foi carregado.\n";
        return;
    }

    std::cout << "\n=== EXIBICAO DO MAPA (" << altura << "x" << largura << ") ===\n";
    std::cout << "Legenda: \033[1;34mP\033[0m=Player | \033[1;31mE\033[0m=Enemy | \033[1;33mV\033[0m=Event | \033[32mO\033[0m=Vazio | \033[90mX\033[0m=Parede\n\n";

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {
            
            // 1. Posição do Jogador (Azul Negrito)
            if (i == playerY && j == playerX) {
                std::cout << "\033[1;34mP\033[0m"; 
            }
            // 2. Tile Caminhável
            else if (grid[i][j].isWalkable()) {
                if (grid[i][j].getEnemy() != nullptr) {
                    std::cout << "\033[1;31mE\033[0m"; // E em Vermelho Negrito (Inimigo)
                } else if (grid[i][j].getEvent() != nullptr) {
                    std::cout << "\033[1;33mV\033[0m"; // V em Amarelo Negrito (Evento)
                } else {
                    std::cout << "\033[32mO\033[0m";    // O em Verde (Livre)
                }
            } 
            // 3. Tile Não Caminhável (Parede em Cinza Escuro para Fundo)
            else {
                std::cout << "\033[90mX\033[0m";
            }
        }
        std::cout << '\n'; // Quebra de linha ao fim de cada fileira
    }

    std::cout << "\n=====================================\n";
}

void Map::populateEventsAndBattles(int playerY, int playerX, Player* player, ItemManager* itemManager) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> chance(1, 100);

    const int ZONA_DE_SEGURANCA = 5; // Distância mínima do spawn do jogador
    const int ESPACAMENTO_MINIMO = 3; // Distância mínima (em tiles) entre inimigos/eventos

    // Função lambda para verificar se há alguma entidade próxima
    auto temEntidadeProxima = [this, ESPACAMENTO_MINIMO](int cy, int cx) -> bool {
        int minY = std::max(0, cy - ESPACAMENTO_MINIMO);
        int maxY = std::min(altura - 1, cy + ESPACAMENTO_MINIMO);
        int minX = std::max(0, cx - ESPACAMENTO_MINIMO);
        int maxX = std::min(largura - 1, cx + ESPACAMENTO_MINIMO);

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                // Se encontrar um inimigo ou evento já colocado nessa vizinhança
                if (grid[y][x].getEnemy() != nullptr || grid[y][x].getEvent() != nullptr) {
                    return true;
                }
            }
        }
        return false;
    };

    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j < largura; ++j) {

            // 1. Ignora tiles não caminháveis
            if (!grid[i][j].isWalkable()) {
                continue;
            }

            // 2. Garante zona de segurança ao redor do jogador
            int distanciaPlayer = std::abs(i - playerY) + std::abs(j - playerX);
            if (distanciaPlayer <= ZONA_DE_SEGURANCA) {
                grid[i][j].setEnemy(nullptr);
                grid[i][j].setEvent(nullptr);
                continue;
            }

            // 3. Se já houver um inimigo ou evento perto deste tile, ignora para não aglomerar
            if (temEntidadeProxima(i, j)) {
                grid[i][j].setEnemy(nullptr);
                grid[i][j].setEvent(nullptr);
                continue;
            }

            // 4. Sorteio de densidade ajustado (chances mais altas para preencher melhor com o filtro ativo)
            int roll = chance(gen);

            if (roll <= 45) { 
                // 45% de tentativa para Inimigo
                Enemy* novoInimigo = Enemy::createRandomEnemy(1);
                grid[i][j].setEnemy(novoInimigo);
                grid[i][j].setEvent(nullptr);

            } else if (roll <= 80) { 
                // 35% de tentativa para Evento Aleatório (46 a 80)
                grid[i][j].setEnemy(nullptr);
                Event* novoEvento = Event::createRandomEvent(player, itemManager, this, true);
                grid[i][j].setEvent(novoEvento);

            } else {
                // 20% restante permanece livre
                grid[i][j].setEnemy(nullptr);
                grid[i][j].setEvent(nullptr);
            }
        }
    }
}

bool Map::movePlayer(int& playerY, int& playerX, Direction dir) {
    int newY = playerY;
    int newX = playerX;

    // 1. Calcula a nova posição pretendida com base na direção
    switch (dir) {
        case Direction::UP:    newY--; break;
        case Direction::DOWN:  newY++; break;
        case Direction::LEFT:  newX--; break;
        case Direction::RIGHT: newX++; break;
    }

    // 2. Valida os limites da matriz do mapa
    if (newY < 0 || newY >= altura || newX < 0 || newX >= largura) {
        std::cout << "\n[Movimento]: Limite do mapa atingido!\n";
        return false;
    }

    // 3. Valida se o tile de destino é caminhável
    if (!grid[newY][newX].isWalkable()) {
        std::cout << "\n[Movimento]: Colisao com parede ou obstaculo!\n";
        return false;
    }

    // 4. Atualiza a posição do jogador e consome o passo
    playerY = newY;
    playerX = newX;
    countStep();

    return true;
}

void Map::checkTileContent(int playerY, int playerX, Player* player, ItemManager* itemManager) {
    Tiles& tileAtual = grid[playerY][playerX];

    // 1. Encontrou um Inimigo
    if (tileAtual.getEnemy() != nullptr) {
        std::cout << "\033[1;31m\n[BATALHA]: Inimigo detectado!\033[0m\n";

        // Instancia e executa o combate
        Battle batalha(player, tileAtual.getEnemy());
        batalha.battleGoing();

        // Desaloca a memória e limpa a célula
        delete tileAtual.getEnemy();
        tileAtual.setEnemy(nullptr);
    } 
    // 2. Encontrou um Evento
    else if (tileAtual.getEvent() != nullptr) {
        std::cout << "\033[1;33m\n[EVENTO]: Encontraste algo no caminho!\033[0m\n";

        Event* eventoAtual = tileAtual.getEvent();

        // Atualiza as referências internas do evento antes de disparar
        eventoAtual->setPlayer(player);
        eventoAtual->setItemManager(itemManager);
        eventoAtual->setMap(this);

        // Executa a lógica do evento (passando *player como referência)
        eventoAtual->triggerEvent(*player, itemManager, this);

        // Desaloca a memória e limpa a célula
        delete eventoAtual;
        tileAtual.setEvent(nullptr);
    }
}