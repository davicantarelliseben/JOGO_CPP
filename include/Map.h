#pragma once
#include "Tiles.h"
#include <vector>
#include <string>

class Player;
class ItemManager;

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Map {
private:
    int stepsCounter;
    bool day;
    std::vector<std::vector<Tiles>> grid;
    int altura = 0;
    int largura = 0;

public:
    Map(int stepsCounter = 30, bool day = true);
    
    // Movimentação do Jogador
    bool movePlayer(int& playerY, int& playerX, Direction dir, int baseVisionRadius = 3);
    void checkTileContent(int playerY, int playerX, Player* player, ItemManager* itemManager);

    // Gestão de Ciclo de Tempo
    void cycleDay();
    int getSteps();
    int countStep();
    bool isDay() const;
    void addSteps(int val);
    void setSteps(int val);
    int getVisionBonus() const; // Retorna o bônus/penalidade de visão conforme a hora atual

    // Visualização e Carregamento
    // 1. Revela a partir das coordenadas passadas (movimentação normal)
    void revealAroundPlayer(int playerY, int playerX, int visionRadius = 3);
    
    // 2. Sobrecarga para o evento da lookouttower (revela um raio específico)
    void revealAroundPlayer(int visionRadius);

    void populateEventsAndBattles(int playerY, int playerX, Player* player, ItemManager* itemManager);
    void printMap(int playerY = -1, int playerX = -1);
    bool loadFromFile(const std::string& filename);

    int getAltura();
    int getLargura();
    Tiles& getTile(int y, int x);
};