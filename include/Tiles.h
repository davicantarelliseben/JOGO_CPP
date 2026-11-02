#pragma once
#include "Battle.h"
#include "Event.h"

enum class TileState {
    Unexplored, // Não visitado / Coberto por névoa
    Explored,   // Já visitado (fora da visão direta)
    Visible     // Visível no raio atual do jogador
};

class Tiles {
private:
    bool walkable;
    Battle* battle;
    Enemy* enemy;
    Event* event;
    TileState state; // Estado de visibilidade no mapa

public:
    Tiles(bool walkable = true, Battle* battle = nullptr, Event* event = nullptr, Enemy* enemy = nullptr, TileState state = TileState::Unexplored);
    
    void setWalkable(bool v);
    bool isWalkable();
    bool isBattle();
    bool isEnemy();
    bool isEvent();

    Event* getEvent();
    Battle* getBattle();
    Enemy* getEnemy();
    void setEvent(Event* newEvent);
    void setBattle(Battle* newBattle);
    void setEnemy(Enemy* newEnemy);

    // Métodos para o controle da Névoa de Guerra
    TileState getState() const;
    void setState(TileState newState);
};