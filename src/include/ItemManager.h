#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "json.hpp"

using json =  nlohmann::json;



class ItemManager {
    protected:
        
        struct itemCoiso {
            int id;
            std::string name;
            std::string rarity;

            unsigned int life;
            unsigned int attack;
            unsigned int armor;
            unsigned int speed;
        };

        std::vector<itemCoiso> itensJson;


    public:

        
        bool loadJson(const std::string& filename) {
    std::ifstream arquivojson(filename);
    if (!arquivojson.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return false;
    }

    json input_json;
    arquivojson >> input_json;

    itensJson.clear();

    // Correção: Garante que estamos lidando com um array JSON antes de iterar
    if (input_json.is_array()) {
        for (const auto& item : input_json) {
            // Garante que cada elemento dentro do array é um objeto {} antes de usar .value()
            if (item.is_object()) {
                itemCoiso novoItem;
                novoItem.id = item.value("id", 0);
                novoItem.name = item.value("name", "Unknown");
                novoItem.rarity = item.value("rarity", "Common");
                novoItem.life = item.value("life", 0u);
                novoItem.attack = item.value("attack", 0u);
                novoItem.armor = item.value("armor", 0u);
                novoItem.speed = item.value("speed", 0u);

                itensJson.push_back(novoItem);
            }
        }
    } else if (input_json.is_object() && input_json.contains("items") && input_json["items"].is_array()) {
        // Caso seu JSON tenha uma chave raiz como: { "items": [ ... ] }
        for (const auto& item : input_json["items"]) {
            if (item.is_object()) {
                itemCoiso novoItem;
                novoItem.id = item.value("id", 0);
                novoItem.name = item.value("name", "Unknown");
                novoItem.rarity = item.value("rarity", "Common");
                novoItem.life = item.value("life", 0u);
                novoItem.attack = item.value("attack", 0u);
                novoItem.armor = item.value("armor", 0u);
                novoItem.speed = item.value("speed", 0u);

                itensJson.push_back(novoItem);
            }
        }
    } else {
        std::cerr << "Formato de JSON inválido ou inesperado!" << std::endl;
        return false;
    }

    return true;
}
        
        void proporItens() const {
        if (itensJson.empty()) {
            std::cout << "Nenhum item disponível no gerenciador." << std::endl;
            return;
        }

        std::cout << "--- Itens Disponíveis em WoodLand ---" << std::endl;
        for (const auto& item : itensJson) {
            std::cout << "[" << item.id << "] " << item.name 
                      << " (" << item.rarity << ") - "
                      << "ATK: " << item.attack << " | "
                      << "DEF: " << item.armor << " | "
                      << "HP: " << item.life << " | "
                      << "SPD: " << item.speed << std::endl;
        }
    }

};