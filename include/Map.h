#pragma once
#include "Tiles.h"
#include <vector>
#include <string>

// Declarações antecipadas (Forward declarations)
class Player;
class ItemManager;

// Enumeração para as direções de movimento no mapa
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
    bool movePlayer(int& playerY, int& playerX, Direction dir);
    void checkTileContent(int playerY, int playerX, Player* player, ItemManager* itemManager);

    // Gestão de Ciclo de Tempo
    void cycleDay();
    int getSteps();
    int countStep();
    bool isDay() const;
    void addSteps(int val);
    void setSteps(int val);

    // Visualização e Carregamento
    void revealAroundPlayer(int radius = 3);
    void populateEventsAndBattles(int playerY, int playerX, Player* player, ItemManager* itemManager);
    void printMap(int playerY = -1, int playerX = -1);
    bool loadFromFile(const std::string& filename);

    // Getters do Grid
    int getAltura();
    int getLargura();
    Tiles& getTile(int y, int x);
};