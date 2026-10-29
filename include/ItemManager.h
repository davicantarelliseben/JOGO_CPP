#pragma once

#include "Item.h"
#include <vector>
#include <string>
#include <memory>
#include <random>
#include <map>

class ItemManager {
private:
    std::vector<Item> allItems;
    std::map<std::string, std::vector<Item>> categorizedItems;

public:
    ItemManager();

    // Helper para roletar raridade (60% Common, 30% Rare, 10% Heroic)
    std::string getRandomRarity();

    // Carrega itens do JSON
    bool loadItemsFromJson(const std::string& filePath);

    // Retorna todos os itens
    const std::vector<Item>& getAllItems() const;

    // Busca item por ID ou Nome
    const Item* getItemById(int id) const;
    const Item* getItemByName(const std::string& name) const;

    // Retorna itens de uma raridade sem repeticao de nome
    std::vector<Item> getDistinctItemsByRarity(const std::string& rarity, int count);

    // Roleta item do bau
    Item getRandomItemForChest(std::string targetRarity = "");

    // Itens por categoria
    const std::vector<Item>& getItemsByCategory(const std::string& category) const;
};
