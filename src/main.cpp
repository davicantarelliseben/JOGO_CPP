#include "include/Inventory.h"
#include "include/Map.h"
#include "include/Player.h"
#include "include/RaylibGame.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<Item> weapons;
    std::vector<Item> items;

    std::string itemPath;
    for (const char* candidate : {"Woodland_items.json", "../Woodland_items.json"}) {
        std::ifstream file(candidate);
        if (file.good()) {
            itemPath = candidate;
            break;
        }
    }
    if (itemPath.empty()) {
        std::cerr << "Nao foi possivel localizar Woodland_items.json.\n";
        return 1;
    }
    if (!loadGameItems(itemPath, weapons, items)) {
        return 1;
    }

    Inventory inventory({}, 10, nullptr, nullptr);
    Player player("Aventureiro", 36, 36, 5, 2, 6, 8, inventory);
    Map map;
    return runRaylibGame(player, map, weapons, items);
}
