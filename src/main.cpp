#include "Player.h"
#include "Enemy.h"
#include "Battle.h"
#include <iostream>

int main() {
    Inventory inventario({}, 10, nullptr, nullptr);
    inventario.addItem(Item(1, "Espada", "Comum", 0, 10, 2, 1));
    inventario.addItem(Item(2, "Pocao", "Comum", 20, 0, 0, 0));

    Player player("Heroi", 100, 100, 15, 5, 7, 50, inventario);
    Enemy enemy(80, 80, 12, 4, 6, WOLF, 1);

    Battle battle(&player, &enemy, 1);
    battle.battleGoing();

    return 0;
}
