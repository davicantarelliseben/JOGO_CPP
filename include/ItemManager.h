#pragma once

#include "Item.h"
#include <vector>
#include <string>
#include <random>
#include <map>

class ItemManager {
private:
    std::vector<Item> allItems;
    std::map<std::string, std::vector<Item>> categorizedItems;

    // Gerador de números aleatórios encapsulado na classe
    mutable std::mt19937 rng;

public:
    ItemManager();

    // Helper para roletar raridade (60% Common, 30% Rare, 10% Heroic)
    std::string getRandomRarity();

    // Carrega itens do JSON
    bool loadItemsFromJson(const std::string& filePath);

    // Retorna todos os itens
    const std::vector<Item>& getAllItems() const;

    // Busca item por ID ou Nome (retorna nullptr se não encontrar)
    const Item* getItemById(int id) const;
    const Item* getItemByName(const std::string& name) const;

    // Retorna itens de uma raridade sem repeticao de nome
    std::vector<Item> getDistinctItemsByRarity(const std::string& rarity, int count);

    // Roleta item do bau
    Item getRandomItemForChest(std::string targetRarity = "");

    // Itens por categoria (ex: "weapons", "items")
    const std::vector<Item>& getItemsByCategory(const std::string& category) const;
};