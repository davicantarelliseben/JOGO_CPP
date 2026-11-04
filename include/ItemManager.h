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
public:
    ItemManager();

    bool loadItemsFromJson(const std::string& filePath);
    const std::vector<Item>& getAllItems() const;
    const Item* getItemById(int id) const;
    const Item* getItemByName(const std::string& name) const;
    std::string getRandomRarity();
    std::vector<Item> getDistinctItemsByRarity(const std::string& rarity, int count);
    const std::vector<Item>& getItemsByCategory(const std::string& category) const;
};