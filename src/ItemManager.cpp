#include "ItemManager.h"
#include "json.hpp"
#include "GameItemException.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using json = nlohmann::json;

ItemManager::ItemManager() {}

bool ItemManager::loadItemsFromJson(const std::string& filePath) {
    try {
        std::string pathUsado = filePath;
        std::ifstream file(pathUsado);
        if (!file.is_open()) {
            pathUsado = "Woodland_items.json";
            file.open(pathUsado);
            if (!file.is_open()) {
                pathUsado = "Woodland_items1.json";
                file.open(pathUsado);
            }
        }

        if (!file.is_open()) {
            throw GameItemException("Nao foi possivel abrir o arquivo de itens: " + filePath);
        }

        json j;
        file >> j;

        allItems.clear();
        categorizedItems.clear();

        // Categorias mantidas no projeto (weapons e items)
        std::vector<std::string> categories = {"weapons", "items"};

        for (const auto& category : categories) {
            if (j.contains(category) && j[category].is_array()) {
                for (const auto& jsonItem : j[category]) {
                    int id = jsonItem.value("id", 0);
                    std::string name = jsonItem.value("name", "Desconhecido");
                    std::string rarity = jsonItem.value("rarity", "Common");

                    int life = 0, attack = 0, armor = 0, speed = 0;

                    if (jsonItem.contains("stats")) {
                        auto stats = jsonItem["stats"];

                        auto parseStat = [](const json& statJson, const std::string& key) -> int {
                            if (!statJson.contains(key)) return 0;
                            try {
                                if (statJson[key].is_number()) {
                                    return statJson[key].get<int>();
                                } else if (statJson[key].is_string()) {
                                    return std::stoi(statJson[key].get<std::string>());
                                }
                            } catch (const std::exception&) {
                                return 0;
                            }
                            return 0;
                        };

                        life = parseStat(stats, "life");
                        attack = parseStat(stats, "attack");
                        armor = parseStat(stats, "armor");
                        speed = parseStat(stats, "speed");
                    }

                    Item item(id, name, rarity, life, attack, armor, speed);
                    allItems.push_back(item);
                    categorizedItems[category].push_back(item);
                }
            }
        }

        if (allItems.empty()) {
            throw GameItemException("Nenhum item valido foi encontrado no JSON.");
        }

        return true;

    } catch (const json::parse_error& e) {
        std::cerr << "[ItemManager Error] Erro de sintaxe no JSON: " << e.what() << std::endl;
        return false;
    } catch (const std::exception& e) {
        std::cerr << "[ItemManager Error] Erro ao carregar itens: " << e.what() << std::endl;
        return false;
    }
}

const std::vector<Item>& ItemManager::getAllItems() const {
    return allItems;
}

const Item* ItemManager::getItemById(int id) const {
    try {
        auto it = std::find_if(allItems.begin(), allItems.end(), [id](const Item& item) {
            return item.getId() == id;
        });

        if (it != allItems.end()) {
            return &(*it);
        }
        return nullptr;
    } catch (const std::exception& e) {
        std::cerr << "[ItemManager Error] Erro ao buscar item por ID: " << e.what() << std::endl;
        return nullptr;
    }
}

const Item* ItemManager::getItemByName(const std::string& name) const {
    auto it = std::find_if(allItems.begin(), allItems.end(), [&name](const Item& item) {
        return item.getName() == name;
    });

    if (it != allItems.end()) {
        return &(*it);
    }
    return nullptr;
}

std::string ItemManager::getRandomRarity() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::discrete_distribution<> dist({60, 30, 10});

    int roll = dist(gen);
    if (roll == 0) return "Common";
    if (roll == 1) return "Rare";
    return "Heroic";
}

std::vector<Item> ItemManager::getDistinctItemsByRarity(const std::string& rarity, int count) {
    std::vector<Item> pool;
    std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(pool),
        [&rarity](const Item& item) {
            return item.getRarity() == rarity;
        }
    );

    if (pool.empty()) {
        pool = allItems;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::shuffle(pool.begin(), pool.end(), gen);

    std::vector<Item> result;
    for (const auto& item : pool) {
        auto jaTem = [&result](const Item& c) {
            return std::any_of(result.begin(), result.end(), [&c](const Item& exist) {
                return exist.getName() == c.getName();
            });
        };

        if (!jaTem(item)) {
            result.push_back(item);
        }
        int curSize = result.size();
        if (curSize >= count) break;
    }

    int poolSize = pool.size();
    while (static_cast<int>(result.size()) < count && poolSize > 0) {
        result.push_back(pool[result.size() % poolSize]);
    }

    return result;
}

Item ItemManager::getRandomItemForChest(std::string targetRarity) {
    try {
        if (allItems.empty()) {
            throw std::underflow_error("Lista de itens esta vazia. Carregue o JSON primeiro.");
        }

        if (targetRarity.empty()) {
            targetRarity = getRandomRarity();
        }

        std::vector<Item> filteredItems;

        std::copy_if(allItems.begin(), allItems.end(), std::back_inserter(filteredItems),
            [&targetRarity](const Item& item) {
                return item.getRarity() == targetRarity;
            }
        );

        if (filteredItems.empty()) {
            filteredItems = allItems;
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        int totalFiltered = filteredItems.size();
        std::uniform_int_distribution<int> dist(0, totalFiltered - 1);

        return filteredItems[dist(gen)];

    } catch (const std::exception& e) {
        std::cerr << "[ItemManager Error] Erro ao roletar item para o bau: " << e.what() << std::endl;
        return Item();
    }
}

const std::vector<Item>& ItemManager::getItemsByCategory(const std::string& category) const {
    static const std::vector<Item> emptyVector;
    auto it = categorizedItems.find(category);
    if (it != categorizedItems.end()) {
        return it->second;
    }
    return emptyVector;
}